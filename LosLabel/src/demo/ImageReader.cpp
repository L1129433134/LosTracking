//
// Created by lup on 17-5-9.
//

#include "ImageReader.h"

void ImageReader::init()
{
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
}

bool ImageReader::getImage(cv::Mat& image)
{
    cap >> image;
    return image.cols > 0;
}
