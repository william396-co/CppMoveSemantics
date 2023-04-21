The consequences for your code are as follow:

. You should implement the move constructor, the move assignment operator and a swap() function with a(conditional) noexcept

. For all other functions, mark them with an unconditonal noexcept only if you know that they cannot throw.

. Destructors do not need a noexcept specificiation
