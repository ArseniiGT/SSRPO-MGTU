#include "collector.h"

using namespace std;

const size_t MAX_PRICE = 5000000;
const size_t MAX_AUTO_PARTS_NAME_LENGTH = 50;
const size_t MAX_MODEL_NAME_LENGTH = 40;
const size_t MAX_BRAND_AUTO_LENGTH = 30;

class AutoPartsStore : public ICollectable {
    std::string _name;
    std::string _model_auto;
    std::string _brand_auto;
    size_t _price;
    bool is_in_stock;

protected:
    bool invariant() const {
        return !_name.empty()
               && _name.size() <= MAX_AUTO_PARTS_NAME_LENGTH
               && !_model_auto.empty()
               && _model_auto.size() <= MAX_MODEL_NAME_LENGTH
               && !_brand_auto.empty()
               && _brand_auto.size() <= MAX_BRAND_AUTO_LENGTH
               && _price <= MAX_PRICE;
    }

public:

    AutoPartsStore() = delete;
    AutoPartsStore(const AutoPartsStore& aps) = delete;

    AutoPartsStore& operator = (const AutoPartsStore& aps) = delete;

    AutoPartsStore(const std::string& name, const std::string& model,
                   const std::string& brand, const size_t price, const bool in_stock)
            : _name(name)
            , _model_auto(model)
            , _brand_auto(brand)
            , _price(price)
            , is_in_stock(in_stock) {
        assert(invariant());
    }

    const std::string& get_auto_parts_store_name() const {
        return _name;
    }

    const std::string& get_model_auto() const {
        return _model_auto;
    }

    const std::string& get_brand_auto() const {
        return _brand_auto;
    }

    size_t get_price() const {
        return _price;
    }

    bool get_is_in_stock() const {
        return is_in_stock;
    }

    virtual bool write(std::ostream& os) override {
        writeString(os, _name);
        writeString(os, _model_auto);
        writeString(os, _brand_auto);
        writeNumber(os, _price);
        writeNumber(os, is_in_stock);

        return os.good();
    }

};

class ItemCollector : public ACollector {

public:
    virtual std::shared_ptr<ICollectable> read(std::istream &is) {
        std::string auto_parts_name = readString(is, MAX_AUTO_PARTS_NAME_LENGTH);
        std::string model_name = readString(is, MAX_MODEL_NAME_LENGTH);
        std::string brand = readString(is, MAX_BRAND_AUTO_LENGTH);
        size_t price = readNumber<size_t>(is);
        bool in_stock = readNumber<int>(is);

        return std::make_shared<AutoPartsStore>(auto_parts_name, model_name, brand, price, in_stock);
    }
};

bool performCommand(const vector<std::string>& args, ItemCollector& col) {
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load") {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.loadCollection(filename))
        {
            std::cerr << "Ошибка при загрузке файла '" << filename << "'" << std::endl;
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save") {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.saveCollection(filename)) {
            std::cerr << "Ошибка при сохранении файла '" << filename << "'" << std::endl;
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean") {
        if (args.size() != 1) {
            std::cerr << "Некорректное количество аргументов команды clean" << std::endl;
            return false;
        }

        col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add") {
        if (args.size() != 6) {
            std::cerr << "Некорректное количество аргументов команды add" << std::endl;
            return false;
        }

        col.addItem(std::make_shared<AutoPartsStore>(args[1].c_str(), args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5])));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove") {
        if (args.size() != 2)
        {
            std::cerr << "Некорректное количество аргументов команды remove" << std::endl;
            return false;
        }

        col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update") {
        if (args.size() != 7) {
            std::cerr << "Некорректное количество аргументов команды update" << std::endl;
            return false;
        }

        col.updateItem(stoul(args[1]), std::make_shared<AutoPartsStore>(
                args[2].c_str(),
                args[3].c_str(),
                args[4].c_str(),
                stoul(args[5]),
                stoul(args[6])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view") {
        if (args.size() != 1) {
            std::cerr << "Некорректное количество аргументов команды view" << std::endl;
            return false;
        }

        size_t count = 0;
        for(size_t i = 0; i < col.getSize(); ++i) {
            const AutoPartsStore & item = static_cast<AutoPartsStore &>(*col.getItem(i));

            if (!col.isRemoved(i)) {
                std::cout << "[" << i << "] "
                          << item.get_auto_parts_store_name() << " "
                          << item.get_model_auto() << " "
                          << item.get_brand_auto() << " "
                          << item.get_is_in_stock() << " "
                          << item.get_price() << std::endl;
                count ++;
            }
        }

        std::cout << "Количество элементов в коллекции: " << count << std::endl;

        return true;
    }

    std::cerr << "Недопустимая команда '" << args[0] << "'" << std::endl;
    return false;

}

int main(int , char **) {
    ItemCollector col;

    for (string line; getline(cin, line); ) {
        if (line.empty())
            break;

        std::istringstream  iss(line);
        std::vector<string> args;

        for(std::string str; iss.good();)
        {
            iss >> str;
            args.emplace_back(str);
        }

        if (!performCommand(args, col))
            return 1;
    }

    std::cout << "Выполнение завершено успешно" << std::endl;
    return 0;
}
