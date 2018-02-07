//
// Created by gabriel on 10/11/16.
//

#ifndef ALGOWEB_PROGRESSANIMATIONS_HPP
#define ALGOWEB_PROGRESSANIMATIONS_HPP

class ProgressAnimations {
public:
    ProgressAnimations() {}

    void printProgBar(unsigned int percent) {
        std::string bar;

        for (unsigned int i = 0; i < 100; i++) {
            if (i < percent) {
                bar.replace(i, 1, "=");
            } else if (i == percent) {
                bar.replace(i, 1, ">");
            } else {
                bar.replace(i, 1, " ");
            }
        }

        std::cout << "\r" "[" << bar << "] ";
        std::cout.width(10);
        std::cout << percent << "%     " << std::flush;
    }
};


#endif //ALGOWEB_PROGRESSANIMATIONS_HPP
