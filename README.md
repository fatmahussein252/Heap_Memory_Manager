# Heap_Memory_Manager
This repository contains my implementation of a heap memory manager in C.
__________________________________________________________________________________________________________
This project consists of two phases. In phase 1, A simulation of the HMM without any kernel dependency has been implemented. The implementation includes:
- A very large statically allocated array to simulate the heap area.
- A pointer to simulate the program break in my HMM.

## Repo contents

- myHMM.c : This file includes the implementation of the simulated heap and break, `HmmAlloc` and `HmmFree` functions and other helping functions.
- stress_test.c and stress_test_2.c: codes used to test my heap putting it under stress of Allocations and Deallocations of random sizes.
- header.h : Includes declarations of functions.
- Makefile : To compile the program (see usage in the next section).
- script.gdb : This script used while debugging to print the free nodes in my heap (see usage next section).
- HmmAlloc.png and HmmFree.png : flowcharts of the allocation and deallocation operations in my program.

## Usage
After cloning the repo, compile the program using the commands:
````
make     
./myHMM
````
The default test code is stress_test.c . to change it compile using:
````
make TEST_FILE=<source file name>
./myHMM
````
To compile with debugging use:
```
make BUILD_TYPE=DEBUG
gdb -x script.gdb ./myHMM
```
To use the script to print all free nodes in gdb call the function using:
```
freelst
```
## Flowcharts

### The Allocation operation flowchart
![HmmAlloc](https://github.com/user-attachments/assets/79147200-0e31-4044-9fd2-ae3a9380092a)

### The Free operation flowchart
![HmmFree](https://github.com/user-attachments/assets/8b1159b6-5113-4982-bbec-0ec9d6c1e8bc)

