. Declaration with two ampresands(name&&) can be two different things:
- If name is not a function template paramter it is an ordinary rvalue reference, binding only to rvalues.
- If name is a function template parameter it is a universal reference, binding to all value categories.

. A universal reference(called forwarding reference in the C++ standard) is a reference that universally
	refer to all objects of any type and value category, Its type is
	- An lvalue reference(type&), if it binds to an lvalue
	- An rvalue reference(type&&), if it binds to an rvalue

. To perfectly forward a passed argument, declare the parameter as a universal reference of a template
	parameter of the function and use std::forward<>().

. std::forward<>() is a conditional std::move(). It expands to std::move() if its parameter is an rvalue.

. It might make sense to mark objects with std::forward<>() even when calling member functions.

. Universal reference are the second-best option of all overload resolutions.

. Avoid implementing generic constructor for on universal reference(or constrain them for specific types).
