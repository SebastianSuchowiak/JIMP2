//
// Created by sebastian on 06.05.18.
//

#include <MovieSubtitles.h>
#include <iostream>



int main() {

    auto subs = std::make_unique<moviesubs::SubRipSubtitles>();
    std::stringstream in {"1\n00:05:54,555 --> 00:05:56,722\nText\n\n2\n00:06:06,433 --> 00:06:07,801\nNEWLINE\n"};
    std::stringstream out;
    subs->ShiftAllSubtitlesBy(300, 24, &in, &out);
    std::cout << out.str();
}