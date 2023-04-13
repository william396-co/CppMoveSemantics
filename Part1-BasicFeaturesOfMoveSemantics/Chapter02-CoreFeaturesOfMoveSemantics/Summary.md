Rvalue reference are declared with && and no const

They can be initialized by temporary objects that do not have a name or non-const objects
marked with std::move()

Rvalue reference extend the lifetime of objects return by value

std::move() is a static_cast to the corresponding rvalue reference type. This allows
us to pass a named object to an rvalue reference

Objects marked with std::move() can also be passed to functions taking the argument by const lvalue
reference but not taking a non-const lvalue reference

Objects marked with std::move() can also be passed to functions taking the argument by value.
In that case, move semantics is used to initlialize the parameter, which can make call-by-value pretty cheap.

const rvalue reference as possible but implementating against them usually makes no sense.

Move-from objects should be in a valid but unspecified state. The C++ standard library guarantees that
for its types, You can still(re)use them providing you do not make any assumptions about their value.

