#define _USE_MATH_DEFINES
#include "functions.h"
#include <cmath>
#include <iostream>

using namespace std;


inline int ij2l(const int i, const int j, const int Nx) {
   return (j-1)*(Nx-1)+(i-1);
}


//aux := x_new
//sol := x_old

double computeResidual_matrixfree(const int N,
                  const double * const aux,
                  const int NX,
                  const int NY,
                  const double DX,
                  const double a10,
                  const double a11,
                  const double a12,
                  const double a01,
                  const double a21) {

   double res = 0.0;

   //compute Ax
   for (int j=1; j<=NY-1; ++j){
      for(int i=1; i<=NX-1; ++i){
            
         int l = ij2l(i,j,NX);

         double Ax_l = a11 * aux[l]; //this term always exists
         double rhs = 0.0;

         //Boundary Conditions
         if (j > 1) Ax_l += a10 * aux[l - (NX - 1)]; // South
         if (i > 1) Ax_l += a01 * aux[l - 1]; // West
         if (i < NX - 1) Ax_l += a21 * aux[l + 1]; // East
         if (j < NY - 1){
            Ax_l += a12 * aux[l + (NX - 1)]; // North
         }
         else {
            // North Boundary
            rhs = -a12*std::sin(M_PI*i*DX);
         }

         res += fabs(rhs-Ax_l);
         //res = max(res,abs(rhs[l]-Ax_l));
      }
   }
   res/=sqrt(N);
   return res;
}

int solveJacobi2D_C(const double L
                   ,const int NX, const int NY
                   ,const double TOL,const int MAX_ITERS
                   ,double* const sol
                   ,const double* const rhs
                   ,double& res , int& iters
                   ,double* const aux
                   ,std::ofstream& LOG_FILE) {

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
      const int N = (NX-1)*(NY-1);
      
      //iterate over rows:
      for (int j=1; j<=NY-1; ++j){
         for(int i=1; i<=NX-1; ++i){
            
            int l = ij2l(i,j,NX);

            //compute sum:
            double sum = 0.0;
            double rhs = 0.0; //standard, will be edited for north boundary

            //Boundary Conditions

            if (j > 1) sum += a10 * sol[l - (NX - 1)]; // South
            if (i > 1) sum += a01 * sol[l - 1]; // West
            if (i < NX - 1) sum += a21 * sol[l + 1]; // East
            if (j < NY - 1){
               sum += a12 * sol[l + (NX - 1)]; // North
            }
            else {
               // North Boundary
               rhs = -a12*std::sin(M_PI*i*DX);
            }
            
            aux[l] = (rhs-sum)/a11;
         }
      }

      // compute residual
      res = computeResidual_matrixfree(N,aux,NX,NY,DX,a10,a11,a12,a01,a21);//to be done

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

   return EXIT_SUCCESS;
}