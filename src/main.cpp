#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#define VIDEO_INPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/input
#define VIDEO_OUTPUT_FOLDER /Users/egorkirichenko/Projects/C++/video-blur/vid/output

#define FACE_DETECT_FOLDER "/Users/egorkirichenko/Projects/C++/video-blur/models/face_detection_yunet_2023mar.onnx"
#define SCORE_THRESHOLD 0.9
#define NMS_THRESHOLD 0.3 
#define TOP_K 5000
#define BACKEND_ID 0
#define TARGET_ID 0

#define DEVICE_ID 0
#define API_ID cv::CAP_ANY

int main() {
    // cv::Mat frame;
    // cv::VideoCapture cap;
    // std::vector<cv::Rect> faces;
    // auto faceDetect = cv::FaceDetectorYN::create(FACE_DETECT_FOLDER, "", cv::Size(320, 320), SCORE_THRESHOLD, NMS_THRESHOLD, TOP_K, BACKEND_ID, TARGET_ID);

    // cap.open(DEVICE_ID, API_ID);

    // if(!cap.isOpened()) {
    //     std::cout << "ERROR! opening main camera!\n";
    //     return -1;
    // }

    // std::cout << "start grabbing" << std::endl 
    //         << "Press any key to terminate" << std::endl;

    // for (;;) {
    //     cap.read(frame);

    //     if(frame.empty()) {
    //         std::cout << "Frame reading error!";
    //         break;
    //     }

    //     faceDetect->detect(frame, faces);
    //     std::cout << "Detected faces: " << faces.size() << std::endl;

    //     for (cv::Rect face : faces) {
    //         cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    //     }

    //     cv::imshow("Live", frame);
    //     cv::waitKey(1);
    // }

    auto detector = cv::FaceDetectorYN::create(FACE_DETECT_FOLDER, "", cv::Size(320, 320));

    // Read image
    cv::Mat img = cv::imread("/Users/egorkirichenko/Projects/C++/video-blur/vid/input/test.jpg");
    if (img.empty()) {
        std::cerr << "Could not read the image!" << std::endl;
        return -1;
    }

    // Get image shape
    int img_W = img.cols;
    int img_H = img.rows;

    // Set input size
    detector->setInputSize(cv::Size(img_W, img_H));

    // Getting detections
    // std::vector<cv::Mat> detections;
    cv::Mat detections;
    detector->detect(img, detections);

    for (int i = 0; i < detections.rows; ++i) {
        // Печатаем координаты прямоугольников лиц
        float x = detections.at<float>(i, 0);
        float y = detections.at<float>(i, 1);
        float w = detections.at<float>(i, 2);
        float h = detections.at<float>(i, 3);
        std::cout << "Лицо " << i + 1 << ": [" << x << ", " << y << ", " << w << ", " << h << "]" << std::endl;

        // Рисуем прямоугольник вокруг лица
        cv::rectangle(img, cv::Rect(cv::Point(x, y), cv::Size(w, h)), cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("aeasd", img);
    cv::waitKey(0);

    return 0;
}


// #include<opencv2/imgcodecs.hpp>
// #include<opencv2/highgui.hpp>
// #include<opencv2/imgproc.hpp>
// #include<opencv2/objdetect.hpp>
// #include<iostream>

// using namespace std;
// using namespace cv;

// /*void main() {
// 	string path = "chando.jpg";
// 	Mat	img = imread(path);
// 	imshow("Frame", img);
// 	waitKey(0);
// }*/

// int main() {
// 	VideoCapture video(0);
// 	CascadeClassifier facedetect;
// 	Mat img;
// 	facedetect.load("/Users/egorkirichenko/Projects/C++/video-blur/src/haarcascade_frontalface_default.xml");
	
// 	while (true) {
// 		video.read(img);

// 		vector<Rect> faces;

// 		facedetect.detectMultiScale(img, faces, 1.3, 5);

// 		cout << faces.size() << endl;

// 		for (int i = 0; i < faces.size(); i++) {
// 			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
// 			rectangle(img, Point(0,0), Point(250,70), Scalar(50, 50, 255), FILLED);
// 			putText(img, to_string(faces.size())+" Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
// 		}

		
// 		imshow("Frame", img);
// 		waitKey(1);
		

// 	}
// }