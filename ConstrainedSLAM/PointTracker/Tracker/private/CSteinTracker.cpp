#include "PointTracker/Tracker/CSteinTracker.hpp"
#include <cmath>


CSteinTracker::CSteinTracker(int maxPoints)
{
    gTritsetPrev = new std::vector <CTritset>();
    gTritsetCur = new std::vector <CTritset>();
    gTablePrevFrame = new std::map<CTritset, std::vector<cv::Point2f> >();
    gTableCurrFrame = new std::map<CTritset, std::vector<cv::Point2f> >();
}

CSteinTracker::~CSteinTracker()
{
    delete gTritsetPrev;
    delete gTritsetCur;
    delete gTableCurrFrame;
    delete gTablePrevFrame;
}


void CSteinTracker::compareSignatures(const cv::Mat & img, const cv::Mat & grayImg,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tablePrevFrame,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tableCurrFrame,
                                      const std::vector<cv::Point2f> &prevFeatures,
                                      std::vector<cv::Point2f> &features,
                                      std::vector<uchar> &status)
{
    __LOG_MSG("compareSignatures start");
    __LOG_VAL(gTritsetPrev->size());
    __LOG_VAL(prevFeatures.size());

    std::map<CTritset, std::vector<cv::Point2f> >::iterator iterTablePrev, iterTableCurr;

    size_t gTritsetPrevSize = gTritsetPrev->size();
    for(int i = 0; i < gTritsetPrevSize; i++)
    {
        iterTableCurr = tableCurrFrame.find(gTritsetPrev->at(i));
        if(iterTableCurr != tableCurrFrame.end())
        {
            iterTablePrev = tablePrevFrame.find(gTritsetPrev->at(i));
            bool flag = 0;
            if(iterTablePrev != tablePrevFrame.end())
            {
                for(auto p2 = iterTableCurr->second.rbegin(); p2 != iterTableCurr->second.rend(); p2++)
                {
                    cv::Scalar intensity1 = grayImg.at<uchar>(prevFeatures[i].y, prevFeatures[i].x);
                    cv::Scalar intensity2 = grayImg.at<uchar>(p2->y, p2->x);
                    if(hypot(abs(prevFeatures[i].x - p2->x), abs(prevFeatures[i].y - p2->y)) <= 20
                            && intensity2.val[0]/intensity1.val[0] <= 1.2
                            && intensity2.val[0]/intensity1.val[0] >= 0.8)
                    {
                        status.push_back(1);
                        gTritsetCur->push_back(gTritsetPrev->at(i));
                        features.push_back(*p2);
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag)
            {
                status.push_back(0);
                features.push_back(cv::Point2f());
            }
        }
        else
        {
            status.push_back(0);
            features.push_back(cv::Point2f());
        }
    }
    std::swap(gTritsetPrev, gTritsetCur);
    gTritsetCur->clear();

    __LOG_MSG("compareSignatures end");
}


int CSteinTracker::isFeature(int elem, int p)
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

bool CSteinTracker::notEnoughMemory(int x, int y)
{
    if(x < (sLBP_LENS + (sLBP_LENS >> 1) - 1) || y < (sLBP_LENS + (sLBP_LENS >> 1)))
        return true;
    return false;
}


void CSteinTracker::lbpFeatureColRow(const cv::Mat & img)
{
    CTritset t(sLBP_TRIT_SZ);
    int idx = 0;

    for(int ind = (sLBP_LENS >> 1); ind < (sCol - (sLBP_LENS >> 1) - 1); ind++)
    {
        int y = ind;
        int x = (sLBP_LENS >> 1);
        long long p = img.at<uchar>((sLBP_LENS >> 1), ind);
        for (int i = 0; i < (sLBP_LENS >> 1); i++)
        {
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), p);
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y), p);
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y - (sLBP_LENS >> 1) + i), p);
            t[idx++] = isFeature(img.at<uchar>(x, y -(sLBP_LENS >> 1)+ i), p);
        }
        gFeatureQueue[(sLBP_LENS >> 1)][ind] = t;
        idx = 0;
    }

    for(int ind = (sLBP_LENS >> 1); ind < (sRow - (sLBP_LENS >> 1) - 1); ind++)
    {
        int x = ind;
        int y = (sLBP_LENS >> 1);
        long long p = img.at<uchar>(ind, (sLBP_LENS >> 1));
        for (int i = 0; i < (sLBP_LENS >> 1); i++)
        {
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), p);
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y), p);
            t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y), p);
            t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y - (sLBP_LENS >> 1) + i), p);
            t[idx++] = isFeature(img.at<uchar>(x, y -(sLBP_LENS >> 1)+ i), p);
        }
        gFeatureQueue[ind][(sLBP_LENS >> 1)] = t;
        idx = 0;
    }
}

