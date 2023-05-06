.Do not return by value with const(otherwise you disable movee semantics for return values)

.Do not mark returned non-const rvalue reference with const.

.auto&&  can be used to declare a universal reference that is not a parameter, Just like any universal
 reference, it can refer to all object of any type and value category and its type is
  - An lvalue reference(Type&) if binds to an lvalue
  - An rvalue reference(Type&&) if it binds to an rvalue

 .Use std::forward<decltype(ref)>(ref) to perfectly forward a universal reference ref that is declared
   with auto&&

 .You can use universal reference to refer to both const and non-const objects and use them multiple
  times without losing the information about their constness.

 .You can use universal reference to bind to reference that are proxy types.

 .Consider using auto&& in generic code that iterates over element of a collection to modify them, That
  way, the code works for references that are proxy types.

 .Using auto&& when declaring parameters of a lambda(or function, since C++20) is a shortcut for declaring
  parameters that are universal references in a function template.
