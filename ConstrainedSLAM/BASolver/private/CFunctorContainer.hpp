#ifndef CFUNCTOR_CONTAINER_HPP
#define CFUNCTOR_CONTAINER_HPP

#include "AFunctor.hpp"

#include <list>

class CFunctorContainer {
   std::list<AFunctor*> mFunctors;

public:
   ~CFunctorContainer();

   void add(AFunctor * functor);
   void changeAllToConstCamera();
};

#endif // CFUNCTOR_CONTAINER_HPP

