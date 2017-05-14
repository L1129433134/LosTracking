//
// Created by lup on 17-5-9.
//

#include "ImageReader.h"

void ImageReader::init()
{
    cap.open(0);
    if (!cap.isOpened())
    {
        std::cout<<"Unable open camera 0!!!"<<std::endl;
    }
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
}

bool ImageReader::getImage(cv::Mat& image)
{
    assert(cap.isOpened());
    cap >> image;
    return image.cols > 0;
}
