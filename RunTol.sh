#!/bin/bash


[ -d results ] || mkdir results

max_iters=1000000
nx=129

for ((i=1;i<9;i++));do
   tol=1e-$i
   odir=`printf "results/TOLe%04d" ${i}`
   [ -d ${odir} ] || mkdir ${odir}
   ./JACOBI2D ${nx} ${tol} ${max_iters} ${odir}
done
