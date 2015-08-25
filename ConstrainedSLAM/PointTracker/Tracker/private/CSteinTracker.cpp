#include "PointTracker/Tracker/CSteinTracker.hpp"
#include <cmath>

#define DEBUG(v) std::cout << #v << " " << v << "\n";
#define MSG(v) std::cout << v << "\n";

CSteinTracker::CSteinTracker(const int maxPoints)
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

bool cmp (cv::Point2f p1, cv::Point2f p2) {
    if(p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y))
        return true;
    return false;
}

void CSteinTracker::compareSignatures(const cv::Mat & img, const cv::Mat & grayImg,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tablePrevFrame,
                                      std::map<CTritset, std::vector<cv::Point2f> > & tableCurrFrame,
                                      const std::vector<cv::Point2f> &prevFeatures,
                                      std::vector<cv::Point2f> &features,
                                      std::vector<uchar> &status)
{
    MSG("compareSignatures start");
    std::map<CTritset, std::vector<cv::Point2f> >::iterator iterTablePrev, iterTableCurr;
    DEBUG(gTritsetPrev->size());
    DEBUG(prevFeatures.size());
    int sz = gTritsetPrev->size();
    for(int i = 0; i < sz; i++)
    {
        iterTableCurr = tableCurrFrame.find(gTritsetPrev->at(i));
        if(iterTableCurr != tableCurrFrame.end())
        {
            iterTablePrev = tablePrevFrame.find(gTritsetPrev->at(i));
            bool flag = 0;
            if(iterTablePrev != tablePrevFrame.end())
            {
                /*std::cout << "    ->" << prevFeatures[i].x << " " << prevFeatures[i].y << " [" << gTritsetPrev[i] << "] := \n";
                for(auto p2 = iterTableCurr->second.rbegin(); p2 != iterTableCurr->second.rend(); p2++)
                {
                    std::cout << p2->x << " " << p2->y <<"\n";
                }*/
                for(auto p2 = iterTableCurr->second.rbegin(); p2 != iterTableCurr->second.rend(); p2++)
                {
                    cv::Scalar intensity1 = grayImg.at<uchar>(prevFeatures[i].y, prevFeatures[i].x);
                    cv::Scalar intensity2 = grayImg.at<uchar>(p2->y, p2->x);
                    if(hypot(abs(prevFeatures[i].x - p2->x), abs(prevFeatures[i].y - p2->y)) <= 20
                            && intensity2.val[0]/intensity1.val[0] <= 1.2
                            && intensity2.val[0]/intensity1.val[0] >= 0.8)
                    {
//                        std::cout << prevFeatures[i].x << " " << prevFeatures[i].y << "->>" <<
//                                p2->x << " " << p2->y << "\n";
                        status.push_back(1);
                        gTritsetCur->push_back(gTritsetPrev->at(i));
                        features.push_back(*p2);
                        flag = 1;
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
    std::cout << "compareSignatures end\n";
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

    long long p = img.at<uchar>(x,y);
    for (int i = 0; i < (sLBP_LENS >> 1); i++)
    {
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x + (sLBP_LENS >> 1) - i, y - (sLBP_LENS >> 1) + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<uchar>(x, y -(sLBP_LENS >> 1)+ i), sLBP_EPS, p);
    }
    return t;
}


void CSteinTracker::makeCandidatesList() { //most frequent features after first frame
    DEBUG(gTablePrevFrame->size());
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;
    for(p = gTablePrevFrame->begin(); p != gTablePrevFrame->end(); p++) {
        if (p->second.size() > sTO_SET) {
            gListOfCandidates.insert(p->first);
            gTablePrevFrame->erase(p->first);
        }
    }
    DEBUG(gTablePrevFrame->size());
    DEBUG(gListOfCandidates.size());
}

void CSteinTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                                  std::vector<cv::Point2f> & features) {
    std::cout<< "setFirstFrame\n";
    gTablePrevFrame->clear();
    gListOfCandidates.clear();
    gTritsetPrev->clear();

    cv::Mat imgBlur;
    cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);
    //cvSmooth();
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;

    for(size_t i = (sLBP_LENS >> 1); i < (grayImg.cols - (sLBP_LENS >> 1) - 1); i++)
    {
        for(size_t j = (sLBP_LENS >> 1); j < (grayImg.rows - (sLBP_LENS >> 1) - 1); j++)
        {

            CTritset temp = CSteinTracker::lbpFeature(imgBlur, j, i);
            p = gTablePrevFrame->find(temp);
            cv::Point2f pt;
            pt.x = i;
            pt.y = j;
            if(p == gTablePrevFrame->end())
                gTablePrevFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
            gTablePrevFrame->at(temp).push_back(pt);

        }
    }

    makeCandidatesList(); //erase features > 10

    std::vector<cv::Point2f>::iterator i;
    for ( p = gTablePrevFrame->begin(); (p!= gTablePrevFrame->end()); p++)
    {
        for(i = p->second.begin(); i!= p->second.end() ;  i++)
        {
            features.push_back(*i);
            gTritsetPrev->push_back((*p).first);
            break;
        }
    }
    frameCounter++;
}

void CSteinTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                    std::vector<cv::Point2f>& features,
                                    const std::vector<cv::Point2f>& old) {

}

void CSteinTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                            const std::vector<cv::Point2f>& prevFeatures,
                                            std::vector<cv::Point2f>& features,
                                            std::vector<uchar>& status){
    //MSG("FindNewFeaturesPosition start");
    std::cout << "FindNewFeaturesPosition start\n";

    cv::Mat imgBlur;
    cv::GaussianBlur(grayImg, imgBlur, cv::Size(3,3), 0);
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;

    if (frameCounter < 51) {
        for(size_t i = (sLBP_LENS >> 1); i < (grayImg.cols - (sLBP_LENS >> 1) - 1); i++)
        {
            for(size_t j = (sLBP_LENS >> 1); j < (grayImg.rows - (sLBP_LENS >> 1) - 1); j++)
            {
                CTritset temp = CSteinTracker::lbpFeature(imgBlur, j, i);
                if (gListOfCandidates.find(temp) == gListOfCandidates.end())
                { //if feature not found at SET of candidates
                    p = gTableCurrFrame->find(temp);
                    cv::Point2f pt;
                    pt.x = i;
                    pt.y = j;
                    if(p == gTableCurrFrame->end())
                        gTableCurrFrame->insert(make_pair(temp, std::vector <cv::Point_<float> >()));
                    gTableCurrFrame->at(temp).push_back(pt);
                    //gTableCurrFrame[temp].push_back(pt); //add her into table2 of this frame
                }
            }
        }
        compareSignatures(img, imgBlur, *gTablePrevFrame, *gTableCurrFrame, prevFeatures, features, status); //compare first and second frame's tables
        frameCounter++;
    } else {
        frameCounter = 1;
        setFirstFrame(img, grayImg, features);
    }

//    gTablePrevFrame.clear();
//    gTablePrevFrame = gTableCurrFrame;

    std::swap(gTablePrevFrame, gTableCurrFrame);
    gTableCurrFrame->clear();

    DEBUG(gTableCurrFrame->size());
    DEBUG(gTablePrevFrame->size());
    std::cout << "FindNewFeaturesPosition end\n";
}


