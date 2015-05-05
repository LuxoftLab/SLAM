#ifndef CSCENE
#define CSCENE

#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class Visualiser{
public:
   static Visualiser& getInstance();
   matrix <double> quaternionToMatrix(double quaternion[]);
   void drawCamera(double quaternion[], double position[]);
   void drawPoint(double center[]);

private:
   Visualiser();
   Visualiser(Visualiser const&);
   void operator = (Visualiser const&);

   ~Visualiser();

   matrix <double> rotationMatrix;

   std::fstream fileStream;

   unsigned int vertexes;

};
#endif // CSCENE

