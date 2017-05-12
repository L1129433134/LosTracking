/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
 *
 * This file is an example of how to use SeetaFace engine for face alignment, the
 * face alignment method described in the following paper:
 *
 *
 *   Coarse-to-Fine Auto-Encoder Networks (CFAN) for Real-Time Face Alignment,
 *   Jie Zhang, Shiguang Shan, Meina Kan, Xilin Chen. In Proceeding of the
 *   European Conference on Computer Vision (ECCV), 2014
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developed by Jie Zhang (a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

#include "FaceDetectionInc/face_detection.h"
#include "FaceAlignmentInc/face_alignment.h"
#include "imageReader.h"

#define SHOW_TIME
const std::string WIN_NAME = "imgColor";

int main(int argc, char** argv)
{
    // Initialize face detection model
    seeta::FaceDetection detector("../model/seeta_fd_frontal_v1.0.bin");
    detector.SetMinFaceSize(200);
    detector.SetScoreThresh(2.f);
    detector.SetImagePyramidScaleFactor(0.8f);
    detector.SetWindowStep(4, 4);

    // Initialize face alignment model
    seeta::FaceAlignment point_detector("../model/seeta_fa_v1.1.bin");

    //load image
    imageReader reader;
    cv::Mat img, img_gray;
    reader.getImage(img);

#ifdef SHOW_TIME
    double time;
    std::vector<double> times1, times2;
#endif // SHOW_TIME

    while(!img.empty()) {
        if (img.channels() != 1)
            cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
        else
            img_gray = img;

        seeta::ImageData img_data;
        img_data.data = img_gray.data;
        img_data.width = img_gray.cols;
        img_data.height = img_gray.rows;
        img_data.num_channels = 1;

        // Detect faces
#ifdef SHOW_TIME
        time = cv::getTickCount();
#endif // SHOW_TIME
        std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);
#ifdef SHOW_TIME
        time = (cv::getTickCount() - time) / cv::getTickFrequency() * 1000;
        std::cout<<"detector.Detect: "<<time<<" ms"<<std::endl;
        times1.push_back(time);
#endif // SHOW_TIME

        int32_t face_num = static_cast<int32_t>(faces.size());
        if (face_num == 0)
        {
            continue;
        }

        seeta::FacialLandmark points[5];
#ifdef SHOW_TIME
        time = cv::getTickCount();
#endif // SHOW_TIME
        point_detector.PointDetectLandmarks(img_data, faces[0], points);
#ifdef SHOW_TIME
        time = (cv::getTickCount() - time) / cv::getTickFrequency() * 1000;
        std::cout<<"detector.Detect: "<<time<<" ms"<<std::endl;
        times2.push_back(time);
#endif // SHOW_TIME

        cv::rectangle(img, cv::Point(faces[0].bbox.x, faces[0].bbox.y),
                      cv::Point(faces[0].bbox.x + faces[0].bbox.width - 1, faces[0].bbox.y + faces[0].bbox.height - 1), CV_RGB(255, 0, 0));
        for (int i = 0; i < 5; i++)
        {
            cv::circle(img, cv::Point(points[i].x, points[i].y), 2, CV_RGB(0, 255, 0), CV_FILLED);
        }
        cv::imshow(WIN_NAME, img);
        if (cv::waitKey(1) == 'q')
        {
            break;
        }

        reader.getImage(img);
    }

#ifdef SHOW_TIME
    double total1 = 0.0, total2 = 0.0, mean1, mean2;
    for (auto p : times1)
    {
        total1 += p;
    }
    for (auto p : times2)
    {
        total2 += p;
    }
    mean1 = total1 / times1.size();
    mean2 = total2 / times2.size();
    std::cout<<"Face Detection Cost mean: "<<mean1<<" ms!"<<std::endl;
    std::cout<<"Face Alignment Cost mean: "<<mean2<<" ms!"<<std::endl;
#endif // SHOW_TIME

    std::cout<<"end!!"<<std::endl;
    return 0;
}
