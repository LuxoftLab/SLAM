#include "Scene3D/CScene3D.hpp"


CScene3D::tCameraPtr CScene3D::createCamera()
{
   tCameraPtr camera(new SCamera);
   mCameras.push_back(camera);
   return camera;
}

CScene3D::tPointPtr CScene3D::getPoint(int i) {
   auto it = mPoints.find(i);
   if(it == mPoints.end())
   {
      tPointPtr point(new SPoint3D(1, 1, 1));
      mPoints.insert(std::pair<int, tPointPtr>(i, point));
      return point;
   }
   return it->second;
}


