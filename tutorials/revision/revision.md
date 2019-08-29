# Initialiser List
The parameters of the initialiser list need to be in the correct order.  
# Function overloading
You cannot distinguish function overloads via return types, they must be distinguished using
function parameters.

# C++ STL
An iterator in the context of C++ STL is an abstraction of a pointer that represents a container
in a linear form.

Iterators requires less syntatic changes (no explicit dereferencing via *) and references cannot
be set to NULL, allowing for greater safety.

Iterators do **not** use less memory than pointers.

Q8) 3 Components of STL: What is benefit of using STL
- Iterators, Containers and Algorithms
- Algorithms not needing to know about iterators

# lvalues and rvalues
lvalues is something that points to a specific memory location.
In general, rvalues are temporary and shortlived and do not have a memory location

Example: 
int var
var = 4

The left hand side is an lvalue that has an identifiable position in memory when the variable is 
declared. The right hand side value of 4 does not have any identifiable position in memory.

This assignment expression expects an lvalue as its left operand and a rvalue as its right. The
following would not work

4 = var

Q5) Usage1:rvalue, Usage2:lvalue, Usage3: lvalue

Q6) Delegating constructor calls itself.


# Static Polymorphism
[Webcms excerpt]
Static polymorphism/templates are a form of generic programming that allows us to define types and
operations that provide functionality independent of the underlying type they operate on.

They allow us to provide the same capability for a range of "generic" types without redefining
code.

Sounds like containers - which are probably an example of static polymorphism.

C++ polymorphism means that a call to a member function will cause a different function to be 
executed depending on the type of object that invokes the function.

Q9) Non-type parameter

template 
auto createDefaultArray(int size) {
  return std::make_unique(size);
}

template 
auto createDefaultArray() {
  return std::make_unique(size);
}
