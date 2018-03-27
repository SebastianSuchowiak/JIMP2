//
// Created by sebastian on 26.03.18.
//

#include <SimpleTemplateEngine.h>

int main() {
    nets::View view("{{t09}}<=>{{t17}}");
    std::cout << view.Render({{"t17", "Am I?"}});
}