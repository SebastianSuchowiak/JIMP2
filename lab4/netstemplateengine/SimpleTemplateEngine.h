//
// Created by sebastian on 26.03.18.
//

#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H


#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>

namespace nets {
    class View {

    public:
        explicit View(std::string templateString);
        std::string Render(const std::unordered_map <std::string, std::string> &model) const;

    private:
        std::string m_templateString;
    };

    std::string ReplaceString(std::string subject, const std::string& search,
                              const std::string& replace);
}



#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
