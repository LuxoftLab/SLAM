#ifndef CSCENE
#define CSCENE

#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

class Visualiser{
public:
   typedef boost::numeric::ublas::matrix <double> tMatrixDouble;

   static Visualiser& getInstance();
   tMatrixDouble quaternionToMatrix(double quaternion[]);
   void drawCamera(double quaternion[], double position[]);
   void drawPoint(double center[]);

private:
   Visualiser();
   Visualiser(Visualiser const&);
   void operator = (Visualiser const&);

   ~Visualiser();

   std::fstream fileStream;

   unsigned int vertexes;

};
#endif // CSCENE

