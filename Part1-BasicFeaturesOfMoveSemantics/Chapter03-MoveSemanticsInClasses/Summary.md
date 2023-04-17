.Move semantics is not passed through.

.For every class, the move constructor and move assignment operator are automatically generated(unless thers is no way to do so).

.User-declaring a copy constructor, copy assignment operator, or destructor disables the automatics support
of move semantics in a class, This does not impact the support in derived classes.

.User-declaring a move constructor or move assignment operator disables the automatic support of copy semantics in a class.
You get move-only types(unless these special move member functions are deleted)

.Neve=delete a special move member function.

.Do no declare a structor if there is no specific need, There is no general need in classes derived from a polymorphic base class.
