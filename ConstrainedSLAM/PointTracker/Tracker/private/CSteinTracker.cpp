#include "PointTracker/Tracker/CSteinTracker.hpp"

CSteinTracker::CSteinTracker()
{
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

CTritset<CSteinTracker::sLBP_TRIT_SZ> CSteinTracker::lbpFeature(const cv::Mat & img, const int64 x, const int64 y)
{
    CTritset <CSteinTracker::sLBP_TRIT_SZ> t;
    int idx = 0;

    int p = img.at<int>(x,y);

    for (int i = 0; i < (sLBP_LENS >> 1); i++)
    {
        t[idx++] = isFeature(img.at<int>(x - (sLBP_LENS >> 1) + i, y - (sLBP_LENS >> 1) + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x - (sLBP_LENS >> 1) + i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x - (sLBP_LENS >> 1) + i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x + (sLBP_LENS >> 1) - i, y + (sLBP_LENS >> 1) - i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x + (sLBP_LENS >> 1) - i, y), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x + (sLBP_LENS >> 1) - i, y + i), sLBP_EPS, p);
        t[idx++] = isFeature(img.at<int>(x, y + i), sLBP_EPS, p);
    }

    return t;
}


void CSteinTracker::toSet() {
    std::map<CTritset<sLBP_TRIT_SZ>, long long>::iterator p;

    for(p = mapFeature.begin(); p != mapFeature.end(); p++) {
        if (p->second > sTO_SET) {
            setFeature.insert(p->first);
            mapFeature.erase(p->first);
        }
      }
}

void CSteinTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                      std::vector<cv::Point2f> & features) {

       for(size_t i = sLBP_LENS >> 1; i < (img.rows - sLBP_LENS >> 1); i++)
       {
           for(size_t j = sLBP_LENS >> 1; j < (img.cols - sLBP_LENS >> 1); j++)
           {

               CTritset<sLBP_TRIT_SZ> temp = CSteinTracker::lbpFeature(img, sLBP_LENS, sLBP_EPS);
               if (mapFeature.find(temp) == mapFeature.end())
               {
                   mapFeature.insert(std::make_pair(temp, 1));
               }
               else
               {
                   mapFeature[temp]++;
               }
           }
       }

   }

void CSteinTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                        std::vector<cv::Point2f>& features,
                        const std::vector<cv::Point2f>& old) {
    std::cout<< "no findNewFeatures";

}

void CSteinTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                const std::vector<cv::Point2f>& prevFeatures,
                                std::vector<cv::Point2f>& features,
                                std::vector<uchar>& status){
  std::cout<< "no findNewFeaturesPosition";
    //TO DO second frame;

}


