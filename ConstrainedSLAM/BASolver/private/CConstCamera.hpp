#ifndef CCONST_CAMERA_HPP
#define CCONST_CAMERA_HPP

#include "AFunctor.hpp"

class CConstCamera : public AFunctor {
private:
   typedef ceres::AutoDiffCostFunction<CConstCamera, 2, 3> tCostFunction;

public:
   CConstCamera(const CScene3D::tPointPtr & point,
                const CScene3D::tCameraPtr & camera,
                const PointTrack::tPoint2fPtr & point2D);
   CConstCamera(const AFunctor * functor);

   ceres::ResidualBlockId bindToProblem(const tProblemPtr & problem);

   template<typename T>
   bool operator()(const T * position, T * residuals) const
   {
      T rotation[4][4];
      T translation[] = {T(mCamera->position[0]), T(mCamera->position[1]),
                        T(mCamera->position[2])};
      T quaternion[] = {T(mCamera->rotation[0]), T(mCamera->rotation[1]),
                        T(mCamera->rotation[2]), T(mCamera->rotation[3])};
      quaternionToMatrix<T>(quaternion, rotation);
      T x = ((T(mCalibration[0][0])) * (rotation[0][0]) + (T(mCalibration[0][2])) * (rotation[2][0])) * (position[0]) + ((T(mCalibration[0][0])) * (rotation[0][1]) + (T(mCalibration[0][2])) * (rotation[2][1])) * (position[1]) + ((T(mCalibration[0][0])) * (rotation[0][2]) + (T(mCalibration[0][2])) * (rotation[2][2])) * (position[2]) + (T(mCalibration[0][0])) * ((rotation[0][0]) * (translation[0]) + (rotation[0][1]) * (translation[1]) + (rotation[0][2]) * (translation[2])) + (T(mCalibration[0][2])) * ((rotation[2][0]) * (translation[0]) + (rotation[2][1]) * (translation[1]) + (rotation[2][2]) * (translation[2]));
      T y = ((T(mCalibration[1][1])) * (rotation[1][0]) + (T(mCalibration[1][2])) * (rotation[2][0])) * (position[0]) + ((T(mCalibration[1][1])) * (rotation[1][1]) + (T(mCalibration[1][2])) * (rotation[2][1])) * (position[1]) + ((T(mCalibration[1][1])) * (rotation[1][2]) + (T(mCalibration[1][2])) * (rotation[2][2])) * (position[2]) + (T(mCalibration[1][1])) * ((rotation[1][0]) * (translation[0]) + (rotation[1][1]) * (translation[1]) + (rotation[1][2]) * (translation[2])) + (T(mCalibration[1][2])) * ((rotation[2][0]) * (translation[0]) + (rotation[2][1]) * (translation[1]) + (rotation[2][2]) * (translation[2]));
      T t = ((T(mCalibration[2][2])) * (rotation[2][0])) * (position[0]) + ((T(mCalibration[2][2])) * (rotation[2][1])) * (position[1]) + ((T(mCalibration[2][2])) * (rotation[2][2])) * (position[2]) + (T(mCalibration[2][2])) * ((rotation[2][0]) * (translation[0]) + (rotation[2][1]) * (translation[1]) + (rotation[2][2]) * (translation[2]));
      if(t == T(0))
      {
         residuals[0] = residuals[1] = T(0);
      }
      else
      {
         residuals[0] = T(mPoint2D->x) - x/t;
         residuals[1] = T(mPoint2D->y) - y/t;
      }
      return true;
   }
};

#endif // CCONST_CAMERA_HPP

