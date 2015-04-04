#ifndef SCAMERA_HPP
#define SCAMERA_HPP

#include "SPoint3D.hpp"

struct SCamera : SPoint3D {
   double rotation[4]; //quaternion [x, y, z, w]
};

#endif // SCAMERA_HPP

