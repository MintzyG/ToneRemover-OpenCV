#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <filesystem>
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

int distance(Vec3b color1, Vec3b color2) {
    int x, y, z;
    x = (int)std::pow((double)(color1[0] - color2[0]), 2);
    y = (int)std::pow((double)(color1[1] - color2[1]), 2);
    z = (int)std::pow((double)(color1[2] - color2[2]), 2);
    return (int)std::sqrt((x + y + z));
}

Vec3b magnitude(Mat& img, std::vector<Vec3b> parameters, int imgY, int imgX, std::vector<std::vector<int>>& matI) {
    Vec3b color = img.at<Vec3b>(imgY, imgX);
    int magnitude = 442, lesser = 442, pos = 0;
    for (int i = 0; i < parameters.size(); i++) {
        magnitude = distance(parameters[i], color);
        if (magnitude < lesser) {
            lesser = magnitude;
            pos = i;
        }
        else if (magnitude == 0) {
            matI[imgY][imgX] = i;
            return parameters[i];
        }
    }
    matI[imgY][imgX] = pos;
    return parameters[pos];
}

int contador = 0;

bool colorCounter(Mat img, std::vector<Vec3b>& parameters, std::vector<std::vector<int>> matI) {
    std::vector<std::vector<int>> Acumulados;
    std::vector<Vec3b> novasCores;
    std::vector<int>  colorCounter;
    bool Improve = false;

    Acumulados.reserve(parameters.size());
    for (int i = 0; i < parameters.size(); i++) {
        std::vector<int> vec;
        for (int i = 0; i < 3; i++) {
            vec.push_back(0);
        }
        Acumulados.push_back(vec);
    }

    for (int i = 0; i < parameters.size(); i++) {
        colorCounter.push_back(0);
    }

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            colorCounter[matI[i][j]] += 1;
            Acumulados[matI[i][j]][0] += (int)img.at<Vec3b>(i, j)[0];
            Acumulados[matI[i][j]][1] += (int)img.at<Vec3b>(i, j)[1];
            Acumulados[matI[i][j]][2] += (int)img.at<Vec3b>(i, j)[2];
        }
    }

    contador += 1;
    novasCores.reserve(parameters.size());
    for (int i = 0; i < parameters.size(); i++) {
        novasCores[i][0] = Acumulados[i][0] / colorCounter[i];
        novasCores[i][1] = Acumulados[i][1] / colorCounter[i];
        novasCores[i][2] = Acumulados[i][2] / colorCounter[i];
        if (distance(novasCores[i], parameters[i]) > 5) {
            Improve = true;
        }
    }

    for (int i = 0; i < parameters.size(); i++) {
        parameters[i] = novasCores[i];
    }

    return Improve;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < sizeof(argv[1]); i++) {
        if (argv[1][i] == (0x5c)) {
            argv[1][i] = '/';
        }
    }

    if (argc > 0) {
        cv::Mat img = cv::imread(argv[1]);
        cv::Mat fImg = cv::imread(argv[1]);
        std::vector<Vec3b> parameters;
        int x = img.cols, y = img.rows, amount = 0;

        std::vector<std::vector<int>> matI;
        matI.reserve(y);
        for (int i = 0; i < y; i++) {
            std::vector<int> vec;
            vec.reserve(x);
            for (int j = 0; j < x; j++) {
                vec.push_back(j);
            }
            matI.push_back(vec);
        }

        std::srand((int)std::time(0));
        std::cout << "How many colors: ";
        std::cin >> amount;
   
        while (parameters.size() < amount) {
            Vec3b color = img.at<Vec3b>(std::rand() % y, std::rand() % x);
            if (parameters.empty() || !exists(parameters, color)) 
                parameters.push_back(color);
        }

        do {
            for (int y = 0; y < img.rows; y++) {
                for (int x = 0; x < img.cols; x++) {
                    fImg.at<Vec3b>(y, x) = magnitude(img, parameters, y, x, matI);
                }
            }

            bool Improve = colorCounter(img, parameters, matI);
            if (Improve) {
                continue;
            }
            else {
                for (int y = 0; y < img.rows; y++) {
                    for (int x = 0; x < img.cols; x++) {
                        img.at<Vec3b>(y, x) = magnitude(img, parameters, y, x, matI);
                    }
                }
                break;
            }
        } while (true);
 
        std::filesystem::path path = std::filesystem::current_path();
        std::string output = path.string();
        output += "/ToneChangerOutput.png";

        namedWindow("Resultado", WINDOW_AUTOSIZE);
        cv::imshow("Resultado", img);
        cv::moveWindow("Resultado", 0, 45);
        cv::waitKey(0);
        cv::destroyAllWindows();
        cv::imwrite(output, img);

        return 0;
    }
}
