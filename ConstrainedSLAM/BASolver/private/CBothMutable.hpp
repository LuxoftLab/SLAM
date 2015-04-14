#ifndef CBOTH_MUTABEL_HPP
#define CBOTH_MUTABEL_HPP

#include "AFunctor.hpp"

class CBothMutable : public AFunctor {
private:
   typedef ceres::AutoDiffCostFunction<CBothMutable, 2, 4, 3, 3> tCostFunction;

public:
   CBothMutable(const CScene3D::tPointPtr & point,
                const CScene3D::tCameraPtr & camera,
                const PointTrack::tPoint2fPtr & point2D);

   ceres::ResidualBlockId bindToProblem(const tProblemPtr & problem);

   template<typename T>
   bool operator()(const T * rotation, const T * translation,
                   const T * position, T * residuals) const
   {
      T x;
      T y;
      return true;
   }
};

#endif // CBOTH_MUTABEL_HPP

