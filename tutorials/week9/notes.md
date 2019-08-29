# Week 9

Specialised classes
- We do not specialise functions because:
	* Specialising functions can have unintended behaviour
	* We already have this capability in the form of function overloading
- We specialise classes when we need to either:
	* Preserve a particular semantic for something that would not work otherwise
	* Make an optimisation for a specific type

2. 

3.

4. An xvalue is an rvalue that is about to expire, as a result of std::move

5. prvalue is an rvalue that is not an xvalue. So an rvalue that is not about to
expire

# Decltype
decltype: inspects the declared type of an entity or the type and value category
of an expression. 

It is a way to specify a type. You give it an expression and decltype gives you
back a type which corresponds to the type of the expression.

6.
int main() {
  int i = 5;
  int& k = i;

  decltype(i) x; // int - variable
  decltype(k) y; // int& - lvalue
  decltype(std::move(i)) z; // int&& - xvalue
  decltype(4.2); // int - prvalue
}

