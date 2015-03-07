#include <iostream>


#include <ceres/ceres.h>


struct Functor {

   Functor() {}
   ~Functor()
   {
      std::cout << "functor destructor" << std::endl;
   }

   template <typename T> bool operator()(const T * const m, T * residual) const
   {
      residual[0] = T(0);
      return true;
   }
};

int main() {
   typedef ceres::AutoDiffCostFunction<Functor, 1, 1> tCostFunction;

   ceres::Problem problem;
   Functor * functor = new Functor();
   tCostFunction * function = new tCostFunction(functor);
   double result = 0;
   problem.AddResidualBlock(function, NULL, &result);

   ceres::Solver::Options options;
   ceres::Solver::Summary summary;
   ceres::Solve(options, &problem, &summary);

   return 0;
}
