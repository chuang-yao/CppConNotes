# Back to Basics: Smart Pointers

## `std::unique_ptr`

Use `std::unique_ptr` for exclusive-ownership resource management. 

A raw pointer is copyable. Ownership is unclear. 
A `unique_ptr` is move-only, and its move constructor nulls out the source pointer. -> unique ownership

There is a specialization for array types. `std::unique_ptr<T[]>`

It also supports user-defined deleter that defaults to `delete`. 

Treat smart pointer types just as raw pointer types:
	• pass by value
	• return by value

## `std::shared_ptr`

Use `std::shared_ptr` for shared-ownership resource management. 

Let the last person out of the room turn off of the lights. Put a counter at the doorway. If you find the counter reaches zero after you leave the room, turn off the lights. 

A typical implementation for `std::shared_ptr`

Q: Why do we need a pointer to the controlled object in the control block?
A: Multiple inheritance. 

Prefer smart pointers to naked use of `new`

Use `std::make_shared<T>` instead of `new`. 

`std::unique_ptr` is implicitly convertible to a `std::shared_ptr<T>`. 

## `std::weak_ptr`

Use `std::weak_ptr` for `shared_ptr`-like pointes that can dangle

A `weak_ptr` is NOT a pointer. You can NOT dereference it. 
Use the `lock` member function to return a `shared_ptr` and then access the object through the `shared_ptr`. 
