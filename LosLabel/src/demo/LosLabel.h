//
// Created by lup on 17-5-13.
//

#ifndef LOSLABEL_LOSLABEL_H
#define LOSLABEL_LOSLABEL_H

#include "opencv2/opencv.hpp"
#include "Timer.h"

namespace
{
    const std::string CC_LABEL_APPLICATION = "labelApplication";
    const std::string CC_LOS_TRACKING = "LosTracking";
    const std::string CC_LABEL_TIME = "labelTime";
    const std::string CC_LOSLABELS = "losLabels";
    const std::string CC_LOSLABEL = "losLabel";

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
    const std::string CC_NO_GLASSES = "no-glasses";
    const std::string CC_HAVE_GLASSES = "have-glasses";
    const std::string CC_CONTACT_LENSES = "Contact-lenses";

    // eyeColor
    const std::string CC_BALCK_EYES = "black-eyes";
    const std::string CC_BLUE_EYES = "blue-eyes";

    // eyeSize
    const std::string CC_SMALL_EYES = "small-eyes";
    const std::string CC_NORMAL_EYES = "normal-eyes";
    const std::string CC_BIG_EYES = "big-eyes";

    // skinColor
    const std::string CC_YELLOW_SKIN = "yellow-skin";
    const std::string CC_WHITE_SKIN = "white-skin";
    const std::string CC_BLACK_SKIN = "black-skin";

    // lightIntensity
    const std::string CC_BRIGHT = "bright";
    const std::string CC_GLARING = "glaring";
    const std::string CC_RAYLESS = "rayless";

    // machineType
    const std::string CC_LAPTOP = "laptop";

    // machineName
    const std::string CC_Hasee_Z8 = "Hasee-Z8-KP7S1";

    // cameraPosition;
    const std::string CC_UPPER_CENTER = "upper-center";

    // cameraResolution
    const std::string CC_1080P = "1080P";
    const std::string CC_720P = "720P";
}

struct LosLabelAttributes
{
    std::string gender;
    std::string age;
    std::string glasses;
    std::string eyeColor;
    std::string eyeSize;
    std::string skinColor;
    std::string lightIntensity;

    std::string collector;
    std::string locality;
    std::string dataAndTime;

    std::string machineType;
    std::string machineName;
    std::string cameraPosition;
    std::string cameraResolution;

    std::string remarks;
};

class LosLabel
{
public:
    LosLabel()
    {
        focusRange = cv::Rect(0, 0, 1000, 1000);
    }
    ~LosLabel() {}

    void setImageName(const std::string& _imageName) {imageName = _imageName;}
    void setFaceWindow(const cv::Rect& _faceWindow) {faceWindow = _faceWindow;}
    void setKeysLocation(const std::vector<cv::Point>& _keysLocation)
    {
        assert(_keysLocation.size() == 5);
        keysLocation = _keysLocation;
    }
    void setFocus(const cv::Point& _focus)
    {
        assert(_focus.x >= focusRange.x && _focus.x < focusRange.x + focusRange.width);
        assert(_focus.y >= focusRange.y && _focus.y < focusRange.y + focusRange.height);
        focus = _focus;
    }
    void setFocusRange(const cv::Rect& _focusRange) {focusRange = _focusRange;}
    void setFocusRange(const cv::Point& lt, const cv::Point& rb) {focusRange = cv::Rect(lt,rb);}
    void setAttributes(const LosLabelAttributes& _attributes);

    std::string getImageName() const {return imageName;}
    cv::Rect getfaceWindow() const {return faceWindow;}
    std::vector<cv::Point> getKeysLocation() const { return keysLocation;}
    cv::Point getFocus() { return focus;}
    LosLabelAttributes getAttributes() const { return attributes;}
    cv::Rect getFocusRange() const { return focusRange;}

    bool check();
    void write(cv::FileStorage& fs) const;
    void read();
    void writeAttributes();
    void readAttributes();

private:
    std::string             imageName;
    cv::Rect                faceWindow;
    std::vector<cv::Point>  keysLocation;
    cv::Point               focus;

    LosLabelAttributes      attributes;
    cv::Rect                focusRange;
};

class LosLabels
{
public:
    LosLabels() {}
    ~LosLabels() {}

    void push_back(const LosLabel& losLabel)
    {
        labels.push_back(losLabel);
    }
    LosLabel pop_back();
    void clear() {labels.clear();}
    size_t size() { return labels.size();}

    bool write(const std::string& fileName);
    bool read(const std::string& fileName);

    LosLabels find() {}     // use lambda

private:
    std::vector<LosLabel> labels;
    DateAndTime dateAndTime;
};

#endif //LOSLABEL_LOSLABEL_H
