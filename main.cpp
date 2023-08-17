#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include<cmath>
#include <vector>
#include <ctime>
using namespace cv;

bool exists (std::vector<Vec3b> parameters, Vec3b color) {
    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i] == color) {
            return true;
        }
        else if (parameters.empty()) {
            return false;
        }
        return false;
    }
}

Vec3b min(Mat& img, std::vector<Vec3b> parameters, int y, int x) {
    Vec3b color = img.at<Vec3b>(y, x);
    long long R = 255, G = 255, B = 255;

    for (int i = 0; i < parameters.size() * 2; i++) {
        if (i < parameters.size()) {
            parameters[i][0] = std::abs(color[0] - parameters[i][0]);
            parameters[i][1] = std::abs(color[1] - parameters[i][1]);
            parameters[i][2] = std::abs(color[2] - parameters[i][2]);
        }
        else {
            if (R > (parameters[i % 2][0])) {
                R = parameters[i % 2][0];
                color[0] = parameters[i % 2][0];
            }
            if (G > (parameters[i % 2][1])) {
                G = parameters[i % 2][1];
                color[1] = parameters[i % 2][1];
            }
            if (B > (parameters[i % 2][2])) {
                B = parameters[i % 2][2];
                color[2] = parameters[i % 2][2];
            }
        }
    }
    
    return color;
}

int main(int argc, char** argv) {
    cv::Mat img = cv::imread("C:/Users/sophia/Downloads/052cb3d36f96044f517eebb038346b28.jpg");
    //cv::Mat img = cv::imread("C:/Users/sophia/Downloads/frog-1280x720.png");
    std::srand(std::time(0));

    int x = img.cols, y = img.rows;
    int amount = 0;
    std::vector<Vec3b> parameters;

    std::cout << "How many colors: ";
    std::cin >> amount;

    while (parameters.size() < amount) {
        Vec3b color = img.at<Vec3b>(std::rand() % y, std::rand() % x);

        if (parameters.empty() || !exists(parameters, color)) {
            parameters.push_back(color);
            std::cout << color << " ";
        }
    }

    // Until here
    for (int i = 0; i < amount; i++) {

        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                Vec3b color = min(img, parameters, y, x);
                img.at<Vec3b>(y, x)[0] = std::abs(color[0] - img.at<Vec3b>(y, x)[0]);
                img.at<Vec3b>(y, x)[1] = std::abs(color[1] - img.at<Vec3b>(y, x)[1]);
                img.at<Vec3b>(y, x)[2] = std::abs(color[2] - img.at<Vec3b>(y, x)[2]);
            }
        }
    }

    std::vector<Vec3b> cores;
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    // cv::imwrite("C:/Users/sophia/Desktop/test" + std::to_string(1) + "FORMAT", img);

    return 0;
}