CTritset CSteinTracker::lbpFeature(const cv::Mat & img, const long long x, const long long y)
{
    CTritset t(sLBP_TRIT_SZ);
    int idx = 0;

    long long p = img.at<uchar>(x,y);
    for (int i = 0; i < (sLBP_LENS >> 1); i++)
    {
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), p);
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y), p);
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), p);
        t[idx++] = isFeature(img.at<uchar>(x, y + (sLBP_LENS >> 1) - i), p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y), p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y - (sLBP_LENS >> 1) + i), p);
        t[idx++] = isFeature(img.at<uchar>(x, y -(sLBP_LENS >> 1)+ i), p);
    }
    return t;
}


void CSteinTracker::lbpFeatureOptimized(const cv::Mat & img)
{
    int x, y, idx, temp1, temp2, temp3, temp4, p;

    lbpFeatureColRow(img);

    for(size_t i = (sLBP_LENS >> 1) + 1; i < (sCol - (sLBP_LENS >> 1) - 1); i++)
    {
        for(size_t j = (sLBP_LENS >> 1) + 1; j < (sRow - (sLBP_LENS >> 1) - 1); j++)
        {
            idx = 0;

            x = j;
            y = i;

            p = img.at<uchar>(x,y);

            for (int k = 0; k < (sLBP_LENS >> 1); k++)
            {
                temp1 = x - (sLBP_LENS >> 1) + k;
                temp2 = y - (sLBP_LENS >> 1) + k;
                temp3 = y + (sLBP_LENS >> 1) - k;
                temp4 = x + (sLBP_LENS >> 1) - k;

                idx = 0;
                if(notEnoughMemory(x, y)) // calculate position for optimization
                {
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp1, temp2), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp1, y), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp1, temp3), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(x, temp3), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, temp3), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, y), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, temp2), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(x, temp2), p);
                }
                else
                {
                    idx = 3 + (k << 3);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(x, temp3), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, temp3), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, y), p);
                    gFeatureQueue[x][y][idx++] = isFeature(img.at<uchar>(temp4, temp2), p);
                }

                //other neighbors features

                gFeatureQueue[x][temp3][(k+1) << 3] = isFeature(p, img.at<uchar>(x, temp3));
                gFeatureQueue[temp4][temp3][(k << 3) + 1] = isFeature(p, img.at<uchar>(temp4, temp3));
                gFeatureQueue[temp4][y][(k << 3) + 2] = isFeature(p, img.at<uchar>(temp4, y));
                gFeatureQueue[temp4][temp2][(k << 3) + 3] = isFeature(p, img.at<uchar>(temp4, temp2));
            }
        }
    }
}


void CSteinTracker::makeCandidatesList() //most frequent features after first frame
{
    __LOG_MSG("makeCandidatesList start");
    __LOG_VAL(gTablePrevFrame->size());

    std::map<CTritset, std::vector<cv::Point2f> >::iterator itr;
    for(itr = gTablePrevFrame->begin(); itr != gTablePrevFrame->end(); itr++)
    {
        if (itr->second.size() > sTO_SET)
        {
            gListOfCandidates.insert(itr->first);
            gTablePrevFrame->erase(itr->first);
        }
    }

    __LOG_VAL(gTablePrevFrame->size());
    __LOG_VAL(gListOfCandidates.size());
    __LOG_MSG("makeCandidatesList end");
}

void CSteinTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                                  std::vector<cv::Point2f> & features)
{
    __LOG_MSG("setFirstFrame");

    gTablePrevFrame->clear();
    gListOfCandidates.clear();
    gTritsetPrev->clear();

    //cv::Mat imgBlur;
    //cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);

    std::map<CTritset, std::vector<cv::Point2f> >::iterator itr;

    for(size_t i = (sLBP_LENS >> 1) + 1; i < (sCol - (sLBP_LENS >> 1) - 1); i++)
    {
        for(size_t j = (sLBP_LENS >> 1) + 1; j < (sRow - (sLBP_LENS >> 1) - 1); j++)
        {

            CTritset temp = CSteinTracker::lbpFeature(grayImg, j, i);
            itr = gTablePrevFrame->find(temp);
            cv::Point2f pt;
            pt.x = i;
            pt.y = j;
            if(itr == gTablePrevFrame->end())
                gTablePrevFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
            gTablePrevFrame->at(temp).push_back(pt);

        }
    }

    makeCandidatesList();

    std::vector<cv::Point2f>::iterator i;
    for (itr = gTablePrevFrame->begin(); (itr != gTablePrevFrame->end()); itr++)
    {
        for(i = itr->second.begin(); i != itr->second.end() ; i++)
        {
            features.push_back(*i);
            gTritsetPrev->push_back((*itr).first);
            break;
        }
    }
    frameCounter++;
}

