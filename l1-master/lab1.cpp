#include <iostream>
#include <memory>
#include <string>
#include <map>

using namespace std;

struct AutoPartsStore // "магазин AutoPartsStore", карточка №13
{
    int key;
    string name;
    string brand;
    string model;
    int value;
    string existence;
};

int main()
{
    map <int, shared_ptr <AutoPartsStore>> parts
    {
        pair<int, shared_ptr <AutoPartsStore>> (798,make_shared<AutoPartsStore>(AutoPartsStore {798,"Подшипник", "Тойота","Рав4",1500, "7 штук" })),
        pair<int, shared_ptr <AutoPartsStore>> (154,make_shared<AutoPartsStore>(AutoPartsStore {154,"Масляный фильтр", "Тойота","Форчунер",500,  "нет в наличии" })),
        pair<int, shared_ptr <AutoPartsStore>> (398,make_shared<AutoPartsStore>(AutoPartsStore {398,"Стойка ГРМ", "Тойота","Спринтер",7100, "3 штуки" })),
    };

    for(auto part : parts)
        cout << part.first << ' ' <<  part.second->name << ' ' << part.second->brand << ' ' << part.second->model << ' ' << part.second->value << ' ' << part.second->existence << endl;

    return 0;
}