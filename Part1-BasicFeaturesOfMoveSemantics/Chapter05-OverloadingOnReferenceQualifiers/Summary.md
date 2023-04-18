.You can overload member functions on different reference qualifiers.

.Overload getters for expensive members with reference qualifiers to make them both safe and fast(const&, &&).

.It can make sense to mark objects with std::move() even when calling member functions.

.Use reference qualifier in assignment operators
