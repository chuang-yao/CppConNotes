# Free Store vs. Heap

There is much confusion regarding the usage of the words stack, heap and free store. Most developers are using the stack and heap wrongly for C++.

## Stack

The stack (actually the call stack) is the memory where all your local variables in a function will be located. The stack is a memory structure where all the function calls, from the start of the current thread, up to the currently executed function are stored together with the memory that they use. The variables which reside on the stack are stored there, until the function where they reside returns. Once the method returns then all local (stack) variables will be cleaned up.

## Heap

The heap is a legacy from C which should not be used in C++. Objects on the heap are allocated using `malloc` or `calloc` and released again using `free`. You should never use `malloc` or `calloc` to allocate an object in C++. This since these calls does not call the constructor of the object, leaving you with allocated memory for an invalid object.

## Free Store

The free store is in C++ what the heap was in C. Objects on the free store are allocated using `new` or `new[]` and released again using `delete` or `delete[]`. Objects allocated using `new` or `new[]` are allocated and their [constructor](https://www.moderncplusplus.com/constructor/) is being called once the memory is allocated. Objects destroyed using `delete` or `delete[]` have their [destructor](https://www.moderncplusplus.com/destructor/) called before the memory is released again.


[Free store vs Heap](https://www.moderncplusplus.com/free-store-vs-heap/)
