
#include <map>
#include <list>
#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ceres/ceres.h>

#include "matrices.h"
#include "Common/LogUtils/CProfiler.hpp"


struct Functor {
   double x, y;

   Functor(double x, double y) :
      x(x),
      y(y)
   {
   }

   template<typename T>
   bool operator()(T const * r, T const * t, T const * p, T* residuals) const {

      START_PROFILING("functor");
      matrix<T> rotation = getRotationMatrix<T>(r[0], r[1], r[2]);
      matrix<T> transition = getTranslationMatrix<T>(t[0], t[1], t[2]);
      matrix<T> point2d = get2DPointMatrix<T>(rotation, transition, get3DPointMatrix<T>(p[0], p[1], p[2]));
      if(point2d(2,0) == T(0))
      {
         residuals[0] = residuals[1] = T(0);
      }
      else
      {
         residuals[0] = T(x) - point2d(0,0)/point2d(2, 0);
         residuals[1] = T(y) - point2d(1,0)/point2d(2,0);
      }
      return true;
   }
};

struct ConstCamera {
   double x, y;

   ConstCamera(double x, double y) :
      x(x),
      y(y)
   {
   }

   template<typename T>
   bool operator()(T const * p, T* residuals) const {

      START_PROFILING("const camera");
      matrix<T> rotation = getRotationMatrix<T>(T(0), T(0), T(0));
      matrix<T> transition = getTranslationMatrix<T>(T(0), T(0), T(0));
      matrix<T> point2d = get2DPointMatrix<T>(rotation, transition, get3DPointMatrix<T>(p[0], p[1], p[2]));
      if(point2d(2,0) == T(0))
      {
         residuals[0] = residuals[1] = T(0);
      }
      else
      {
         residuals[0] = T(x) - point2d(0,0)/point2d(2, 0);
         residuals[1] = T(y) - point2d(1,0)/point2d(2,0);
      }
      return true;
   }
};
#define PATH "/home/gorz/luxoft/SLAM-input/rotation-1956/"
int main()
{
   typedef ceres::AutoDiffCostFunction<Functor, 2, 3, 3, 3> tCostFunction;
   typedef ceres::AutoDiffCostFunction<ConstCamera, 2, 3> tConstCameraCostFunction;
   initCalibrationMatrix(PATH "calibration.txt");
   std::ifstream points3d(PATH "points3d.txt");
   std::ifstream points2d(PATH "points2d.txt");
   int nPointds3d;
   points3d >> nPointds3d;
   double * points = new double[3*nPointds3d];
   for(int i = 0; i < nPointds3d; i++)
   {
      points3d >> points[3*i] >> points[3*i + 1] >> points[3*i + 2];
      points[3*i] = points[3*i + 1] = points[3*i + 2] = 1;
   }
   int nFrames;
   points2d >> nFrames;


   double *rotation= new double[3*nFrames];
   double *transition = new double[3*nFrames];

   ceres::Problem problem;
   for(int f = 0; f < nFrames; f++)
   {
      rotation[3*f] = 0;
      rotation[3*f+1] = 0;
      rotation[3*f+2] = 0;
      transition[3*f] = 0;
      transition[3*f+1] = 0;
      transition[3*f+2] = 0;
      int nPoints;
      points2d >> nPoints;
      for(int i = 0; i < nPoints; i++)
      {
         int p;
         double x, y;
         points2d >> p >> x >> y;
         if(f == 0)
         {
            ConstCamera * functor = new ConstCamera(x, y);
            tConstCameraCostFunction * function = new tConstCameraCostFunction(functor);
            problem.AddResidualBlock(function, NULL, &points[3*p]);
         } else
         {
            Functor * functor = new Functor(x, y);
            tCostFunction * function = new tCostFunction(functor);
            problem.AddResidualBlock(function, NULL, &rotation[3*f], &transition[3*f], &points[3*p]);
         }


      }


   }
   std::cout << "Solving..." << std::endl;
   ceres::Solver::Options options;
  // options.minimizer_progress_to_stdout = true;
   ceres::Solver::Summary summary;
   {
      START_PROFILING("solving");
      ceres::Solve(options, &problem, &summary);
   }
   std::cout << "Solved" << std::endl;
   for(int f = 0; f < nFrames; f++)
   {
      std::cout << "Camera " << f << std::endl
                << "Rotation: ";
      for(int i = 0; i < 3; i++)
         std::cout << rotation[3*f+i] << ' ';
      std::cout << std::endl << "Transition: ";
      for(int i = 0; i < 3; i++)
         std::cout << transition[3*f+i] << ' ';
      std::cout << std::endl;
      std::cout << std::endl;
   }
   return 0;
}
