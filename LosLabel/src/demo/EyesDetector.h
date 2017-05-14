//
// Created by lup on 17-5-12.
//

#ifndef LOSLABEL_EYESDETECTOR_H
#define LOSLABEL_EYESDETECTOR_H

#include "FaceDetectionInc/face_detection.h"
#include "FaceAlignmentInc/face_alignment.h"
#include "opencv2/opencv.hpp"

class EyesDetector
{
public:
    EyesDetector();
    ~EyesDetector() {}

    int faceDetect(const cv::Mat& image, std::vector<cv::Rect>& faces);
    int eyesDetect(const cv::Mat& image, std::vector<cv::Rect>& faces, std::vector<std::vector<cv::Point>>& keys);

private:
    seeta::FaceDetection m_faceDetector;
    seeta::FaceAlignment m_keysDetector;

    int                 m_minFaceSize;
    seeta::ImageData    m_imgData;
};


#endif //LOSLABEL_EYESDETECTOR_H
