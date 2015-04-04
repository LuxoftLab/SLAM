#ifndef CBASOLVER_HPP
#define CBASOLVER_HPP

#include "IBASolver.hpp"
#include "private/AFunctor.hpp"
#include "private/CFunctorContainer.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>
#include <ceres/ceres.h>

class CBASolver : public IBASolver {
public:
   typedef boost::shared_ptr<CFunctorContainer> tFunctorContainerPtr;

   CBASolver(int minFrames);

   void addFrame(const CFrame & frame);
   const CScene3D & getScene();

private:
   CScene3D mScene;
   boost::circular_buffer<tFunctorContainerPtr> mFunctors;
   AFunctor::tProblemPtr mProblem;
};

#endif // IBASOLVER_HPP

