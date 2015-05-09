#include "AFunctor.hpp"
#include "Common/LogUtils/Logger.hpp"

AFunctor::AFunctor(const CScene3D::tPointPtr &point,
                   const CScene3D::tCameraPtr &camera,
                   const PointTrack::tPoint2fPtr &point2D) :
   mPoint(point),
   mCamera(camera),
   mPoint2D(point2D),
   mId(NULL)
{
   mCalibration[0][0] = -500;
   mCalibration[0][1] = 0;
   mCalibration[0][2] = 300;
   mCalibration[0][3] = 0;

   mCalibration[1][0] = 0;
   mCalibration[1][1] = 500;
   mCalibration[1][2] = 300;
   mCalibration[1][3] = 0;

   mCalibration[2][0] = 0;
   mCalibration[2][1] = 0;
   mCalibration[2][2] = 1;
   mCalibration[2][3] = 0;

}

AFunctor::AFunctor(const AFunctor *functor) :
   AFunctor(functor->mPoint, functor->mCamera, functor->mPoint2D)
{
}

AFunctor::~AFunctor()
{
}

void AFunctor::bind(const tProblemPtr & problem)
{
   mProblem = problem;
   mId = bindToProblem(problem);
}

void AFunctor::unbind()
{
   CVNAR_LOGGER_INIT;
   if(mId != NULL) {
      mProblem->RemoveResidualBlock(mId);
      mId = NULL;
   } else {
      CVNAR_LOG(ERROR) << "Functor already unbind\n";
   }
}

const AFunctor::tProblemPtr & AFunctor::getProblem()
{
   return mProblem;
}

