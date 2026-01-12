# REPORT

## 0. Introduction

### 0.1. Assignment

In this assignment we were asked to improve an implementation of the Jacobi algorithm provided to us and conduct tests with regards to performance in comparison to the initial implementation. The new version is to be matrix free and should aim to improve time and memory usage while achieving the same result.

This report will present the requested datapoints aswell as answer the questions provided in the excercise sheet.

### 0.2. Machine

Testing is conducted on the Jupyter hub provided on the Tuwel page, the exact specs of the machine are therefore not known, however, they are not mandatory to draw conclusions from the tests.


---

## 1. Improvements

### 1.1. Performance

Comparison of both algortihms for different sizes of nxn Matrices:

| Size nx | Jacobi A [s] | Jacobi C [s] | Decrease |
|:----:|:------------:|:------------:|:--------:|
|   9  |    1.95e-4   |    1.16e-4   |   -40%   |
|   17  |    2.84e-3   |    1.28e-3   |   -55%   |
|   33  |    4.39e-2   |    1.66e-2   |   -62%   |
|   65  |     0.709    |     0.257    |   -64%   |
|   129  |     13.2     |      4.2     |   -68%   |
|   257  |      204     |      68      |   -67%   |

It can be observed that the magnitude of the 'savings' increases with problem size; larger problems tend to exhibit more significant optimization results. This makes sense as larger problems will usually be bound by their memory meaning that we should observe a memory traffic ration of about 3:1.

### 1.2. Memory

To simplify the calculation we will be looking into the memory intensive structures.

*Jacobi A*:

- Update step: $ 24 \times nnz $
- Residual computation: $ 24 \times nnz $
- Residual norm: $ 16 \times N$
- Save solution: $ 16 \times N$
- $ nnz = 5 \times N$ due to stencil size
- Total:  $ 272 \times N \text{ Bytes / Iteration} $

*Jacobi C*:

for larger problems one can assume 5 read accesses per iteration as edge cases become less likely.

- Update step: 5 double reads 1 write $ \implies 48 \text{ Bytes / Unknown / Iteration} $
- Residual computation: 5 double reads $ \implies 40 \text{ Bytes / Unknown / Iteration} $
- Save solution: 1 read 1 write $ \implies 16 \text{ Bytes / Unknown / Iteration} $
- Total: $ 104 \times N \text{ Bytes / Iteration} $

As we can see our assumptions appears to be correct.

---

## 2. Consequences

### 2.1. Versatilitiy of the functions

- The operator (laplace in our case) must be known beforehand as the matrix free approach uses it, we cannot enter an arbitrary matrix
- Since we need boundary conditions the domain has to be relatively smooth, ideally rectangular
- Sparsity of the Matrix is a requirement as otherwise the approach is very inefficient
- Stencil is coded into the approach and thus has to be present in the matrix

### 2.2 Demands for the programmer

- As the matrix free approach discards the use of a matrix, the resulting code will be alot harder to debug as finding a specific source of an error is way more difficult (less data processed means less info available).
- Since the approach is less general the code will also be less reusable, this results in high amounts of maintenance if one chooses to write ones software based on this approach.

---

## 3. Tolerance

From testing we saw that the tolerance requested seems to have a logarithmic relation with the number of iterations and thus with performance, i.e. requesting a lot of precision will not result in a significantly longer runtime. This makes these iterative methods very exact however also means that going for a less accurate solution is completely unreasonable as the computation will just take very long anyway.

---

## 4. optimization flags
Both algorithms were compiled with the -O3 optimisation flag, so we can be sure that the observed differences come from the algorithm implementation rather than from how the compiler treated the code or which optimisation strategy it applied. We can say that $O3$ is the highest optimization level designed for HPC. It enables: loop unrolling, inlining, vectorizaton.