#pragma once

#include "Activator.h"
#include <string>
#include <vector>

struct ActivatorData {

    std::string Name;
    std::vector <KeyActivator> Keys;
    bool FixedKeyOrder;

};

class XMLReader
{
public:

    static bool ReadActivatorFromXML(const std::string& filename, ActivatorData& OuterData);
};

