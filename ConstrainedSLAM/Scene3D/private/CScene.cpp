#include "Scene3D/CScene.hpp"

Visualiser::Visualiser() : vertexes (0)
{
   fileStream.open("3D_scene.obj", std::ios_base::out |
                                   std::ios_base::trunc);
   fileStream.precision();
   fileStream.setf(std::ios::fixed, std::ios::floatfield);

}

Visualiser& Visualiser::getInstance()
{
   static Visualiser instance;
   return instance;
}

Visualiser::tMatrixDouble Visualiser::quaternionToMatrix(double quaternion[])
{
   tMatrixDouble rotationMatrix(3,3);

   double x, y, z, w;
   double x2, y2, z2;
   double wx, wy, wz;
   double xx, xy, xz;
   double yy, yz;
   double zz;

   x = quaternion[0];
   y = quaternion[1];
   z = quaternion[2];
   w = quaternion[3];

   double s = 2.0f / (x * x + y * y + z * z + w * w);

   x2 = x * s;
   y2 = y * s;
   z2 = z * s;

   xx = x * x2;
   xy = x * y2;
   xz = x * z2;

   yy = y * y2;
   yz = y * z2;

   zz = z * z2;

   wx = w * x2;
   wy = w * y2;
   wz = w * z2;

   rotationMatrix(0,0) = 1.0f - (yy + zz);
   rotationMatrix(1,0) = xy - wz;
   rotationMatrix(2,0) = xz + wy;

   rotationMatrix(0,1) = xy + wz;
   rotationMatrix(1,1) = 1.0f - (xx + zz);
   rotationMatrix(2,1) = yz - wx;

   rotationMatrix(0,2) = xz - wy;
   rotationMatrix(1,2) = yz + wx;
   rotationMatrix(2,2) = 1.0f - (xx + yy);

   return rotationMatrix;
}

void Visualiser::drawCamera(double quaternion[], double position[])
{
   tMatrixDouble camera(5,3);

   camera(0,0) = -0.5 + position[0];
   camera(0,1) = -0.5 + position[1];
   camera(0,2) =  0.5 + position[2];

   camera(1,0) = -0.5 + position[0];
   camera(1,1) =  0.5 + position[1];
   camera(1,2) =  0.5 + position[2];

   camera(2,0) =  0.5 + position[0];
   camera(2,1) =  0.5 + position[1];
   camera(2,2) =  0.5 + position[2];

   camera(3,0) =  0.5 + position[0];
   camera(3,1) = -0.5 + position[1];
   camera(3,2) =  0.5 + position[2];

   camera(4,0) = -0.0 + position[0];
   camera(4,1) = -0.0 + position[1];
   camera(4,2) = -0.5 + position[2];

   camera = boost::numeric::ublas::prod(camera, this->quaternionToMatrix(quaternion));

   for(size_t i = 0; i < camera.size1(); ++i)
   {
      fileStream << "v ";
      for(size_t j = 0; j < camera.size2(); ++j)
      {
         fileStream << camera(i,j) << ' ';
      }
      fileStream << std::endl;
   }

   fileStream << "f " << vertexes + 1 << ' ' << vertexes + 2 << ' '
                      << vertexes + 3 << ' ' << vertexes + 4 << '\n'

              << "f " << vertexes + 1 << ' ' << vertexes + 2 << ' '
                      << vertexes + 5 << '\n'

              << "f " << vertexes + 2 << ' ' << vertexes + 3 << ' '
                      << vertexes + 5 << '\n'

              << "f " << vertexes + 3 << ' ' << vertexes + 4 << ' '
                      << vertexes + 5 << '\n'

              << "f " << vertexes + 4 << ' ' << vertexes + 1 << ' '
                      << vertexes + 5 << '\n';

   vertexes += 5;

}

void Visualiser::drawPoint(double center[3]){

    double x = center[0];
    double y = center[1];
    double z = center[2];

    fileStream << "v " << x + 0.2 << ' ' << y - 0.2 << ' ' << z - 0.2 << std::endl
               << "v " << x + 0.2 << ' ' << y - 0.2 << ' ' << z + 0.2 << std::endl
               << "v " << x - 0.2 << ' ' << y - 0.2 << ' ' << z + 0.2 << std::endl
               << "v " << x - 0.2 << ' ' << y - 0.2 << ' ' << z - 0.2 << std::endl

               << "v " << x + 0.2 << ' ' << y + 0.2 << ' ' << z - 0.2 << std::endl
               << "v " << x + 0.2 << ' ' << y + 0.2 << ' ' << z + 0.2 << std::endl
               << "v " << x - 0.2 << ' ' << y + 0.2 << ' ' << z + 0.2 << std::endl
               << "v " << x - 0.2 << ' ' << y + 0.2 << ' ' << z - 0.2 << std::endl;

    fileStream << "f " << vertexes + 1 << ' ' << vertexes + 2 << ' '
                       << vertexes + 3 << ' ' << vertexes + 4 << '\n'

               << "f " << vertexes + 5 << ' ' << vertexes + 8 << ' '
                       << vertexes + 7 << ' ' << vertexes + 6 << '\n'

               << "f " << vertexes + 1 << ' ' << vertexes + 5 << ' '
                       << vertexes + 6 << ' ' << vertexes + 2 << '\n'

               << "f " << vertexes + 2 << ' ' << vertexes + 6 << ' '
                       << vertexes + 7 << ' ' << vertexes + 3 << '\n'

               << "f " << vertexes + 3 << ' ' << vertexes + 7 << ' '
                       << vertexes + 8 << ' ' << vertexes + 4 << '\n'

               << "f " << vertexes + 5 << ' ' << vertexes + 1 << ' '
                       << vertexes + 4 << ' ' << vertexes + 8 << '\n';

    vertexes += 8;
}

Visualiser::~Visualiser()
{
   fileStream.close();
}
