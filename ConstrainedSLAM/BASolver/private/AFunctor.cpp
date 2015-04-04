#include "AFunctor.hpp"
#include "Common/LogUtils/Logger.hpp"

AFunctor::AFunctor(const CScene3D::tPointPtr &point,
                   const CScene3D::tCameraPtr &camera) :
   mPoint(point),
   mCamera(camera),
   mId(NULL)
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
   if(mId != NULL) {
      mProblem->RemoveResidualBlock(mId);
      mId = NULL;
   } else {
      CVNAR_LOGGER_INIT;
      CVNAR_LOG(ERROR) << "Functor already unbind";
   }
}

