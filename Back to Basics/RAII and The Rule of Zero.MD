# Back to Basics: RAII and The Rule of Zero

## Resource Acquisition is Initialization

It is more about freeing up resources than initialization. 
Use a constructor/destructor pair to make your class safe to copy, assignment, and throwing exceptions. 

## The Rule of Three

If your class directly manages some kind of resource, then you almost certainly need to hand-write three special member functions:

* A **destructor** to free the resource
* A **copy constructor** to copy the resource
* A **copy assignment operator** to free the left-hand resource and copy the right-hand one

Resource management classes should follow the Rule of Three. 

## The Rule of Zero

If your class does not directly manage any resource, but merely uses library components such as vector and string, then you should thrive to write no special member function. **Default Them All!**

Business-logic classes that do not manually manage any resources should follow the Rule of Zero. 

## The Rule of Five

If your class directly manages some kind of resource, then you may need to hand-write five special member functions for correctness and performance:

* A **destructor** to free the resource
* A **copy constructor** to copy the resource
* A **move constructor** to transfer ownership of the resource
* A **copy assignment operator** to free the left-hand resource and copy the right-hand one
* A **move assignment operator** to free the left-hand resource and transfer ownership of the right-hand one
