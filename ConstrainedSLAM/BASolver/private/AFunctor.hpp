#ifndef AFUNCTOR_HPP
#define AFUNCTOR_HPP

#include "Scene3D/CScene3D.hpp"

#include <ceres/ceres.h>


//WARNING: object will be destroyed by ceres::Problem
class AFunctor {
public:
   typedef boost::shared_ptr<ceres::Problem> tProblemPtr;

   AFunctor(const CScene3D::tPointPtr & point, const CScene3D::tCameraPtr & camera);

   virtual ~AFunctor();

   virtual ceres::ResidualBlockId
   bindToProblem(const tProblemPtr & problem) = 0;

   void bind(const tProblemPtr & problem);
   void unbind();

private:
   tProblemPtr mProblem;
   ceres::ResidualBlockId mId;

protected:
   CScene3D::tPointPtr mPoint;
   CScene3D::tCameraPtr mCamera;
};

#endif // AFUNCTOR_HPP

