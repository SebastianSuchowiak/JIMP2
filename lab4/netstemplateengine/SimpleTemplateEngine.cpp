//
// Created by sebastian on 26.03.18.
//

#include "SimpleTemplateEngine.h"

namespace nets {

    View::View(const std::string templateString): m_templateString{templateString} {}

    std::string View::Render(const std::unordered_map<std::string, std::string> &model) const {

        std::string renderedTemplate = m_templateString;
        std::regex pattern("\\{\\{[A-Za-z0-9_]+\\}\\}");
        int positionToMoveBack = 0;
        bool matchWasReplaced;

        for(std::sregex_iterator i = std::sregex_iterator(m_templateString.begin(), m_templateString.end(), pattern);
            i != std::sregex_iterator();
            ++i ) {

            std::smatch match = *i;
            matchWasReplaced = false;

            for (const auto& switchPair: model) {
                if (match.str() == "{{" + switchPair.first + "}}") {
                    renderedTemplate.replace((unsigned) match.position() - positionToMoveBack,
                                             (unsigned) match.length(), switchPair.second);
                    positionToMoveBack += match.length() - switchPair.second.length();
                    matchWasReplaced = true;
                    break;
                }
            }
            if (!matchWasReplaced) {
                renderedTemplate.erase((unsigned) match.position() - positionToMoveBack,(unsigned) match.length());
                positionToMoveBack += match.length();
            }
        }

        return renderedTemplate;
    }


}

