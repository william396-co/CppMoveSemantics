.For each class, clarify the state of moved-from objects, You have to ensure they are at least 
 destructible(which is usually the case without implementating special member functions). However, 
 users of you class might expect/require more.

 .The requirements of functions of the C++ standard library alos apply to moved-from objects.

 .Generated special move member functions might bring moved-from objects into a state such that a
 class invariants is broken. This is might happen especially if:

-- Classes have no default constructor with a determinate value(and therefore no natural moved-from
 state)

 -- Values of members have restrictions(such as assertions)
 -- Values of members depend on each other
 -- Member with pointer-like semantics are used(pointers, smart pointers, etc.)

 . If the moved-from state breaks invariants or invalidates opertions, you should fix this by using
 one of the following option:

 -- Disable move semantics
 -- Fix the implementation of move semantics
 -- Deal with broken invariants inside the class and hide them to the outside 
 -- Relax the invariants of the class by documenting the constriants and precodition for moved-from
 objects
