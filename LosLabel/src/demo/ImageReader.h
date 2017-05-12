//
// Created by lup on 17-5-9.
//

#ifndef SEETA_FACEDET_LIB_IMAGEREADER_H
#define SEETA_FACEDET_LIB_IMAGEREADER_H

#include "opencv2/opencv.hpp"

class ImageReader
{
public:
    ImageReader() {init();}
    ~ImageReader() {}

    bool getImage(cv::Mat& image);

private:
    void init();

private:
    cv::VideoCapture cap;
};

#endif //SEETA_FACEDET_LIB_IMAGEREADER_H
