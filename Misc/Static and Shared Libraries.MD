# Difference between Static and Shared Libraries

In programming, a library is a collection of pre-compiled pieces of code that can be reused in a program. Libraries simplify life for programmers, in that they provide reusable functions, routines, classes, data structures and so on
which they can be reused in the programs.

## Static Libraries

A Static library or statically-linked library is a set of routines, external functions and variables which are resolved in a caller at compile-time and copied into a target application by a compiler, linker, or binder, producing an object file and a stand-alone executable. This executable and the process of compiling it are both known as a static build of the program. Historically, libraries could only be static.

They are usually faster than the shared libraries because a set of commonly used object files is put into a single library executable file. One can build multiple executables without the need to recompile the file. Because it is a single file to be built, use of link commands are simpler than shared library link commands, because you specify the name of the static library.

## Shared Libraries

Shared libraries are .so (or in Windows .dll, or in OS X .dylib) files.
These are linked dynamically simply including the address of the library (whereas static linking is a waste of space). Dynamic linking links the libraries at the run-time. Thus, all the functions are in a special place in memory space, and every program can access them, without having multiple copies of them.

| PROPERTIES |	STATIC LIBRARY | SHARED LIBRARY |
| :--------- | :-------------- | :------------- |
| Linking time | It happens as the last step of the compilation process. After the program is placed in the memory	| Shared libraries are added during linking process when executable file and libraries are added to the memory.
| Means	| Performed by linkers	| Performed by operating System |
| Size |	Static libraries are much bigger in size, because external programs are built in the executable file.	| Dynamic libraries are much smaller, because there is only one copy of dynamic library that is kept in memory. |
| External file changes |	Executable file will have to be recompiled if any changes were applied to external files. |	In shared libraries, no need to recompile the executable. |
| Time	| Takes longer to execute, because loading into the memory happens every time while executing.	| It is faster because shared library code is already in the memory. |
| Compatibility	| Never has compatibility issue, since all code is in one executable module. |	Programs are dependent on having a compatible library. Dependent program will not work if library gets removed from the system . |

From <https://www.geeksforgeeks.org/difference-between-static-and-shared-libraries/> 
