#include "hw/l3_DomainLayer.h"

using namespace std;

Date::Date(const Date &date)
        : _year(date._year)
        , _month(date._month)
        , _day(date._day) {
    assert(invariant());
}

Date::Date(const int y, const int m, const int d)
        : _year(y)
        , _month(m)
        , _day(d) {
    assert(invariant());
}

int Date::get_year() const {
    return _year;
}

int Date::get_month() const {
    return _month;
}

int Date::get_day() const {
    return _day;
}

bool Date::is_expired(const Date &deadline) const {
    return _year * 365 + _month * 30 + _day <= deadline.get_year() * 365 + deadline.get_month() * 30 + deadline.get_day();
}

bool Date::invariant() const {
    return _day >= MIN_DAY
           && _day <= MAX_DAY
           && _month >= MIN_MONTH
           && _month <= MAX_MONTH
           && _year <= MAX_YEAR
           && _year >= MIN_YEAR;
}
bool AutoPartsStore::invariant() const {
    return !_name.empty()
           && _name.size() <= MAX_AUTO_PARTS_NAME_LENGTH
           && !_model_auto.empty()
           && _model_auto.size() <= MAX_MODEL_NAME_LENGTH
           && !_brand_auto.empty()
           && _brand_auto.size() <= MAX_BRAND_AUTO_LENGTH
           && _price <= MAX_PRICE;
}

AutoPartsStore::AutoPartsStore(
        const std::string &name, const std::string &model,
        const std::string &brand, const size_t price,
        const bool in_stock, Date& shelf_life)
        : _name(name)
        , _model_auto(model)
        , _brand_auto(brand)
        , _price(price)
        , _is_in_stock(in_stock)
        , _shelf_life(shelf_life) {
    assert(invariant());
}

const std::string& AutoPartsStore::get_auto_parts_store_name() const {
    return _name;
}

const std::string& AutoPartsStore::get_model_auto() const {
    return _model_auto;
}

const std::string& AutoPartsStore::get_brand_auto() const {
    return _brand_auto;
}

uint16_t AutoPartsStore::get_price() const {
    return _price;
}

bool AutoPartsStore::get_is_in_stock() const {
    return _is_in_stock;
}

const Date& AutoPartsStore::get_shelf_life() const {
    return _shelf_life;
}

bool AutoPartsStore::write(std::ostream &os) {
    writeString(os, _name);
    writeString(os, _model_auto);
    writeString(os, _brand_auto);
    writeNumber(os, _price);
    writeNumber(os, _is_in_stock);
    writeNumber(os, _shelf_life.get_day());
    writeNumber(os, _shelf_life.get_month());
    writeNumber(os, _shelf_life.get_year());

    return os.good();
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream &is) {
    std::string auto_parts_name = readString(is, MAX_AUTO_PARTS_NAME_LENGTH);
    std::string model_name = readString(is, MAX_MODEL_NAME_LENGTH);
    std::string brand = readString(is, MAX_BRAND_AUTO_LENGTH);
    uint16_t price = readNumber<int>(is);
    bool in_stock = readNumber<int>(is);
    int day = readNumber<int>(is);
    int month = readNumber<int>(is);
    int year = readNumber<int>(is);
    Date date(year, month, day);

    return std::make_shared<AutoPartsStore>(auto_parts_name, model_name, brand, price, in_stock, date);
}
