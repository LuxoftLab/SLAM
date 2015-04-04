#ifndef SPOINT3D_HPP
#define SPOINT3D_HPP


struct SPoint3D {
   double position[3];

   SPoint3D()
   {
      position[0] = position[1] = position[2] = 0;
   }

   SPoint3D(double x, double y, double z)
   {
      position[0] = x;
      position[1] = y;
      position[2] = z;
   }
};

#endif // SPOINT3D_HPP

