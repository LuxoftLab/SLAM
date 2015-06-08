#include <iostream>
#include <random.h>
#include <time.h>
#include <vector>

#include <ceres/ceres.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/shared_ptr.hpp>

struct CostFunctor {

    const double cx, cy, r;

    CostFunctor(const double x, const double y, const double r) :
        cx(x),
        cy(y),
        r(r) {}

    template <typename T> bool operator()(const T* const x, const T* const y, T* residual) const {
        T dx = x[0] - T(cx);
        T dy = y[0] - T(cy);
        residual[0] = T(r) - sqrt(dx * dx + dy * dy);
        return true;
    }

};

typedef ceres::AutoDiffCostFunction<CostFunctor, 1, 1, 1> CostFunction;

const int WIDTH = 400, HEIGHT = 400;
const cv::Point2d POINTS[] = {
    cv::Point(100, 100), cv::Point(WIDTH - 100, HEIGHT - 100), cv::Point(100, HEIGHT - 100),
    cv::Point(WIDTH - 100, 100), cv::Point(WIDTH / 2, 100), cv::Point(100, HEIGHT / 2),
    cv::Point(WIDTH / 2, HEIGHT - 100), cv::Point(WIDTH - 100, HEIGHT / 2)
};
const double measuringError = 0.1;

double inline frand() {
    return 1.0 / (rand() % 100 + 1);
}

int main() {
    cv::Point point;
    cv::Point2d result(1, 1);
    int n;

    std::cout << "Type coords of target point:\nx(0-" << WIDTH << ")=";
    std::cin >> point.x;
    std::cout << "y(0-" << HEIGHT << ")=";
    std::cin >> point.y;
    std::cout << "Type amount of fixed points(3-8):";
    std::cin >> n;
    if(n < 3 || n > 8)
        n = 3;

    srand(time(NULL));

    std::vector<boost::shared_ptr<CostFunctor> > costFunctors;
    std::vector<boost::shared_ptr<ceres::CostFunction> > costFunctions;
    ceres::Problem problem;
    for(int i = 0; i < n; i++) {
        double dx = point.x - POINTS[i].x;
        double dy = point.y - POINTS[i].y;
        double length = sqrt(dx * dx + dy * dy);

        //add random error
        double error = measuringError * frand();
        error *= (1 - 2 * (rand() % 2)); // random sign
        length *= 1 + error;

        boost::shared_ptr<CostFunctor> functor(new CostFunctor(POINTS[i].x, POINTS[i].y, length));
        boost::shared_ptr<ceres::CostFunction> function(new CostFunction(functor.get()));
        problem.AddResidualBlock(function.get(), NULL, &result.x, &result.y);

        costFunctors.push_back(functor);
        costFunctions.push_back(function);
    }

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
    std::cout << "Result: " << std::endl;
    std::cout << "x : " << result.x << " "
              << "y : " << result.y << std::endl;

    cv::Mat img(WIDTH, HEIGHT, CV_8UC3);
    for(int i = 0; i < n; i++) {
        boost::shared_ptr<CostFunctor> &t = costFunctors[i];
        cv::circle(img, cv::Point(t->cx, t->cy), 3, cv::Scalar(0, 180, 0), -1);
        cv::circle(img, cv::Point(t->cx, t->cy), t->r, cv::Scalar(0, 180, 0, 5));
    }
    cv::circle(img, point, 5, cv::Scalar(255, 0, 0), -1);
    cv::circle(img, result, 5, cv::Scalar(0, 0, 255), -1);
    cv::imshow("result", img);
    cv::waitKey();
    return 0;
}

