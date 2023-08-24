#ifndef L3_L2_APPLICATIONLAYER_H
#define L3_L2_APPLICATIONLAYER_H

#include <string>
#include <vector>

#include "hw/l3_DomainLayer.h"
#include <iostream>

class IOutput
{
public:
    virtual ~IOutput() = default;

    virtual void Output(std::string s) const = 0;
};

class Application
{
public:
    Application() = delete;
    Application(const Application &) = delete;

    Application & operator=(const Application &) = delete;

    Application(const IOutput & out)
            : _out(out)
    {}

    bool performCommand(const std::vector<std::string> & args);

private:
    const IOutput & _out;
    ItemCollector   col;
};

#endif //L3_L2_APPLICATIONLAYER_H
