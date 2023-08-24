#ifndef L3_L3_DOMAINLAYER_H
#define L3_L3_DOMAINLAYER_H

#include "hw/l4_InfrastructureLayer.h"
#include <cassert>
#include <stdint.h>
#include <memory>

const size_t MAX_PRICE = 5000000;
const size_t MAX_AUTO_PARTS_NAME_LENGTH = 50;
const size_t MAX_MODEL_NAME_LENGTH = 40;
const size_t MAX_BRAND_AUTO_LENGTH = 30;
const int MAX_YEAR = 2100;
const int MAX_DAY = 31;
const int MAX_MONTH = 12;
const int MIN_YEAR = 2020;
const int MIN_DAY = 1;
const int MIN_MONTH = 1;

class Date {
    int _year;
    int _month;
    int _day;

protected:
    bool invariant() const;

public:
    Date() = delete;

    Date(const int y, const int m, const int d);
    Date(const Date& date);

    int get_year() const;
    int get_month() const;
    int get_day() const;

    bool is_expired(const Date& deadline) const;

};

class AutoPartsStore : public ICollectable {
    std::string _name;
    std::string _model_auto;
    std::string _brand_auto;
    size_t _price;
    bool _is_in_stock;
    Date _shelf_life;

protected:
    bool invariant() const;

public:
    AutoPartsStore() = delete;
    AutoPartsStore(const AutoPartsStore& aps) = delete;

    AutoPartsStore& operator = (const AutoPartsStore& aps) = delete;

    AutoPartsStore(const std::string& name, const std::string& model,
                   const std::string& brand, const size_t price, const bool in_stock, Date& shelf_life);

    const std::string& get_auto_parts_store_name() const;

    const std::string& get_model_auto() const;

    const std::string& get_brand_auto() const;

    uint16_t get_price() const;

    bool get_is_in_stock() const;

    const Date& get_shelf_life() const;

    virtual bool write(std::ostream& os) override;

};

class ItemCollector : public ACollector {

public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;
};

#endif //L3_L3_DOMAINLAYER_H
