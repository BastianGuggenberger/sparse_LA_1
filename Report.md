# REPORT

## 0. Introduction

### 0.1. Assignment

In this assignment we were tasked to imporve an implementation of the Jacobi algorithm provided to us and conduct tests with regards to performance in comparison to the initial implementation. The new version is to be matrix free and should aim to improve time and memory usage while achieving the same result.

This report will present the requested datapoints aswell as answer the questions provided in the excercise sheet.

### 0.2. Machine

Testing is conducted on the Jupyter hub provided on the Tuwel page, the exact specs of the machine are therefore not known, however, they are not mandatory to draw conclusions from the tests.


---

## 1. Improvements

### 1.1. Performance

Comparison of both algortihms for different sizes of nxn Matrices:

| Size n | Jacobi A [s] | Jacobi C [s] | Decrease |
|:----:|:------------:|:------------:|:--------:|
|   3  |    1.95e-4   |    1.16e-4   |   -40%   |
|   4  |    2.84e-3   |    1.28e-3   |   -55%   |
|   5  |    4.39e-2   |    1.66e-2   |   -62%   |
|   6  |     0.709    |     0.257    |   -64%   |
|   7  |     13.2     |      4.2     |   -68%   |
|   8  |      204     |      68      |   -67%   |



### 1.2. Memory



---

## 2. Consequences

### 2.1. Versatilitiy of the functions

### 2.2 Demands of the programmer

---

## 3. Tolerance

---

## 4. Optimization flags