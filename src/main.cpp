#include <iostream>
#include <fstream>
#include <opencv2/highgui.hpp>


int main() {
    cv::Mat img = cv::imread("/Users/egorkirichenko/Projects/C++/video-blur/img/IMG_0428.JPG");

    cv::imshow("window", img);

    cv::waitKey(0);

    return 0;
}
