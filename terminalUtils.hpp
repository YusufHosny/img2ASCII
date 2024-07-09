#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

#include <vector>
#include <opencv2/opencv.hpp>

struct Pixel {
    double R, G, B;
};

class Terminal {
    public:
        int width;
        int height;

        std::vector<std::vector<Pixel>> pixels;

        Terminal();
        Terminal(cv::Mat image);
    
        double getLuminance(int x, int y);
        void refresh();
        void visualizeOnGui();
};

#endif