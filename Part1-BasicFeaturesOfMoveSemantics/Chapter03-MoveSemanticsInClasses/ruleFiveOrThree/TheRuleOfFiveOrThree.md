Rule of Five or Three:

.If you declare the copy constructor, move constructor.copy assignment operator, move assignment operator,
or destructor, think very carefully about how to deal with other special member functions.

.If you do not understand move semantics, think only about the copy constructor, copy assignment operator,
and destructor if you are declaring one of them, If in doubt, disable move semantics by declaring the 
copying special member functions with =default.

