
#include "functions.h"

using namespace std;

/*
inline int ij2l(const int i, const int j, const int Nx) {
   return (j-1)*(Nx-1)+(i-1);
}
*/

double computeResidual_matrixfree(){
   //to be done
}

int solveJacobi2D_C(const double L
                   ,const int NX, const int NY
                   ,const double TOL,const int MAX_ITERS
                   ,double& res , int& iters
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
      for (int l=0; l<N; l++){

         int j = l / (NX-1) + 1; //j starts at 1
         int i = l % (NY-1) + 1; //i starts at 1

         //compute sum:
         double sum = 0.0;
         double rhs = 0.0; //standard, will be edited for north boundary

         //Boundary Conditions

         if(j==1){
            //South
            if(i==1){
               //South-West Boundary
               //sum += a10 * sol[l-(NX-1)]; //a10 (south)
               //sum += a01 * sol[l-1]; //a01 (west)
               sum += a21 * sol[l+1]; //a21 (east)
               sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
            else if (i==NY-1){
               //South-East Boundary
               //sum += a10 * sol[l-(NX-1)]; //a10 (south)
               sum += a01 * sol[l-1]; //a01 (west)
               //sum += a21 * sol[l+1]; //a21 (east)
               sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
            else {
               //South Boundary
               //sum += a10 * sol[l-(NX-1)]; //a10 (south)
               sum += a01 * sol[l-1]; //a01 (west)
               sum += a21 * sol[l+1]; //a21 (east)
               sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
         }
         
         else if(j==NX-1){
            //North

            //Non-zero Boundary Condition:
            const double xi = static_cast<double>(i)*DX;
            rhs = -a12*std::sin(M_PI*xi);

            if(i==1){
               //North-West Boundary
               sum += a10 * sol[l-(NX-1)]; //a10 (south)
               //sum += a01 * sol[l-1]; //a01 (west)
               sum += a21 * sol[l+1]; //a21 (east)
               //sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
            else if (i==NY-1){
               //North-East Boundary
               sum += a10 * sol[l-(NX-1)]; //a10 (south)
               sum += a01 * sol[l-1]; //a01 (west)
               //sum += a21 * sol[l+1]; //a21 (east)
               //sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
            else {
               //Noth Boundary
               sum += a10 * sol[l-(NX-1)]; //a10 (south)
               sum += a01 * sol[l-1]; //a01 (west)
               sum += a21 * sol[l+1]; //a21 (east)
               //sum += a12 * sol[l+(NX-1)]; //a12 (north)
            }
         }

         else if(i==1){
            //West Boundary
            sum += a10 * sol[l-(NX-1)]; //a10 (south)
            //sum += a01 * sol[l-1]; //a01 (west)
            sum += a21 * sol[l+1]; //a21 (east)
            sum += a12 * sol[l+(NX-1)]; //a12 (north)
         }

         else if(i==NY-1){
            //East Boundary
            sum += a10 * sol[l-(NX-1)]; //a10 (south)
            sum += a01 * sol[l-1]; //a01 (west)
            //sum += a21 * sol[l+1]; //a21 (east)
            sum += a12 * sol[l+(NX-1)]; //a12 (north)
         }

         else {
            //Inner points:
            sum += a10 * sol[l-(NX-1)]; //a10 (south)
            sum += a01 * sol[l-1]; //a01 (west)
            sum += a21 * sol[l+1]; //a21 (east)
            sum += a12 * sol[l+(NX-1)]; //a12 (north)
         }
         
         aux[l] = (rhs-sum)/a11;
      }

      // compute residual
      res = computeResidual_matrixfree(nnz,N,aux,rhs,sol);//to be done

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

