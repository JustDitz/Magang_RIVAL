#ifndef Catch_HPP
#define Catch_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Catcher
{
public:
    Catcher();
    void run();

private:
    VideoCapture camera;
    int score;
    Point ballPosition;

    int buttonRadius;
    int x = 0;
    int y = 0;
    int dx = 7;
    int dy = 7;
    int radius = 10;
    int numballs = 1;
    void displayScore(Mat &frame);
    void Checking(Mat &frame);
};

#endif