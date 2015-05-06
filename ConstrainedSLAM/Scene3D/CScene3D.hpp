#ifndef CSCENE3D_HPP
#define CSCENE3D_HPP

#include <vector>
#include <map>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "SCamera.hpp"
#include "SPoint3D.hpp"


class CScene3D {
public:
   typedef boost::shared_ptr<SPoint3D> tPointPtr;
   typedef boost::shared_ptr<SCamera> tCameraPtr;
   typedef boost::numeric::ublas::matrix <double> tMatrixDouble;

   tCameraPtr createCamera();
   tPointPtr getPoint(int i);
   void saveToObj(std::string path);

private:
   tMatrixDouble quaternionToMatrix(double quaternion[]);
   void drawCamera(double quaternion[], double position[]);
   void drawPoint(double center[]);

   std::map <int, tPointPtr> mPoints;
   std::vector <tCameraPtr> mCameras;

   std::fstream fileStream;
   unsigned short vertexes = 0;
};

#endif // CSCENE3D_HPP

