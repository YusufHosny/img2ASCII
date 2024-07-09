#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include "imageRenderer.hpp"

int main(int argc, char** argv) {

    if(argc < 2) {
        std::cout << "Incorrect usage. Try RenderASCII [PATH TO IMAGE] or RenderASCII [SHAPE].\n";
        return 0;
    }

    std::string shapeName = std::string(argv[1]);
    if(shapeName == "cube" || shapeName == "sphere" || shapeName == "donut") {
        std::cout << "Shapes not yet implemented.\n";
        return 0;
    }

    char fullpath[255];
    if (GetFullPathName(argv[1], 255, fullpath, NULL) == 0) {
        std::cerr << "Error converting to absolute path: " << GetLastError() << "\n";
        return 1;
    }

    cv::String filepath = cv::String(fullpath);
    renderImage(filepath);

    return 0;
}