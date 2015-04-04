#include "CFunctorContainer.hpp"

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
