# Constructors

Constructor (direct initialisation) - Preferred not to be used. Initialised with parameters passed
next to the name of the object.
std::vector<int> a(1, 2, 3) 

Constructor (uniform initialisation).
std::vector<int> a{1, 2, 3}
std::vector<int> b = {1, 2, 3}

Important to remember copy / move construction

- Copy constructor: 
class a = b
- Move constructor:
class a{std::move(b)}

And copy / move assignments (no instantiation required)

- Copy assignment
a = b
- Move assignment
a = std::move(b)

# Prefix increment/decrement
Prefix is generally preferred (when no copy is needed) because one less step (copy and return)
being completed. Will yield performance improvements at scale.

Postfix is used when you want to receive a copy of the object's current state prior to increment
/decrement occuring.

# Smart Pointers
Smart pointers mean:
- We do not have to worry about deleting our heap memory
- Move and copy semantics are handled for us (static polymorphism?)
