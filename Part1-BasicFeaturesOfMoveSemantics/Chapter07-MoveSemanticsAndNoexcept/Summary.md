. With noexcept, you can declare a (conditional)guaranetee not to throw.

. If you implemnt a move constructor, move assignment operator , or swap(), declare it witha
 a(conditional)noexcept expression.

. For other functions, you might just want to mark them with an unconditonal noexcept if they never
throw.

. Destrcutors are always declared with noexcept(even when implemented).
