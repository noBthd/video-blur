#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect/face.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#define VIDEO_INPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/input
#define VIDEO_OUTPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/output

#define FACE_DETECT_FOLDER "/Users/egorkirichenko/Projects/C++/video-blur/models/face_detection_yunet_2023mar_int8.onnx"
#define SCORE_THRESHOLD 0.9 
#define NMS_THRESHOLD 0.3 

#define DEVICE_ID 0
#define API_ID cv::CAP_ANY

int main() {
    cv::Mat frame;
    cv::VideoCapture cap;
    std::vector<cv::Rect> faces;
    auto face = cv::FaceDetectorYN::create(FACE_DETECT_FOLDER, "", cv::Size(1920, 1080), SCORE_THRESHOLD, NMS_THRESHOLD);

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

        face->detect(frame, faces);
        std::cout << "Detected faces: " << faces.size() << std::endl;

        for (cv::Rect rect : faces) {
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("Live", frame);
        if (cv::waitKey(1) >= 0)
            break;
    }

    return 0;
}
