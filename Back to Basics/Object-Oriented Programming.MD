# Back to Basics: Object-Oriented Programming

> A programming paradigm in C++ using polymorphism based on runtime function dispatch using virtual functions.  

Derived objects in OOP can be thought of as independent libraries. 
* libraries share the same API (defined by the base class)
* libraries objects can implement and extend this API (dynamic binding)

## Use OOP to model a “is-a” relationship, not for code-reuse

A $(derived) **is-a** $(base). 

Base class defines an **interface** for an object that might provide a type of functionality. 
Derived classes provide **implementations** of different expressions of that object type. 

In OOP we can constantly _lying_ to the compiler about object pointers. The static type is almost never the dynamic type. 

Only dereference an OOP pointer/reference to access base class members. 

## Make non-leaf classes abstract

1. Make every class in your hierarchy either a base-only or leaf-only
2. Make bases
   * abstract
   * assignment operators protected
3. Make leaf classes
	* concrete
	* public assignment operators
	* `final`

## Use the non-virtual interface (NVI) idiom

## Overridden functions must be declared `virtual`

## Always make base classes destructors `virtual`

Deleting a derived class object through a pointer to the base class without a virtual destructor is undefined behavior. 

## Use `override` for overridden functions

* tell readers your intent
* tell the compile to check if you are actually doing overrides

## Don’t mix overloading with overriding

## Don’t specify default values on function overrides

Default parameter values are inserted into the parameter list at the call site at compile-time. 

## Don’t call virtual functions in constructors or destructors

Subjects are constructed and destructed in order according to the inheritance hierarchy. Calling virtual members is llikely to fail due to incomplete objects. 

## Use dynamic rather than static casts for down casting, but avoid casting by refactoring where possible

An upcast is casting a derived type pointer or reference to a pointer or reference to a type further up the hierarchy (to a base type). This is always safe and also called “derived to base conversion”. 

A downcast is casting a base type pointer or reference to a pointer or reference to a type further down the hierarchy (to a derived type). 

* Use an unconditional, static cast (if you are certain the object is of required type). 
* conditional, dynamic cast is a better option

A `dynamic_cast` may fail. We need to check for `nullptr`. 

