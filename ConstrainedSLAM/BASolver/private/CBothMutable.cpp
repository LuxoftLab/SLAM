#include "CBothMutable.hpp"

CBothMutable::CBothMutable(const CScene3D::tPointPtr &point,
                           const CScene3D::tCameraPtr &camera,
                           const PointTrack::tPoint2fPtr & point2D) :
   AFunctor(point, camera, point2D)
{

}

ceres::ResidualBlockId
CBothMutable::bindToProblem(const tProblemPtr &problem)
{
   //function will be delited by ceres::problem
   tCostFunction * function = new tCostFunction(this);
   return problem->AddResidualBlock(function, NULL, mCamera->rotation,
                                    mCamera->position, mPoint->position);
}