#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cstdlib>
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

Vec3b magnitude(Vec3b cor, std::vector<Vec3b> parameters) {
    int x, y, z, magnitude, lesser = 442, pos = 0;
    for (int i = 0; i < parameters.size(); i++) {
        x = (int)std::pow((double)(parameters[i][0] - cor[0]), 2);
        y = (int)std::pow((double)(parameters[i][1] - cor[1]), 2);
        z = (int)std::pow((double)(parameters[i][2] - cor[2]), 2);
        magnitude = (int)std::sqrt(x + y + z);
        if (magnitude < lesser) {
            lesser = magnitude;
            pos = i;
        }
    }
    return parameters[pos];
}

Vec3b min(Mat& img, std::vector<Vec3b> parameters, int y, int x) {
    Vec3b color = img.at<Vec3b>(y, x);
    for (int i = 0; i < parameters.size(); i++) {
        if (i < parameters.size()) {
            parameters[i][0] = std::abs(color[0] - parameters[i][0]);
            parameters[i][1] = std::abs(color[1] - parameters[i][1]);
            parameters[i][2] = std::abs(color[2] - parameters[i][2]);
        }
        return magnitude(color, parameters);
    }
    return color;
}

int main(int argc, char** argv) {
    cv::Mat img = cv::imread("C:/Users/sophia/Downloads/frog-1280x720.png");
    std::srand((int)std::time(0));
    int x = img.cols, y = img.rows, amount = 0;
    std::vector<Vec3b> parameters;
    std::cout << "How many colors: ";
    std::cin >> amount;

    while (parameters.size() < amount) {
        Vec3b color = img.at<Vec3b>(std::rand() % y, std::rand() % x);
        if (parameters.empty() || !exists(parameters, color)) {
            parameters.push_back(color);
        }
    }

    for (int i = 0; i < amount; i++) {
        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                Vec3b color = min(img, parameters, y, x);
                img.at<Vec3b>(y, x) = color;
            }
        }
    }

    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    // cv::imwrite("C:/Users/sophia/Desktop/test" + std::to_string(1) + "FORMAT", img);
    return 0;
}