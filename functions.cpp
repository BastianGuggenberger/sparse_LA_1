
#include "functions.h"

using namespace std;

inline int ij2l(const int i, const int j, const int Nx) {
   return (j-1)*(Nx-1)+(i-1);
}

int solveJacobi2D_C(const double L
                   ,const int NX, const int NY
                   ,const double TOL,const int MAX_ITERS
                   //,double* const sol
                   //,const double* const rhs
                   ,double& res , int& iters
                   //,double* const aux
                   ,std::ofstream& LOG_FILE) {

   //implementation without boundary conditions
   //inspired by generateLinSystemCOO

   //prepare constants
   const double DX  = L/static_cast<double>(NX);
   const double DY  = L/static_cast<double>(NY);
   const double DXSQ  = pow(DX,2);
   const double DYSQ  = pow(DY,2);

   const double a10 = 1.0/DYSQ;
   const double a01 = 1.0/DXSQ;
   const double a11 = -(2.0/DXSQ+2.0/DYSQ);
   const double a21 = 1.0/DXSQ;
   const double a12 = 1.0/DYSQ;

   //begin jacobi algorithm based on solveJacobi2D_A

   res = 2*TOL;

   iters = 0;
   while (res>TOL) {
      const int N = (NX-1)*(NY-1); //amount of points - matrix is of size NxN
      
      //iterate over rows:
      for (int l=0; l<N; l++){

         int j = l / (NX-1) + 1; //j starts at 1
         int i = l % (NY-1) + 1; //i starts at 1

//----------
         //To be done: Boundary Conditions

         //South Boundary
         if(j==1){

         }

         //North Boundary
         if(j==NX-1){


         }

         //West Boundary
         if(i==1){

         }

         //East Boundary
         if(i==NY-1){

         }
//----------------

         //Inner points:

         //compute sum:
         double sum = 0.0;
         int m;
         
         //a10 bottom:
         m = l-NX;
         sum += a10 * sol[m];

         //a01 left:
         m = l-1;
         sum += a01 * sol[m];

         //a21 right:
         m = l+1;
         sum += a21 * sol[m];

         //a12 top:
         m = l+NX;
         sum += a12 * sol[m];
         
         aux[l] = (0.0-sum)/a11;
      }

      // compute residual
      res = computeResidual(nnz,N
                           ,cooRow,cooCol,cooMat
                           ,aux,rhs,sol);//note that res of new x is computed (sol=aux, aux=sol, see parameters of the function)

      for (int l = 0; l<N;++l) {
         sol[l] = aux[l];
      }

      ++iters;
      if (iters == MAX_ITERS) break;
   }

   if (iters < MAX_ITERS) {
      LOG_FILE << "Successfull convergence" << endl;
      LOG_FILE << " - residual achieved " << res << endl;
      LOG_FILE << " - iterations " << iters << endl;
      return EXIT_SUCCESS;
   } else { 
      LOG_FILE << "Failure of convergence procedure" << endl;
      LOG_FILE << " - residual achieved " << res << endl;
      LOG_FILE << " - iterations " << iters << endl;
      return EXIT_FAILURE;
   }


///END

   return EXIT_SUCCESS;
}

