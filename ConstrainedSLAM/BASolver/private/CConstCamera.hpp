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
      return true;
   }
};

#endif // CCONST_CAMERA_HPP

