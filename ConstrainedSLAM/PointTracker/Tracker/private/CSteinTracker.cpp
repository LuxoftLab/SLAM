#include "PointTracker/Tracker/CSteinTracker.hpp"
#include <cmath>

CSteinTracker::CSteinTracker(const int maxPoints)
{
}

bool cmp (cv::Point2f p1, cv::Point2f p2) {
    if(p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y))
        return true;
    return false;
}

void CSteinTracker::compareSignatures(const cv::Mat & img, const cv::Mat & grayImg,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tablePrevFrame,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tableCurrFrame,
                                      const std::vector<cv::Point2f> &prevFeatures)
{
    gFeaturesFoundInTables.clear();
    gFeaturesStatus.clear();
    gCorrespondenceHypotheses.clear();
    gFeatures2FramesAgo.clear();

    int sumSize = 0;

    for(std::map<CTritset, std::vector<cv::Point2f> >::iterator iterTablePrevFrame = tablePrevFrame.begin();
        iterTablePrevFrame != tablePrevFrame.end(); ++iterTablePrevFrame)
    {
        sumSize += iterTablePrevFrame->second.size();
        bool flag = false;
        std::map<CTritset, std::vector<cv::Point2f> >::iterator iterTableCurrFrame = tableCurrFrame.find(iterTablePrevFrame->first);

        if(iterTableCurrFrame != tableCurrFrame.end() && iterTableCurrFrame->second.size() < sMDP)
        {
            for(auto p1 = iterTablePrevFrame->second.begin(); p1 != iterTablePrevFrame->second.end(); p1++)
                for(auto p2 = iterTableCurrFrame->second.begin(); p2 != iterTableCurrFrame->second.end(); p2++)
                {
                    cv::Scalar intensity1 = grayImg.at<uchar>(p1->y, p1->x);
                    cv::Scalar intensity2 = grayImg.at<uchar>(p2->y, p2->x);
                    if(hypot(abs(p1->x - p2->x), abs(p1->y - p2->y)) <= 70
                            && intensity2.val[0]/intensity1.val[0] <= 1.2
                            && intensity2.val[0]/intensity1.val[0] >= 0.8
                            && !flag)
                    {
                        gFeaturesFoundInTables.push_back((*iterTableCurrFrame).second[0]);
                        gFeaturesStatus.push_back(1);
                        gCorrespondenceHypotheses.push_back((*iterTableCurrFrame).second[0]);
                        flag = true;
                    } else {
                        gFeaturesFoundInTables.push_back(cv::Point2f());
                        gFeaturesStatus.push_back(0);
                    }
            }
        } else {
            gFeaturesFoundInTables.push_back(cv::Point2f());
            gFeaturesStatus.push_back(0);
        }
    }

    sumSize -= gFeaturesFoundInTables.size();
    int size = gFeaturesStatus.size();
    gFeaturesFoundInTables.resize(gFeaturesFoundInTables.size()+sumSize);
    gFeaturesStatus.resize(gFeaturesStatus.size()+sumSize);
//    gFeaturesStatus.resize(prevFeatures.size());
    std::fill(gFeaturesStatus.begin()+size,gFeaturesStatus.end(),0);


//    if(frameCounter > 2) {
//        for (auto it = gFeaturesFoundInTables.begin(); it != gFeaturesFoundInTables.end(); it++)
//            for (auto itr = prevFeatures.begin(); itr != prevFeatures.end(); itr++)
//            {
//                if(*it == *itr)
//                {
//                    std::cout << "sdg > fg size = " << gTableCurrFrame.size() << "\n";

//                    gFeatures2FramesAgo.push_back(*it);
//                    break;
//                }
//            }

//        gFeaturesFoundInTables.clear();
//        gFeaturesFoundInTables = gFeatures2FramesAgo;
//    }
}


int CSteinTracker::isFeature(int elem, int sLBP_EPS, int p)
{
    int resChar;
    if (p - elem > sLBP_EPS)
    {
        resChar = 0;
    }
    else if (abs(p - elem) <= sLBP_EPS)
    {
        resChar = 1;
    }
    else if (elem - p > sLBP_EPS)
    {
        resChar = 2;
    }
    return resChar;
}

CTritset CSteinTracker::lbpFeature(const cv::Mat & img, const long long x, const long long y)
{
    CTritset t(sLBP_TRIT_SZ);
    int idx = 0;

    int p = img.at<long long>(x,y);

    for (int i = 0; i < (sLBP_LENS >> 1); i++)
    {
        t[idx++] = isFeature(img.at<long long>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x - (sLBP_LENS >> 1) + i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x + (sLBP_LENS >> 1) - i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x + (sLBP_LENS >> 1) - i, y - (sLBP_LENS >> 1) + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x, y -(sLBP_LENS >> 1)+ i), sLBP_EPS, p);
    }
    return t;
}


void CSteinTracker::makeCandidatesList() { //most frequent features after first frame
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;
    for(p = gTablePrevFrame.begin(); p != gTablePrevFrame.end(); p++) {
        if (p->second.size() > sTO_SET) {
            gListOfCandidates.insert(p->first);
            gTablePrevFrame.erase(p->first);
        }
    }
}

void CSteinTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                                  std::vector<cv::Point2f> & features) {
    std::cout<< "setFirstFrame\n";
    gListOfCandidates.clear();

    std::cout << "setFirstFrame > features size = " << features.size() << "\n";
    std::cout << "setFirstFrame > gListOfCandidates size = " << gListOfCandidates.size() << "\n";

    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;

    for(size_t i = (sLBP_LENS >> 1); i < (grayImg.cols - (sLBP_LENS >> 1) - 1); i++)
    {
        for(size_t j = (sLBP_LENS >> 1); j < (grayImg.rows - (sLBP_LENS >> 1) - 1); j++)
        {

            CTritset temp = CSteinTracker::lbpFeature(grayImg, j, i);
            p = gTablePrevFrame.find(temp);
            cv::Point2f pt;
            pt.x = i;
            pt.y = j;
            if (p!= gTablePrevFrame.end()) //if found
            {
                p->second.push_back(pt);
            }
            else
            {
                gTablePrevFrame[temp].push_back(pt);
            }

        }
    }

    std::cout << "setFirstFrame > gTablePrevFrame size = " << gTablePrevFrame.size() << "\n";

    makeCandidatesList(); //erase features > 10

    std::cout << "setFirstFrame > gListOfCandidates size = " << gListOfCandidates.size() << "\n";
    std::cout << "setFirstFrame > gTablePrevFrame size  = " << gTablePrevFrame.size() << "\n";

    std::vector<cv::Point2f>::iterator i;
    for ( p = gTablePrevFrame.begin(); (p!= gTablePrevFrame.end()); p++)
        for(i = p->second.begin(); i!= p->second.end() ;  i++)
            features.push_back(*i);

    std::cout << "setFirstFrame > features size = " << features.size() << "\n";
    std::cout << "----------------------\n";

    frameCounter++;
}

void CSteinTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                    std::vector<cv::Point2f>& features,
                                    const std::vector<cv::Point2f>& old) {
    std::cout<< "no findNewFeatures\n";

}

void CSteinTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                            const std::vector<cv::Point2f>& prevFeatures,
                                            std::vector<cv::Point2f>& features,
                                            std::vector<uchar>& status){
    std::cout<< "\nfindNewFeaturesPosition \n";
    std::cout << "findNewFeaturesPosition > frameCounter =  "<< frameCounter << "\n";
    std::cout << "findNewFeaturesPosition > prevFeatures size = " << prevFeatures.size() << "\n";

    gTableCurrFrame.clear();

    if (frameCounter < 51) {
        for(size_t i = (sLBP_LENS >> 1); i < (grayImg.cols - (sLBP_LENS >> 1) - 1); i++)
        {
            for(size_t j = (sLBP_LENS >> 1); j < (grayImg.rows - (sLBP_LENS >> 1) - 1); j++)
            {
                CTritset temp = CSteinTracker::lbpFeature(grayImg, j, i);
                if (gListOfCandidates.find(temp) == gListOfCandidates.end()) { //if feature not found at SET of candidates
                    cv::Point2f pt;
                    pt.x = i;
                    pt.y = j;
                    gTableCurrFrame[temp].push_back(pt); //add her into table2 of this frame
                }
            }
        }
        compareSignatures(img, grayImg, gTablePrevFrame,gTableCurrFrame, prevFeatures); //compare first and second frame's tables
        frameCounter++;
    } else {
        frameCounter = 1;
        setFirstFrame(img, grayImg, features);
    }
    std::cout << "\n";
    std::cout << "findNewFeaturesPosition > features size = " << features.size() << "\n";
    std::cout << "findNewFeaturesPosition > gFeaturesFoundInTables size = " << gFeaturesFoundInTables.size() << "\n";
    std::cout << "findNewFeaturesPosition > status size = " << status.size() << "\n";
    std::cout << "findNewFeaturesPosition > gFeaturesStatus size = " << gFeaturesStatus.size() << "\n";
    std::cout << "findNewFeaturesPosition > gTableCurrFrame size = " << gTableCurrFrame.size() << "\n";
    std::cout << "findNewFeaturesPosition > gTablePrevFrame size = " << gTablePrevFrame.size() << "\n";

    features = gFeaturesFoundInTables;
    status = gFeaturesStatus;

    gTablePrevFrame.clear();
    gTablePrevFrame = gTableCurrFrame;

    std::cout << "-------------------------------------\n";
    std::cout << "findNewFeaturesPosition > features size = " << features.size() << "\n";
    std::cout << "findNewFeaturesPosition > gFeaturesFoundInTables size = " << gFeaturesFoundInTables.size() << "\n";
    std::cout << "findNewFeaturesPosition > status size = " << status.size() << "\n";
    std::cout << "findNewFeaturesPosition > gFeaturesStatus size = " << gFeaturesStatus.size() << "\n";
    std::cout << "findNewFeaturesPosition > gTableCurrFrame size = " << gTableCurrFrame.size() << "\n";
    std::cout << "findNewFeaturesPosition > gTablePrevFrame size = " << gTablePrevFrame.size() << "\n";

}


