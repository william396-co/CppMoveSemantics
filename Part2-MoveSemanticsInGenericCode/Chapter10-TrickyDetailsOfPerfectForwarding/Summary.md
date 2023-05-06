.You can use universal reference to bind to all const and non-const objects without losing the information
 about the constness of object.

 .You can use universal reference to implement special handling for passed arguments with move semantics
  even without using std::forward<>().

 .To have a universal reference of a specific type, you need concepts/requirements(since C++20) or some 
  template tricks(up to C++17)

.Only rvalue reference of function template parameter are universal references. Rvalue references of
 class template parameters, member of template paramaters,and full specialization are ordinary rvalue
 references, you can only bind to rvalues.

.When specifying the types of universal reference explicitly, they act no longer as universal references.
 Use Type& to be able to pass lvalues then.

.The C++ standard committee introduced forwarding reference as a "better" for universal reference.
 Unfortunately, the term forwarding reference restricts the purpose of universal references to a common
 specific use case and creates the unnecessary confusion of having two terms for the same thing, Therefor,
 use universal/forwarding reference to avoid even more confusion.
