#ifndef CSCENE3D_HPP
#define CSCENE3D_HPP

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

#include "SCamera.hpp"
#include "SPoint3D.hpp"


class CScene3D {
public:
   typedef boost::shared_ptr<SPoint3D> tPointPtr;
   typedef boost::shared_ptr<SCamera> tCameraPtr;

   tCameraPtr createCamera();
   tPointPtr getPoint(int i);

private:
   std::map<int, tPointPtr> mPoints;
   std::vector<tCameraPtr> mCameras;
};

#endif // CSCENE3D_HPP

