#include "BASolver/CBASolver.hpp"
#include "CBothMutable.hpp"

CBASolver::CBASolver(int minFrames) :
   mFunctors(minFrames),
   mProblem(new ceres::Problem)
{

}

void CBASolver::addFrame(const CFrame &frame)
{
   tFunctorContainerPtr functors(new CFunctorContainer);

   CScene3D::tCameraPtr camera = mScene.createCamera();
   for(auto it = frame.points.begin(); it != frame.points.end(); it++)
   {
      CScene3D::tPointPtr point = mScene.getPoint(it->first);
      AFunctor * functor = new CBothMutable(point, camera);
   }

   mFunctors.push_back(functors);
   if(mFunctors.capacity() == mFunctors.size())
   {
      ceres::Solver::Options options;
      ceres::Solver::Summary summary;
      ceres::Solve(options, mProblem.get(), &summary);
   }
}

const CScene3D & CBASolver::getScene()
{
   return mScene;
}
