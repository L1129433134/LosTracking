#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"
#include "ImageReader.h"
#include "Timer.h"
#include "EyesDetector.h"

#define SHOW_TIME
const std::string WIN_NAME = "imgColor";

int main(int argc, char** argv)
{
    // Initialize eyes detector
    EyesDetector eyesDetector;

    //load image
    ImageReader reader;
    cv::Mat img, img_gray;
    reader.getImage(img);


#ifdef SHOW_TIME
    Timer timer;
    long time;
    std::vector<long> times;
#endif // SHOW_TIME

    std::vector<cv::Rect> faces;
    std::vector<std::vector<cv::Point>> keys;
    while(!img.empty())
    {
#ifdef SHOW_TIME
        timer.timingStart();
        double tt = cv::getTickCount();
#endif // SHOW_TIME
        // Detect faces
        int faceNum = eyesDetector.eyesDetect(img, faces, keys);
#ifdef SHOW_TIME
        tt = cv::getTickCount() - tt;
        time = timer.timingStop();
        std::cout<<"timer: "<<time<<" ms"<<std::endl;
        std::cout<<"opencv: "<<tt * 1000 / cv::getTickFrequency()<<" ms"<<std::endl<<std::endl;
        times.push_back(time);
#endif // SHOW_TIME

        if (faceNum == 0)
        {
            continue;
        }

        for (int i = 0; i < faceNum; ++i)
        {
            cv::rectangle(img, faces[i], CV_RGB(255, 0, 0));
            for (int j = 0; j < 5; ++j)
            {
                cv::circle(img, keys[i][j], 2, CV_RGB(0, 255, 0), CV_FILLED);
            }
        }

        cv::imshow(WIN_NAME, img);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        reader.getImage(img);
    }

#ifdef SHOW_TIME
    long total = 0, mean;
    for (auto p : times)
    {
        total += p;
    }

    mean = total / times.size();
    std::cout<<"Face Detection Cost mean: "<<mean<<" ms!"<<std::endl;
#endif // SHOW_TIME

    std::cout<<"end!!"<<std::endl;
    return 0;
}
