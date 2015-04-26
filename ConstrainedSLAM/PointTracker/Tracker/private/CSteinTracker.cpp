#include "PointTracker/Tracker/CSteinTracker.hpp"

CSteinTracker::CSteinTracker()
{
}

void CSteinTracker::compareMaps(std::map<CTritset, std::vector<cv::Point2f> > & m1,
                                std::map<CTritset, std::vector<cv::Point2f> > & m2)
{

   for(std::map<CTritset, std::vector<cv::Point2f> >::iterator m1_iter = m1.begin(); m1_iter != m1.end(); ++m1_iter)
   {

    std::map<CTritset, std::vector<cv::Point2f> >::iterator m2_iter = m2.find(m1_iter->first);
    if(m2_iter != m2.end())
    {
        hypoCor.push_back((*m2_iter).second[0]);
        featuresStatus.push_back('1');
    }
    else
    {
        featuresStatus.push_back('0');
    }
   }

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
        t[idx++] = isFeature(img.at<long long>(x + (sLBP_LENS >> 1) - i, y + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<long long>(x, y + i), sLBP_EPS, p);
    }
    return t;
}


void CSteinTracker::toSet() {
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;

    for(p = featuresMap.begin(); p != featuresMap.end(); p++) {
        if (p->second.size() > sTO_SET) {
            featuresSet.insert(p->first);
            featuresMap.erase(p->first);
        }
    }
}

void CSteinTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                                  std::vector<cv::Point2f> & features) {
    featuresSet.clear();
    std::map<CTritset, std::vector<cv::Point2f> >::iterator p;
    for(size_t i = sLBP_LENS >> 1; i < (img.rows - sLBP_LENS >> 1); i++)
    {
        for(size_t j = sLBP_LENS >> 1; j < (img.cols - sLBP_LENS >> 1); j++)
        {

            CTritset temp = CSteinTracker::lbpFeature(img, i, j);
            if ((p = featuresMap.find(temp)) != featuresMap.end())
            {
                cv::Point2f pt;
                pt.x = i;
                pt.y = j;
                p->second.push_back(pt);
            }
            else
            {
                cv::Point2f pt;
                pt.x = i;
                pt.y = j;
                featuresMap[temp].push_back(pt);
            }
            cv::Point2f pt;
            pt.x = i;
            pt.y = j;
            features.push_back(pt);

        }
    }
    toSet();
    frameCounter++;
}

void CSteinTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                    std::vector<cv::Point2f>& features,
                                    const std::vector<cv::Point2f>& old) {
    std::cout<< "no findNewFeatures \n";

}

void CSteinTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                            const std::vector<cv::Point2f>& prevFeatures,
                                            std::vector<cv::Point2f>& features,
                                            std::vector<uchar>& status){
    if (frameCounter < 51) {
        for(size_t i = sLBP_LENS >> 1; i < (img.rows - sLBP_LENS >> 1); i++)
        {
            for(size_t j = sLBP_LENS >> 1; j < (img.cols - sLBP_LENS >> 1); j++)
            {
                CTritset temp = CSteinTracker::lbpFeature(img, sLBP_LENS, sLBP_EPS);
                if (featuresSet.find(temp) == featuresSet.end()) {
                    cv::Point2f pt;
                    pt.x = i;
                    pt.y = j;
                        featuresMapTemp[temp].push_back(pt);
                }
            }
        }
        frameCounter++;
    } else {
        setFirstFrame(img, grayImg, features);
        frameCounter = 1;
    }
    features = hypoCor;
    status = featuresStatus;
}


