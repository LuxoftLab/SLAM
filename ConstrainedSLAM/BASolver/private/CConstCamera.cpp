#include "CConstCamera.hpp"

CConstCamera::CConstCamera(const CScene3D::tPointPtr &point,
                           const CScene3D::tCameraPtr &camera,
                           const PointTrack::tPoint2fPtr & point2D) :
   AFunctor(point, camera, point2D)
{

}

CConstCamera::CConstCamera(const AFunctor *functor) :
   AFunctor(functor)
{

}

ceres::ResidualBlockId
CConstCamera::bindToProblem(const tProblemPtr &problem)
{
   //function will be delited by ceres::problem
   tCostFunction * function = new tCostFunction(this);
   return problem->AddResidualBlock(function, NULL, mPoint->position);
}
