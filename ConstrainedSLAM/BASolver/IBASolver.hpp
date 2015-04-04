#ifndef IBASOLVER_HPP
#define IBASOLVER_HPP

#include "Common/CFrame.hpp"
#include "Scene3D/CScene3D.hpp"

class IBASolver {
public:
   virtual ~IBASolver() {}

   virtual void addFrame(const CFrame & frame) = 0;
   virtual const CScene3D & getScene() = 0;

};

#endif // IBASOLVER_HPP

