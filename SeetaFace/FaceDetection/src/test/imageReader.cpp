//
// Created by lup on 17-5-9.
//

#include "imageReader.h"

void imageReader::init()
{
    cap.open(0);
//    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
//    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
}

bool imageReader::nextImage(cv::Mat& image)
{
    cap >> image;
    return image.cols > 0;
}