void CSteinTracker::setFirstFrameOptimized(const cv::Mat & img, const cv::Mat & grayImg,
                   std::vector<cv::Point2f> & features)
{
    __LOG_MSG("setFirstFrameOptimized");

    gTablePrevFrame->clear();
    gListOfCandidates.clear();
    gTritsetPrev->clear();

    //cv::Mat imgBlur;
    //cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);

    std::map<CTritset, std::vector<cv::Point2f> >::iterator itr;

    CSteinTracker::lbpFeatureOptimized(grayImg);

    for(size_t i = (sLBP_LENS >> 1); i < (sCol - (sLBP_LENS >> 1) - 1); i++)
    {
        for(size_t j = (sLBP_LENS >> 1); j < (sRow - (sLBP_LENS >> 1) - 1); j++)
        {

            CTritset temp = gFeatureQueue[j][i];
            itr = gTablePrevFrame->find(temp);
            cv::Point2f pt;
            pt.x = i;
            pt.y = j;
            if(itr == gTablePrevFrame->end())
                gTablePrevFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
            gTablePrevFrame->at(temp).push_back(pt);

        }
    }

    makeCandidatesList();

    std::vector<cv::Point2f>::iterator i;
    for (itr = gTablePrevFrame->begin(); itr != gTablePrevFrame->end(); itr++)
    {
        for(i = itr->second.begin(); i != itr->second.end() ;  i++)
        {
            features.push_back(*i);
            gTritsetPrev->push_back((*itr).first);
            break;
        }
    }
    frameCounter++;
}


void CSteinTracker::findNewFeaturesPositionOptimized(const cv::Mat & img,const cv::Mat & grayImg,
                                            const std::vector<cv::Point2f>& prevFeatures,
                                            std::vector<cv::Point2f>& features,
                                            std::vector<uchar>& status)
{
    __LOG_MSG("FindNewFeaturesPositionOptimized start");

    //cv::Mat imgBlur;
    //cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);

    std::map<CTritset, std::vector<cv::Point2f> >::iterator itr;

    lbpFeatureOptimized(grayImg);

    if (frameCounter % 50) {
        for(size_t i = (sLBP_LENS >> 1); i < (sCol - (sLBP_LENS >> 1) - 1); i++)
        {
            for(size_t j = (sLBP_LENS >> 1); j < (sRow - (sLBP_LENS >> 1) - 1); j++)
            {
                CTritset temp = gFeatureQueue[j][i];
                if (gListOfCandidates.find(temp) == gListOfCandidates.end())
                {
                    itr = gTableCurrFrame->find(temp);
                    cv::Point2f pt;
                    pt.x = i;
                    pt.y = j;
                    if(itr == gTableCurrFrame->end())
                        gTableCurrFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
                    gTableCurrFrame->at(temp).push_back(pt);
                }
            }
        }
        compareSignatures(img, grayImg, *gTablePrevFrame, *gTableCurrFrame, prevFeatures, features, status);
        //compare first and second frame's tables

        frameCounter++;
    } else {
        //frameCounter = 0;

        return;
       // features.clear();
       // setFirstFrameOptimized(img, grayImg, features);
    }

    std::swap(gTablePrevFrame, gTableCurrFrame);
    gTableCurrFrame->clear();

    __LOG_VAL(gTableCurrFrame->size());
    __LOG_VAL(gTablePrevFrame->size());
    __LOG_MSG("FindNewFeaturesPositionOptimized end");
}

void CSteinTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                    std::vector<cv::Point2f>& features,
                                    const std::vector<cv::Point2f>& old) {

}

void CSteinTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                            const std::vector<cv::Point2f>& prevFeatures,
                                            std::vector<cv::Point2f>& features,
                                            std::vector<uchar>& status)
{
    __LOG_MSG("FindNewFeaturesPosition start");

    //cv::Mat imgBlur;
    //cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);

    std::map<CTritset, std::vector<cv::Point2f> >::iterator itr;

    if (frameCounter % 50) {
        for(size_t i = (sLBP_LENS >> 1) + 1; i < (sCol - (sLBP_LENS >> 1) - 1); i++)
        {
            for(size_t j = (sLBP_LENS >> 1) + 1; j < (sRow - (sLBP_LENS >> 1) - 1); j++)
            {
                CTritset temp = CSteinTracker::lbpFeature(grayImg, j, i);
                if (gListOfCandidates.find(temp) == gListOfCandidates.end())
                { //if feature not found at SET of candidates
                    itr = gTableCurrFrame->find(temp);
                    cv::Point2f pt;
                    pt.x = i;
                    pt.y = j;
                    if(itr == gTableCurrFrame->end())
                        gTableCurrFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
                    gTableCurrFrame->at(temp).push_back(pt);
                }
            }
        }
        compareSignatures(img, grayImg, *gTablePrevFrame, *gTableCurrFrame, prevFeatures, features, status);
        //compare first and second frame's tables
        frameCounter++;
    } else {
       // frameCounter = 1;
        return;
        //setFirstFrame(img, grayImg, features);
    }


    std::swap(gTablePrevFrame, gTableCurrFrame);
    gTableCurrFrame->clear();

    __LOG_VAL(gTableCurrFrame->size());
    __LOG_VAL(gTablePrevFrame->size());
    __LOG_MSG("FindNewFeaturesPosition end");
}

