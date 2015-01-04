#include <opencv2/opencv.hpp>
#include <vector>

#define IN
#define OUT

class PointTrack {
    //путь точки (тут вопрос, надо хранить весь путь или только по последним двум кадрам?)
    std::vector<cv::Point> points;
};

class SensorData {
    //описание данных с сенсоров машины
};

class ITracker {
public:
    void setFirstFrame(IN cv::Mat& frame, OUT std::vector<cv::Point>& fetures) = 0;
    void findNewFeaturesPosition(IN cv::Mat& frame, IN std::vector<cv::Point>& prevFetures,
                                 OUT std::vector<cv::Point>& fetures) = 0;
};

class IFilter {
public:
    /*
        previous, current - точки с предыдущего и текущеко кадра
        filtered -  маска, которая описывает какие из точек следует учитывать при обработке
    */
    void filter(IN std::vector<cv::Point>& previous, IN std::vector<cv::Point>& current,
                IN SensorData& sensors, OUT std::vector<bool>& filtered) = 0;
};

class IPointTracker {
public:
    //установка кадра относительно которого будут тречится точки
    void setFirstFrame(IN cv::Mat& frame) = 0;
    //поиск точек на новом фрейме и обновление их трэка
    void processFrame(IN cv::Mat& frame, IN SensorData& sensors,
                      OUT std::vector<PointTrack>& tracks) = 0;
};
