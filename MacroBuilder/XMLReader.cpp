#include "XMLReader.h"
#include "tinyxml2.h"
#include <iostream>

bool XMLReader::ReadActivatorFromXML(const std::string& filename, ActivatorData& data)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename.c_str());

    if (error != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file: " << doc.ErrorIDToName(error) << std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("ActivatorData");
    if (!root) {
        std::cerr << "Error: Root element <ActivatorData> not found." << std::endl;
        return false;
    }

    // Читаем Name
    tinyxml2::XMLElement* nameElement = root->FirstChildElement("Name");
    if (nameElement) {
        const char* name = nameElement->GetText();
        if (name) {
            data.Name = name;
        }
    }

    // Читаем FixedKeyOrder
    tinyxml2::XMLElement* fixedKeyOrderElement = root->FirstChildElement("FixedKeyOrder");
    if (fixedKeyOrderElement) {
        const char* value = fixedKeyOrderElement->GetText();
        if (value) {
            data.FixedKeyOrder = (std::string(value) == "true");
        }
    }

    // Читаем Keys
    tinyxml2::XMLElement* keysContainer = root->FirstChildElement("Keys");
    if (keysContainer) {
        for (tinyxml2::XMLElement* keyElement = keysContainer->FirstChildElement("KeyActivator");
            keyElement;
            keyElement = keyElement->NextSiblingElement("KeyActivator")) {

            KeyActivator key;
            tinyxml2::XMLElement* keyNameElement = keyElement->FirstChildElement("Name");
            if (keyNameElement) {
                const char* keyName = keyNameElement->GetText();
                if (keyName) {
                    key.Name = keyName;
                    data.Keys.push_back(key);
                }
            }
        }
    }

    return true;

}
