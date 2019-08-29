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
a = 
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
- Move and copy semantics are handled for us

# Sharedptr vs uniqueptr

Shared ptr preferred over unique ptr if
- There is shared ownership (very rare, usually one owner and many observers)
- There is a single owner but the observers may stick around longer than the owner

When we have ownership loops (graph that isnt a dag - directed acyclic graph) two options:
- Preferred: std::vector<std::unique_ptr<Node>> and each node stores raw pointers to other
nodes. (This may not be possible if it's hard to find all the raw pointers and remove them when 
you delete the unique pointer.)

- Otherwise: std::vector<std::shared_ptr<Node>> and each node stores weak pointers to other
nodes. (Do not store shared pointers in each node)


