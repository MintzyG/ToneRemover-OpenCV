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
        if (parameters[i] == color) 
            return true;
        else if (parameters.empty())
            return false;
        return false;
    }
    return false;
}

Vec3b magnitude(Mat& img, std::vector<Vec3b> parameters, int imgY, int imgX) {
    Vec3b color = img.at<Vec3b>(imgY, imgX);
    int x, y, z, magnitude = 442, lesser = 442, pos = 0;
    for (int i = 0; i < parameters.size(); i++) {
        x = (int)std::pow((double)(parameters[i][0] - color[0]), 2);
        y = (int)std::pow((double)(parameters[i][1] - color[1]), 2);
        z = (int)std::pow((double)(parameters[i][2] - color[2]), 2);
        magnitude = (int)std::sqrt((x + y + z));
        if (magnitude < lesser) {
            lesser = magnitude;
            pos = i;
        }
        else if (magnitude == 0)
            return parameters[i];
    }
    return parameters[pos];
}

int main(int argc, char** argv) {
    cv::Mat img = cv::imread("PATH_TO_FILE");
    std::vector<Vec3b> parameters;
    int x = img.cols, y = img.rows, amount = 0;
    std::srand((int)std::time(0));
    std::cout << "How many colors: ";
    std::cin >> amount;

    while (parameters.size() < amount) {
        Vec3b color = img.at<Vec3b>(std::rand() % y, std::rand() % x);
        if (parameters.empty() || !exists(parameters, color)) 
            parameters.push_back(color);
    }

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            img.at<Vec3b>(y, x) = magnitude(img, parameters, y, x);
        }
    }
 
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    cv::imwrite("PATH/FILENAME.EXTENSION", img);
    return 0;
}