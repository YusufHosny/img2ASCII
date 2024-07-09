#include "terminalUtils.hpp"
#include <windows.h>
#include <iostream>

Terminal::Terminal() {
    this->refresh();
}

Terminal::Terminal(cv::Mat image) {
    this->refresh();
    
    // determine width in pixels of each block which will be mapped to a terminal character
    int blockHeight = std::max(2 * image.cols / this->width, image.rows / this->height) + 1;
    int blockWidth = blockHeight/2;

    cv::Vec3b buf;
    for(int i = 0; i < image.rows; i++)
        for(int j = 0; j < image.cols; j++)
        {
            buf = image.at<cv::Vec3b>(i,j);
            this->pixels.at(i/blockHeight).at(j/blockWidth).B += buf[0] * (1.0/(blockHeight*blockWidth));
            this->pixels.at(i/blockHeight).at(j/blockWidth).G += buf[1] * (1.0/(blockHeight*blockWidth));
            this->pixels.at(i/blockHeight).at(j/blockWidth).R += buf[2] * (1.0/(blockHeight*blockWidth));
        }
}

void Terminal::refresh() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    this->width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    this->height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    for(int i = 0; i < height; i++) {
        std::vector<Pixel> cur;
        for(int j = 0; j < width; j++) {
            Pixel p;
            cur.push_back(p);
        }
        pixels.push_back(cur);
    }

    system("cls");
}

double Terminal::getLuminance(int x, int y) {
    return (0.2126 * pixels[x][y].R + 0.7152 * pixels[x][y].G + 0.0722 * pixels[x][y].B) / 255.;
}

void Terminal::visualizeOnGui() {
    // create image
    cv::Mat image = cv::Mat(this->height, this->width, CV_8UC3);
    cv::Vec3b buf;
    for(int i = 0; i < this->height; i++)
        for(int j = 0; j < this->width; j++)
        {
            buf[0] = this->pixels.at(i).at(j).B;
            buf[1] = this->pixels.at(i).at(j).G;
            buf[2] = this->pixels.at(i).at(j).R;

            image.at<cv::Vec3b>(i,j) = buf;
        }


    // draw image to popup window
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::imshow("Display Image", image);
    cv::waitKey(0);
}