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



### 1.2. Memory

To simplify the calculation we will be looking into the memory intensive structures.

*Jacobi A*:

-



*Jacobi C*:

for larger problems one can assume 5 read accesses per iteration as edge cases become less likely.

- Update step: 5 double reads 1 write $ \implies 48 \text{ Bytes / Unknown / Iteration} $
- Residual computation: 5 double reads $ \implies 40 \text{ Bytes / Unknown / Iteration} $
- Save solution: 1 read 1 write $ \implies 16 \text{ Bytes / Unknown / Iteration} $
- Total: $ 104 \times N \text{ Bytes / Iteration} $



---

## 2. Consequences
The first improvement we can observe is the safety of the solution. Taking into account how dynamic memory allocation works—even compared to static memory allocation—one risks the impossibility of allocating the required memory chunk while the function is executed.
Considering the computational cost of the operation, Jacobi C outperforms Jacobi A by several times. Despite having the same number of iterations, each iteration takes a significantly smaller amount of time due to code optimization, the lack of additional memory allocation, and a more efficient implementation.
It is also important to note that we still solve the same mathematical system; that is, the residual errors of the computation remain unchanged.

### 2.1. Versatilitiy of the functions

### 2.2 Demands of the programmer

---

## 3. Tolerance

---

## 4. Optimization flags