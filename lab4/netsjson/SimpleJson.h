//
// Created by sebastian on 26.03.18.
//

#ifndef JIMP_EXERCISES_SIMPLEJSON_H
#define JIMP_EXERCISES_SIMPLEJSON_H

#include <experimental/optional>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

namespace nets {
    class JsonValue {

    public:

        JsonValue(bool value);
        JsonValue(int value);
        JsonValue(double value);
        JsonValue(std::string value);
        JsonValue(std::vector<JsonValue> value);
        JsonValue(std::map <std::string, nets::JsonValue> value);

        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;
        std::string ToString() const;

    private:

        std::string getMapString() const;
        std::string getVectorString() const;
        std::string getBoolString() const;
        std::string getDoubleString() const;

    private:

        bool m_boolValue;
        int m_intValue;
        double m_doubleValue;
        std::string m_stringValue;
        std::vector<JsonValue> m_vectorValue;
        std::map <std::string, nets::JsonValue> m_mapValue;

        enum Type{BOOL, INT, DOUBLE, STRING, MAP, VECTOR};
        Type m_type;
    };
}

#endif //JIMP_EXERCISES_SIMPLEJSON_H
