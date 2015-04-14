#ifndef AFUNCTOR_HPP
#define AFUNCTOR_HPP

#include "Scene3D/CScene3D.hpp"
#include "Common/Common.hpp"

#include <ceres/ceres.h>


//WARNING: object will be destroyed by ceres::Problem
class AFunctor {
public:
   typedef boost::shared_ptr<ceres::Problem> tProblemPtr;

   AFunctor(const CScene3D::tPointPtr & point,
            const CScene3D::tCameraPtr & camera,
            const PointTrack::tPoint2fPtr & point2D);
   AFunctor(const AFunctor * functor);

   virtual ~AFunctor();

   virtual ceres::ResidualBlockId
   bindToProblem(const tProblemPtr & problem) = 0;

   void bind(const tProblemPtr & problem);
   void unbind();
   const tProblemPtr & getProblem();

private:
   tProblemPtr mProblem;
   ceres::ResidualBlockId mId;

protected:
   PointTrack::tPoint2fPtr mPoint2D;
   CScene3D::tPointPtr mPoint;
   CScene3D::tCameraPtr mCamera;
   double mCalibration[3][4];

   template<typename T>
   void quaternionToMatrix(const T * quaternion, T matrix[4][4]) const
   {
      T xx = quaternion[0] * quaternion[0];
      T xy = quaternion[0] * quaternion[1];
      T xz = quaternion[0] * quaternion[2];
      T xw = quaternion[0] * quaternion[3];

      T yy = quaternion[1] * quaternion[1];
      T yz = quaternion[1] * quaternion[2];
      T yw = quaternion[1] * quaternion[3];

      T zz = quaternion[2] * quaternion[2];
      T zw = quaternion[2] * quaternion[3];

      T zero(0);
      T one(1);
      T two(2);

      matrix[0][0] = one - two * (yy + zz);
      matrix[0][1] = two * (xy - zw);
      matrix[0][2] = two * (xz + yw);
      matrix[0][3] = zero;

      matrix[1][0] = two * (xy + zw);
      matrix[1][1] = one - two * (xx + zz);
      matrix[1][2] = two * (yz - xw);
      matrix[1][3] = zero;

      matrix[2][0] = two * (xz - yw);
      matrix[2][1] = two * (yz + xw);
      matrix[2][2] = one - two * (xx + yy);
      matrix[2][3] = zero;


      matrix[3][0] = zero;
      matrix[3][1] = zero;
      matrix[3][2] = zero;
      matrix[3][3] = one;
   }

};

#endif // AFUNCTOR_HPP

