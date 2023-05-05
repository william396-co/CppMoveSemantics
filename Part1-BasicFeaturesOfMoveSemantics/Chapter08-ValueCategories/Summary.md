.Any expression in a C++ program belongs to exactly one of these primary value categories:
- lvalue(roughly, for a named object or a string literal)
- prvalue(roughly, for an unnamed temporary object)
- xvalue(roughly, for an object marked with std::move())

.Whether a call or operation in C++ is valid depends on both the type and the value category.

.Rvalue reference of types can only bind to rvalue(prvalues or xvalues).

.Implicit operations might change the value category of a passed argument.

.Passing an rvalue to an rvalue reference binds it to an lvalue.

.Move semantics is not passed through.

.FUnctions and references to functions are always lvalues.

.For rvalues(temporary objects or objects marked with std::move()), plain value members have move semantics
	but reference or static members have not.

.decltype can either check for the declared type of a passed name or for the type and the value category
  of a psssed expressions.

