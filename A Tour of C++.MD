# A Tour of C++

## 1. The Basics

## 2. User-Defined Types

## 3. Modularity

Simple operations must be inlined; should be implemented without function call in the generated machine code. 

The constructor/destructor combination is the basis of many elegant techniques; the basis for most C++ general resource management. 

**RAII**: Resource Acquisition Is Initialization. 

`virtual` means may be redefined later in a class derived from this one. 

The usual implementation technique is for the compiler to convert the name of a virtual function into an index into a table of pointers to functions. The table is usually called the *virtual function table*. 

A virtual destructor is essential for an abstract base class.

We tend to allocate classes in class hierarchies on the free store using `new`, and we access them through pointers and references. 

A “plain old pointer” should not be used to represent ownership. 

Make a function a member only if it needs direct access to the representation of a class. Use non-members for symmetric operators. 

## 4. Classes

## 5. Essential Operations

A copy or move constructor invocation is often optimized away by constructing the object used to initialize right in the target object by the compiler. 

When a class has a pointer member, it is usually a good idea to be explicitly about copy and move operations. 

The Rule of Zero: to either define all of the essential operations or none.

When it comes to conversions, use `explicit` for constructors that take a single argument unless there is a good reason not to. 

For abstract types, member-wise copy is almost never the right semantics. 

Resource handle: responsible for an object access through a pointer. 

An rvalue reference is a reference to something that nobody else can assign to, so we can safely “steal” its value. 

The standard library function `move()` does not actually move anything. Instead, it returns an rvalue reference to its argument from which we may move; it is a kind of cast. 

Use resource handles: let each resource have an owner in some scope and by default be released at the end of its owners scope. (RAII)

`”Surprise!”` is a `const char[10]`.
`”Surprise!”s` is a `std::string`.

A literal operator converts a literal of its argument type, followed by a subscript, into its return type. `operator””_`

The standard library `unordered_map<K, V>` is a hash table with `K` as the key type and `V` as the value type. To use a type `X` as a key, we must define `hash<X>`. 

Never leak anything you think of as a resource.

## 6. Templates

Templates are compile-time mechanism, so they incur on runtime overhead compare to hand-crafted code. 

Templates provide compile-time parametric polymorphism.

*Concept* is a predicate that checks whether `T` has all the properties that a template requires. 

When a template argument cannot be deduced from the constructor arguments, we can help by providing a deduction guide. 

```cpp
template <typename It>
Vector<It, It> -> Vector<typename It::value_type>;
```

A function template can be a member function but not a `virtual` member. Because the compiler would not know all instantiations of such a template in a program so it could not generate a virtual function table. 

A function object is sometimes also called a functor. 

Function objects used to specify the meaning of key operations of a general algorithm are often referred to as policy objects. 

Using a lambda, we can turn any statement into an expression. 

Having the alias `size_t` allows the programmer to write portable code. 

Only the selected branch of an `if constexpr` is instantiated. 

There is no separate compilation of templates: `#include` template definitions in every translation unit that uses them. 

## 7. Concepts and Generic Programming

Generic Programming: programming that focuses on the design, implementation, and use of general algorithms. 

Concepts: The abstractions representing the fundamental operations and data structures; appears as requirements for template parameters

Good abstractions are carefully grown from concrete examples. 

Variadic templates are sometimes called *variadics*. 

Fold is a powerful abstraction.

```cpp
template <typename ...T>
void print(T && ...args) {
	(std::cout << ... << args) << '\n';
}

print("Hello!"s, ' ', "World ", 2017);
// (((((std::cout << "Hello!"s) << ' ') << "World ") << 2017) << '\n');
```

Checking against concepts happens before instantiation-time type checking (duck typing). 

Templates provide a general mechanism for compile-time programming. 

Don’t use variadics for homogeneous argument lists (prefer init list for that). 
 
## 8. Library Overview

The specification of the standard library is over two thirds of the ISO C++ standard. 

Don’t reinvent the wheel; use libraries. 

## 9. Strings and Regular Expressions

`string` is a `Regular` type for owning and manipulating a sequence of characters of various character types. 

The standard `string` has a move constructor so returning strings by value is efficient. 

Short-string optimization: short string values are kept in the `string` object itself and only long strings are placed on the free store. 

Why?
	• memory allocation is costly in multithreaded workload
	• strings of various lengths can result in memory fragmentation

To handle multiple character sets, `string` is really an alias for a general template `basic_string` with the character type `char`.

`string_view` is basically a (pointer, length) pair denoting a contiguous sequence of characters. 

## 10. Input and Output

An `iostream` has a state that we can examine to determine whether an operation succeeded. 

If you don’t use C-style I//O and care about I//O performance, call `ios_base::sync_with_stdio(false);` to avoid significant overhead due to compatibility with C-style I//O

We use the error codes when operations are expected to fail frequently in normal use and the throwing operations when an error is considered exceptional.

Avoid `endl`. 

Remember to check that a file stream is attached to a file before using it. 

## 11. Containers

A typical implementation of `vector` will consist of a handle holding pointers to the first element, one-past-the-last element, and one-past-the last allocated space. 

In addition, it holds an allocator from which the `vector` can acquire memory for its elements. 

If you have a class hierarchy that relies on virtual functions to get polymorphic behavior, do not store objects directly in a container. Instead store a pointer (or a smart pointer). 

Many performance-critical applications use `vector`s and checking all subscripting implies a cost on the order of 10%.

Use `vector::at()` if you want guaranteed range-checking. 

Unless you have a reason not to, use a `vector`. 

A `map` is also known as an associative array or a dictionary. It is implemented as a balanced binary tree (usually a Red-Black Tree). 

Creating a new hash function by combining existing hash functions using exclusive-or (`ˆ`) is simple and often very effective.

We can avoid explicitly passing the hash operation by defining it as a specialization of the standard-library `hash` template. 

Given a good hash function, an `unordered_map` is much faster than a `map` for large containers. However, the worst-case behavior of an `unordered_map` with a poor hash function is far worse than that of a `map`.

When it comes to performance, don’t trust your intuition: measure. 

## 12. Algorithms

Iterators are used to separate algorithms and containers.

Iterator is a concept. 

An algorithm is a function template operating on sequences of elements.

A predicate must not modify its argument. 

## 13. Utilities

Use `shared_ptr` only if you actually need shared ownership.

`std::move()` should have been called something like `rvalue_cast`.

An `array` does not follow the ‘‘handle to elements’’ model of STL containers.

A type function is a function that is evaluated at compile time given a type as its argument or returning a type.

## 14. Numerics

## 15. Concurrency

Work at the highest level of abstraction that you can afford. 

Prefer parallel algorithms to direct use of concurrency.

## 16. History and Compatibility

For each standard C header `<X.h>` that places names in the global namespace, the header `<cX>` places the names in namespace `std`.
