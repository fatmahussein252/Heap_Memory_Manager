# Heap_Memory_Manager
This repository contains my implementation of a heap memory manager in C.
__________________________________________________________________________________________________________
This project consists of two phases. In phase 1, A simulation of the HMM without any kernel dependency has been implemented. The implementation includes:
- A very large statically allocated array to simulate the heap area.
- A pointer to simulate the program break in my HMM.

## simulated_HMM
This Directory includes phase 1

- myHMM.c : This file includes the implementation of the simulated heap and break, `HmmAlloc` and `HmmFree` functions and other helping functions.
- stress_test.c and stress_test_2.c: codes used to test my heap putting it under stress of Allocations and Deallocations of random sizes.
- header.h : Includes declarations of functions.
- Makefile : To compile the program (see usage in the next section).
- script.gdb : This script used while debugging to print the free nodes in my heap (see usage next section).
- HmmAlloc.png and HmmFree.png : flowcharts of the allocation and deallocation operations in my program.

### Usage
After cloning the repo, compile and run the program using the commands:
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
make BUILD_TYPE=DEBU
gdb -x script.gdb ./myHMM
```
To use the script to print all free nodes in gdb call the function using:
```
freelst
```
In phase 2, the fake heap and program break were replaced with the sbrk system call to reserve in the actual heap memory.
To use my implementation instead of the libc functions, the four functions: `malloc`, `calloc`, `realloc` and `free` were implemented using my `HmmAlloc` an `HmmFree` functions. Then compiled them together and generated the libmyHMM.so dynamic shared function.

## HMM_phase_2
This Directory includes:
- myHMM.c : This file includes the implementation of the simulated heap and break, `HmmAlloc` and `HmmFree` functions and other helping functions.
- Allocs_and_Free.c: This file includes the implementation of the dynamic memory allocate and free functions (`malloc`, `calloc`, `realloc`, `free`).
- myHMMheader.h : Includes declarations of functions.
- script.gdb : This script used while debugging to print the free nodes in my heap.
- test.c: This code used to test my HMM putting it under stress of Allocations and Deallocations of random sizes and writing in the allocated memory.
- allocated.gdb: This script used while debugging to print the allocated pointers in the test.c code .
- flowcharts : contains flowcharts of the `malloc`, `calloc`, `realloc` and `free` operations.

### Usage
After cloning the repo, compile the library as dynamic shared library using the commands:
````
$ gcc -g -c -fPIC Allocs_and_Free.c myHMM.c
$ gcc -g -shared -o libmyHMM.so *.o
````
Then add the library to the libraries path and run any process after preloading mylib using:
````
$ export LD_LIBRARY_PATH=/home/fatma/STM/session_6/HMM_phase2/mylib
$ LD_PRELOAD=/home/fatma/STM/session_6/HMM_phase2/mylib/libmyHMM.so <command>
````
Note: my HMM implementation does not include multi threading processes (e.g. like gdb).
sample output showing using mylib to run bash
![image](https://github.com/user-attachments/assets/9e01e4f7-b5ac-4d8c-abf7-74515aa6af3f)

Link to videos explaining my Design and testing mylib with several processes: https://drive.google.com/drive/folders/1ryHj1ZjsYD7PjsowYY0TwIYo5gz-M7VF?usp=drive_link

