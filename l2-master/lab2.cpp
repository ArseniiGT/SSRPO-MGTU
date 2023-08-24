
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>


class AutoPartsStore {

public:
    AutoPartsStore() : _value(0), _is_in_stock(false) {};
    ~AutoPartsStore() = default;

    void set_name(const std::string& name) {
        _name = name;
    }

    void set_model(std::string& name) {
        _model_auto = std::move(name);
    }
    void set_model(const std::string& name) {
        _model_auto = name;
    }

    void set_brand(std::string& name) {
        _brand_auto = std::move(name);
    }
    void set_brand(const std::string& name) {
        _brand_auto = name;
    }

    void set_value(const int16_t price) {
        _value = _value;
    }

    void set_is_in_stock(const bool in_stock) {
        _is_in_stock = in_stock;
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

    uint16_t get_value() const {
        return _value;
    }

    bool get_is_in_stock() const {
        return _is_in_stock;
    }

    void show_auto_arts_store() const {
        std::cout << "Detail name: " << get_auto_parts_store_name() << " on this auto model: "
                  << get_model_auto() << " of this brand: " << get_brand_auto() << " with the price: " << get_value() << " is ";
        if (!get_is_in_stock()) {
            std::cout << "not ";
        }
        std::cout << "available" << std::endl;
    }

private:
    std::string _name;
    std::string _model_auto;
    std::string _brand_auto;
    int16_t _value;
    bool _is_in_stock;
};

class AutoPartsStoreBuilder {

protected:
    std::shared_ptr<AutoPartsStore> aps;

public:
    AutoPartsStoreBuilder() = default;
    virtual ~AutoPartsStoreBuilder() = default;

    std::shared_ptr<AutoPartsStore> get_auto_parts_store() {
        return aps;
    }

    void create_new_auto_parts_store() {
        aps = std::make_shared<AutoPartsStore>();
    }

    virtual void build_name() = 0;
    virtual void build_brand() = 0;
    virtual void build_model() = 0;
    virtual void build_is_in_stock() = 0;
    virtual void build_price() = 0;
};

class TransmissionBuilder : public AutoPartsStoreBuilder {

public:
    TransmissionBuilder() = default;
    ~TransmissionBuilder() override = default;

    void build_name() override {
        aps->set_name("Топливный фильтр");
    }

    void build_brand() {
        aps->set_brand("Ваз");
    }

    void build_model() {
        aps->set_model("2107");
    }

    void build_is_in_stock() {
        aps->set_is_in_stock(true);
    }

    void build_price() {
        aps->set_value(15000);
    }
};

class WheelsBuilder : public AutoPartsStoreBuilder {

public:
    WheelsBuilder() = default;
    ~WheelsBuilder() override = default;

    void build_name() override {
        aps->set_name("Диски");
    }

    void build_brand() {
        aps->set_brand("Мерседес");
    }

    void build_model() {
        aps->set_model("Мерин");
    }

    void build_is_in_stock() {
        aps->set_is_in_stock(true);
    }

    void build_price() {
        aps->set_value(30000);
    }
};

class BodyKitBuilder : public AutoPartsStoreBuilder {

public:
    BodyKitBuilder() = default;
    ~BodyKitBuilder() override = default;

    void build_name() override {
        aps->set_name("Стойка стабилизатора");
    }

    void build_brand() {
        aps->set_brand("Тойота");
    }

    void build_model() {
        aps->set_model("Рав4");
    }

    void build_is_in_stock() {
        aps->set_is_in_stock(true);
    }

    void build_price() {
        aps->set_value(25000);
    }
};

class ChainAutoPartsStore {

public:
    ChainAutoPartsStore() : _builder(nullptr) {};
    ~ChainAutoPartsStore() = default;

    void set_auto_parts_builder(AutoPartsStoreBuilder* b) {
        _builder = b;
    }

    std::shared_ptr<AutoPartsStore> get_auto_parts_store() {
        return _builder->get_auto_parts_store();
    }

    void create_new_auto_parts_store() {
        _builder->create_new_auto_parts_store();
        _builder->build_name();
        _builder->build_model();
        _builder->build_brand();
        _builder->build_price();
        _builder->build_is_in_stock();
    }

private:
    AutoPartsStoreBuilder* _builder;
};

int main() {
    ChainAutoPartsStore stores;

    TransmissionBuilder tb;
    stores.set_auto_parts_builder(&tb);
    stores.create_new_auto_parts_store();
    auto part = stores.get_auto_parts_store();
    part->show_auto_arts_store();

    BodyKitBuilder kit_builder;
    stores.set_auto_parts_builder(&kit_builder);
    stores.create_new_auto_parts_store();
    auto kit_builder_part = stores.get_auto_parts_store();
    kit_builder_part->show_auto_arts_store();

    WheelsBuilder wheels_builder;
    stores.set_auto_parts_builder(&wheels_builder);
    stores.create_new_auto_parts_store();
    auto wheels_builder_builder_part = stores.get_auto_parts_store();
    wheels_builder_builder_part->show_auto_arts_store();
    return 0;
}