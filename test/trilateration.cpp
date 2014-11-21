#include <iostream>
#include <random.h>
#include <time.h>

#include <ceres/ceres.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

using namespace std;
using namespace cv;

struct CostFunctor {
    CostFunctor(double x, double y, double r) : cx(x),cy(y),r(r) {}
    template <typename T> bool operator()(const T* const x, const T* const y, T* residual) const {
        T dx = x[0]-T(cx);
        T dy = y[0]-T(cy);
        residual[0] = T(r)-sqrt(dx*dx+dy*dy);
        return true;
    }
    const double cx, cy, r;
};

const int WIDTH=400, HEIGHT = 400;

const Point2d POINTS[] = {
    Point(100, 100), Point(WIDTH-100, HEIGHT-100), Point(100, HEIGHT-100),
    Point(WIDTH-100, 100), Point(WIDTH/2, 100), Point(100, HEIGHT/2),
    Point(WIDTH/2, HEIGHT-100), Point(WIDTH-100, HEIGHT/2)
};
const double measuringError = 0.1; //measure error

double frand() {
    return 1.0/(rand()%100+1);
}

int main() {
    Point point;
    Point2d result(1, 1);
    int n;

    cout << "Type coords of target point:\nx(0-" << WIDTH << ")=";
    cin >> point.x;
    cout << "y(0-" << HEIGHT << ")=";
    cin >> point.y;
    cout << "Type amount of fixed points(3-8):";
    cin >> n;
    if(n<3 || n>8) n = 3;

    srand(time(NULL));
    Problem problem;
    CostFunctor** costFunctors = new CostFunctor*[n];
    for(int i=0; i<n; i++) {
        double dx = point.x - POINTS[i].x;
        double dy = point.y - POINTS[i].y;
        double length = sqrt(dx*dx+dy*dy);
        length *= (1+measuringError*((-1)*rand()%2)*frand()); //add random error;
        costFunctors[i] = new CostFunctor(POINTS[i].x, POINTS[i].y, length);
        CostFunction* cost_function =
                new AutoDiffCostFunction<CostFunctor, 1, 1, 1>(costFunctors[i]);
        problem.AddResidualBlock(cost_function, NULL, &result.x, &result.y);
    }

    Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, &problem, &summary);

    cout << summary.BriefReport() << endl;
    cout << "Result: " << endl;
    cout << "x : " << result.x << " "
         << "y : " << result.y << endl;

    Mat img(WIDTH, HEIGHT, CV_8UC3);
    for(int i=0; i<n; i++) {
        CostFunctor *t = costFunctors[i];
        circle(img, Point(t->cx, t->cy), 3, Scalar(0, 180, 0), -1);
        circle(img, Point(t->cx, t->cy), t->r, Scalar(0, 180, 0, 5));
    }
    circle(img, point, 5, Scalar(255, 0, 0), -1);
    circle(img, result, 5, Scalar(0, 0, 255), -1);
    imshow("result", img);
    waitKey();
    return 0;
}
