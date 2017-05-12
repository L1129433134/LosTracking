//
// Created by lup on 17-5-13.
//

#ifndef LOSLABEL_LOSLABEL_H
#define LOSLABEL_LOSLABEL_H

#include "opencv2/opencv.hpp"

namespace
{
    // gender
    const std::string CC_MAN = "man";
    const std::string CC_WOMAN = "woman";

    // age
    const std::string CC_CHILD = "child";
    const std::string CC_YOUNG = "young";
    const std::string CC_YOUTH = "youth";
    const std::string CC_MIDDLEAGED = "middle-aged";
    const std::string CC_ELDERLY = "elderly";

    // glasses
    const std::string CC_NO_GLASSES = "no glasses";
    const std::string CC_HAVE_GLASSES = "have glasses";
    const std::string CC_CONTACT_LENSES = "Contact lenses";

    // eyeColor
    const std::string CC_BALCK_EYES = "black eyes";
    const std::string CC_BLUE_EYES = "blue eyes";

    // eyeSize
    const std::string CC_SMALL_EYES = "small eyes";
    const std::string CC_NORMAL_EYES = "normal eyes";
    const std::string CC_BIG_EYES = "big eyes";

    // skinColor
    const std::string CC_YELLOW_SKIN = "yellow skin";
    const std::string CC_WHITE_SKIN = "white skin";
    const std::string CC_BLACK_SKIN = "black skin";

    // lightIntensity
    const std::string CC_BRIGHT = "bright";
    const std::string CC_GLARING = "glaring";
    const std::string CC_RAYLESS = "rayless";
}

class LosLabelAttributes
{
public:
    std::string gender;
    std::string age;
    std::string glasses;
    std::string eyeColor;
    std::string eyeSize;
    std::string skinColor;
    std::string lightIntensity;
};

class LosLabel
{
public:
    LosLabel();
    ~LosLabel();

    bool writeLabel();
    bool readLabel();

private:
    std::string             imageName;
    cv::Rect                faceWindow;
    std::vector<cv::Point>  keysLocation;
    cv::Point               focus;

    LosLabelAttributes attributes;
};


#endif //LOSLABEL_LOSLABEL_H
