//
// Created by sebastian on 26.03.18.
//

#include <iostream>
#include "SimpleJson.h"

namespace nets {

    JsonValue::JsonValue(bool value):
            m_boolValue{value},
            m_type{BOOL} {}

    JsonValue::JsonValue(int value):
            m_intValue{value},
            m_type{INT} {}

    JsonValue::JsonValue(double value):
            m_doubleValue{value},
            m_type{DOUBLE} {}

    JsonValue::JsonValue(std::string value):
            m_type{STRING} {
        for (uint64_t i = 0; i < value.length(); i++){
            if (value[i] == '\"' || value[i] == '\\'){
                value.insert(i, 1, '\\');
                i++;
            }
        }
        m_stringValue = value;
    }

    JsonValue::JsonValue(std::vector<JsonValue> value):
            m_type{VECTOR} {
        m_vectorValue = value;
    }

    JsonValue::JsonValue(std::map <std::string, nets::JsonValue> value):
            m_type{MAP} {
        m_mapValue = value;
    }

    std::experimental::optional<JsonValue> JsonValue::ValueByName(const std::string &name) const {

        if (m_type == MAP) {
            auto search = m_mapValue.find(name);
            if(search != m_mapValue.end()) {
                return search->second;
            }
        }
    }

    std::string JsonValue::ToString() const {

        switch (m_type) {
            case BOOL:
                return getBoolString();
            case INT:
                return std::to_string(m_intValue);
            case DOUBLE:
                return getDoubleString();
            case STRING:
                return "\"" + m_stringValue + "\"";
            case VECTOR:
                return getVectorString();
            case MAP:
                return getMapString();
        }
    }

    std::string JsonValue::getDoubleString() const {

        uint64_t i;
        std::string returnString = std::to_string(m_doubleValue);

        for (i = returnString.length() - 1; returnString[i] == '0' && returnString[i - 1] != '.'; i--);

        return returnString.erase(i + 1, std::string::npos);
    }

    std::string JsonValue::getBoolString() const {

        if (m_boolValue) {
            return "true";
        }

        return "false";
    }

    std::string JsonValue::getVectorString() const {

        std::string stringToReturn = "[";

        for(const JsonValue &elem: m_vectorValue) {
            stringToReturn += elem.ToString() + ", ";
        }

        stringToReturn.erase(stringToReturn.end() - 2, stringToReturn.end());

        return stringToReturn + "]";
    }

    std::string JsonValue::getMapString() const {

        std::string stringToReturn = "{";
        std::string keyString;

        for (const auto& mappedPair: m_mapValue) {

                    for (int i = 0; i < mappedPair.first.length(); ++i) {
                        if (mappedPair.first[i] == '\\') {
                            keyString += "\\\\";
                        } else if (mappedPair.first[i] == '\"') {
                            keyString += "\\\"";
                        } else {
                            keyString += mappedPair.first[i];
                        }
                    }

                    stringToReturn += "\"" + keyString + "\"" ": " + mappedPair.second.ToString() + ", ";
                    keyString.clear();
                }

        stringToReturn.erase(stringToReturn.end() - 2, stringToReturn.end());

        return stringToReturn + "}";
    }
}
