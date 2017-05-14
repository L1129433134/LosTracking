//
// Created by lup on 17-5-12.
//

#include "EyesDetector.h"
#include <string>
#include <vector>

namespace{
    const std::string FaceDetectionModelName = "../model/seeta_fd_frontal_v1.0.bin";
    const std::string KeysDetectionModelName = "../model/seeta_fa_v1.1.bin";
}

EyesDetector::EyesDetector() : m_faceDetector(FaceDetectionModelName.c_str()),
                               m_keysDetector(KeysDetectionModelName.c_str())
{
    m_minFaceSize = 200;
    m_faceDetector.SetMinFaceSize(m_minFaceSize);
    m_faceDetector.SetScoreThresh(2.f);
    m_faceDetector.SetImagePyramidScaleFactor(0.8f);
    m_faceDetector.SetWindowStep(4, 4);
}

int EyesDetector::faceDetect(const cv::Mat& image, std::vector<cv::Rect>& faces)
{
    cv::Mat imgGray;
    if (image.channels() != 1) {
        cv::cvtColor(image, imgGray, CV_BGR2GRAY);
    }
    else {
        imgGray = image;
    }

    m_imgData.data = imgGray.data;
    m_imgData.width = imgGray.cols;
    m_imgData.height = imgGray.rows;
    m_imgData.num_channels = 1;

    std::vector<seeta::FaceInfo> facesInfo = m_faceDetector.Detect(m_imgData);

    faces.clear();
    for (auto p : facesInfo)
    {
        if (p.bbox.width > m_minFaceSize)
        {
            faces.push_back(cv::Rect(p.bbox.x, p.bbox.y, p.bbox.width, p.bbox.height));
        }
    }
    return faces.size();
}

int EyesDetector::eyesDetect(const cv::Mat& image, std::vector<cv::Rect>& faces, std::vector<std::vector<cv::Point>>& keys)
{
    cv::Mat imgGray;
    if (image.channels() != 1) {
        cv::cvtColor(image, imgGray, CV_BGR2GRAY);
    } else {
        imgGray = image;
    }

    m_imgData.data = imgGray.data;
    m_imgData.width = imgGray.cols;
    m_imgData.height = imgGray.rows;
    m_imgData.num_channels = 1;

    std::vector<seeta::FaceInfo> facesInfo;
    facesInfo = m_faceDetector.Detect(m_imgData);

    seeta::FacialLandmark points[5];
    std::vector<cv::Point> temp;
    faces.clear();
    keys.clear();
    for (auto p : facesInfo)
    {
        if (p.bbox.width > m_minFaceSize)
        {
            faces.push_back(cv::Rect(p.bbox.x, p.bbox.y, p.bbox.width, p.bbox.height));

            m_keysDetector.PointDetectLandmarks(m_imgData, p, points);
            temp.clear();
            for (int j = 0; j < 5; ++j)
            {
                temp.push_back(cv::Point(static_cast<int>(points[j].x), static_cast<int>(points[j].y)));
            }
            keys.push_back(temp);
        }
    }

    return faces.size();
}
