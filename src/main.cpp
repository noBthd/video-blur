#include <iostream>
#include <stdio.h>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

#define VIDEO_INPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/input
#define VIDEO_OUTPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/output

#define DEVICE_ID 0
#define API_ID cv::CAP_ANY

int main() {
    cv::Mat frame;
    cv::VideoCapture cap;

    cap.open(DEVICE_ID, API_ID);

    if(!cap.isOpened()) {
        std::cout << "ERROR! opening main camera!\n";
        return -1;
    }

    std::cout << "start grabbing" << std::endl 
            << "Press any key to terminate" << std::endl;

    for (;;) {
        cap.read(frame);

        if(frame.empty()) {
            std::cout << "Frame reading error!";
            break;
        }

        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }

    cv::waitKey(0);
    return 0;
}
