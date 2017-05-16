#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"
#include "ImageReader.h"
#include "Timer.h"
#include "EyesDetector.h"
#include "LosLabel.h"

#define SHOW_TIME
const std::string WIN_NAME = "imgColor";

int main(int argc, char** argv)
{
    // Initialize eyes detector
    EyesDetector eyesDetector;

    // LosLabels
    LosLabels losLabels;
    LosLabel losLabel;

    //load image
    ImageReader reader;
    cv::Mat img, img_gray;
    reader.getImage(img);

#ifdef SHOW_TIME
    Timer timer;
    double time;
    std::vector<double> times;
#endif // SHOW_TIME

    std::vector<cv::Rect> faces;
    std::vector<std::vector<cv::Point>> keys;
    while(!img.empty())
    {
#ifdef SHOW_TIME
        time = timer.stop();
#endif // SHOW_TIME
        // Detect faces
        int faceNum = eyesDetector.eyesDetect(img, faces, keys);
#ifdef SHOW_TIME
        time = timer.stop() - time;
        std::cout<<"timer: "<<time<<" ms"<<std::endl;
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
            losLabel.setFaceWindow(faces[i]);
            losLabel.setImageName("test");
            losLabel.setKeysLocation(keys[i]);
            losLabel.setFocus(cv::Point(100,100));
            losLabels.push_back(losLabel);
        }

        cv::imshow(WIN_NAME, img);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        reader.getImage(img);
    }

#ifdef SHOW_TIME
    double total = 0, mean;
    for (auto p : times)
    {
        total += p;
    }

    mean = total / times.size();
    std::cout<<"Face Detection Cost mean: "<<mean<<" ms!"<<std::endl;
#endif // SHOW_TIME

    losLabels.write("test.xml");
    std::cout<<"end!!"<<std::endl;
    return 0;
}
