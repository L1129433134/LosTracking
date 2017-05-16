//
// Created by lup on 17-5-13.
//

#include "LosLabel.h"

//----------------------------LosLabel----------------------------------------------------------------------------------
void LosLabel::write(cv::FileStorage& fs) const
{
    fs << CC_LOSLABEL;
    fs << "{";

    fs << "imageName" <<imageName;
    fs << "faceWindow" << "[";
    fs << faceWindow.x << faceWindow.y << faceWindow.width << faceWindow.height;
    fs << "]";

    fs << "keysLocation" << "[";
    for (int i = 0; i < keysLocation.size(); ++i)
    {
        fs << keysLocation[i].x << keysLocation[i].y;
    }
    fs << "]";

    fs << "focus" << "[";
    fs << focus.x << focus.y;
    fs << "]";

    fs << "}";
}







//----------------------------LosLabels---------------------------------------------------------------------------------
bool LosLabels::write(const std::string& fileName)
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
    if (!fs.isOpened())
    {
        std::cout<<"Unable open "<<fileName<<"!\n";
        return false;
    }

    dateAndTime.reinit();
    std::string dataStr = dateAndTime.getString();

    fs << CC_LABEL_APPLICATION << CC_LOS_TRACKING;
    fs << CC_LABEL_TIME << dataStr;

    fs << CC_LOSLABELS;
    fs << "{";
    for (int i = 0; i < labels.size(); ++i)
    {
        labels[i].write(fs);
    }
    fs << "}";

    fs.release();
    return true;
}