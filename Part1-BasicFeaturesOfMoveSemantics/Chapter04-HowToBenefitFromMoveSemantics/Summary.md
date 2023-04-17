.Avoid object with names.

.Avoid unnecessary std::move, Especially do not use it when returning a local object.

.Constructor that initialize members form parameter, for which move operations are cheap, should take
the argument by value and move it to the member.

.Constructors that initialized members from parameters. for which move operations take a significant
amount of time, should be overloaded for move semantics for best formance.

.In general, creating and initlializing new values form parameters, for which move operations are cheap,
should take the arguments by value and move, However, do not take by value and move to update/modify 
existing values.

.Do not declare a virtual destructor in derived classes(unless you have to implement it )
