#include "CFunctorContainer.hpp"
#include "CConstCamera.hpp"

CFunctorContainer::~CFunctorContainer()
{
   for(auto it = mFunctors.begin(); it != mFunctors.end(); it++)
   {
      (*it)->unbind();
   }
}

void CFunctorContainer::add(AFunctor * functor)
{
   mFunctors.push_back(functor);
}

void CFunctorContainer::changeAllToConstCamera()
{
   for(auto it = mFunctors.begin(); it != mFunctors.end(); it++)
   {
      AFunctor * prev = *it;
      (*it) = new CConstCamera(prev);
      (*it)->bind(prev->getProblem());
      prev->unbind();
   }
}
