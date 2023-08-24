#include "hw/l2_ApplicationLayer.h"

using namespace std;

bool Application::performCommand(const vector<std::string> &args) {
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load") {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.loadCollection(filename))
        {
            _out.Output("Ошибка при загрузке файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save") {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.saveCollection(filename)) {
            _out.Output("Ошибка при сохранении файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean") {
        if (args.size() != 1) {
            _out.Output("Некорректное количество аргументов команды clean");
            return false;
        }

        col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add") {
        if (args.size() != 9) {
            _out.Output("Некорректное количество аргументов команды add");
            return false;
        }

        Date shelf_life(stoi(args[8]), stoi(args[7]), stoi(args[6]));
        col.addItem(std::make_shared<AutoPartsStore>(args[1].c_str(), args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5]), shelf_life));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove") {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды remove");
            return false;
        }

        col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update") {
        if (args.size() != 10) {
            _out.Output("Некорректное количество аргументов команды update");
            return false;
        }

        Date shelf_life(stoi(args[9]), stoi(args[8]), stoi(args[7]));
        col.updateItem(stoul(args[1]), std::make_shared<AutoPartsStore>(args[2].c_str(), args[3].c_str(),
                                                                        args[4].c_str(), stoul(args[5]), stoul(args[6]), shelf_life));
        return true;
    }

    if (args[0] == "v" || args[0] == "view") {
        if (args.size() != 1) {
            _out.Output("Некорректное количество аргументов команды view");
            return false;
        }

        size_t count = 0;
        for(size_t i = 0; i < col.getSize(); ++i) {
            const AutoPartsStore & item = dynamic_cast<AutoPartsStore &>(*col.getItem(i));

            if (!col.isRemoved(i)) {
                _out.Output("[" + to_string(i) + "] "
                            + item.get_auto_parts_store_name() + " "
                            + item.get_model_auto() + " "
                            + item.get_brand_auto() + " "
                            + to_string(item.get_is_in_stock()) + " "
                            + to_string(item.get_price()) + " "
                            + to_string(item.get_shelf_life().get_day()) + "."
                            + to_string(item.get_shelf_life().get_month()) + "."
                            + to_string(item.get_shelf_life().get_year()));
                count ++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + to_string(count));

        return true;
    }

    if (args[0] == "rp" || args[0] == "report") {
        if (args.size() != 4) {
            _out.Output("Некорректное количество аргументов команды report");
            return false;
        }

        Date report_date(stoi(args[3]), stoi(args[2]), stoi(args[1]));

        for (size_t i = 0; i < col.getSize(); ++i) {
            const AutoPartsStore & item = dynamic_cast<AutoPartsStore &>(*col.getItem(i));
            if (!col.isRemoved(i)) {
                if (item.get_shelf_life().is_expired(report_date)) {
                    _out.Output("Срок годности детали №" + to_string(i) + " истек. Детали:\n" +
                                item.get_auto_parts_store_name() + " "
                                + item.get_model_auto() + " "
                                + item.get_brand_auto() + " "
                                + to_string(item.get_price()) + " "
                                + to_string(item.get_is_in_stock()) + " "
                                + to_string(item.get_shelf_life().get_day()) + "."
                                + to_string(item.get_shelf_life().get_month()) + "."
                                + to_string(item.get_shelf_life().get_year()));
                }
            }
        }
        return true;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return false;
}