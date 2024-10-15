#include "function.hpp"
#include <opencv4/opencv2/opencv.hpp>

Catcher::Catcher() : score(0), ballPosition(0, 0)
{
    camera.open(0);
    if (!camera.isOpened())
    {
        cout << "Tidak bisa membuka kamera" << endl;
        exit(1);
    }
}

void Catcher::run()
{
    Mat frame;
    while (true)
    {
        camera >> frame;
        Checking(frame);
        displayScore(frame);
        imshow("Catcher", frame);
        if (waitKey(30) == 32)
        { // Press space to exit
            break;
        }
    }
}

void Catcher::Checking(Mat &frame)
{
    Mat hsv, lim_color;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(100, 150, 100), Scalar(140, 255, 255), lim_color);

    vector<vector<Point>> kontur;
    findContours(lim_color, kontur, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    x += dx;
    y += dy;

    if (x < 0 || x > frame.cols)
    {
        dx = -dx;
    }
    if (y < 0 || y > frame.rows)
    {
        dy = -dy;
    }

    int low = 0;
    int high_x = frame.cols;
    int high_y = frame.rows;
    int range_x = (high_x - low) + 1;
    int range_y = (high_y - low) + 1;

    for (size_t i = 0; i < kontur.size(); i++)
    {
        Moments m = moments(kontur[i]);
        Point center(m.m10 / m.m00, m.m01 / m.m00);         
        int radius = static_cast<int>(sqrt(m.m00 / CV_PI)); 
        circle(frame, center, radius, Scalar(0, 0, 0), 7);

        ballPosition = Point(x, y);
        if (pointPolygonTest(kontur[i], ballPosition, true) >= 0)
        {
            score++; // Increment score if ball is inside the circle
            x = low + rand() % range_x;
            y = low + rand() % range_y;
        }
    }
    Point center2(x, y);
    circle(frame, center2, radius, Scalar(0, 0, 255), -1);
}

void Catcher::displayScore(Mat &frame)
{
    string scoreText = "SCORE: " + to_string(score);
    putText(frame, scoreText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
}