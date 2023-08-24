#include "hw/l3_DomainLayer.h"

using namespace std;

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
        const bool in_stock)
        : _name(name)
        , _model_auto(model)
        , _brand_auto(brand)
        , _price(price)
        , _is_in_stock(in_stock) {
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

bool AutoPartsStore::write(std::ostream &os) {
    writeString(os, _name);
    writeString(os, _model_auto);
    writeString(os, _brand_auto);
    writeNumber(os, _price);
    writeNumber(os, _is_in_stock);

    return os.good();
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream &is) {
    std::string auto_parts_name = readString(is, MAX_AUTO_PARTS_NAME_LENGTH);
    std::string model_name = readString(is, MAX_MODEL_NAME_LENGTH);
    std::string brand = readString(is, MAX_BRAND_AUTO_LENGTH);
    uint16_t price = readNumber<int>(is);
    bool in_stock = readNumber<int>(is);

    return std::make_shared<AutoPartsStore>(auto_parts_name, model_name, brand, price, in_stock);
}