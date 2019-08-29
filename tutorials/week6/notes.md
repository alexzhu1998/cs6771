# Week 6
I think this week we focus on exceptions and continued study of smart pointers

1. C++ exceptions
std::invalid-argument
std::out-of-bounds

2. An example of a case where we'd want to rethrow an exception is when you aren't interested in
managing a caught exception, but you would like to log something to do with an exception.

3. Two catch statements for a thrown exception: 
When we have some type specific exceptions to catch (out-of-range) but also want to handle other
exceptions (known or unknown) in other cases. Eg, length-error or exception

4. We use a shared pointer instead of a unique pointer when we are unsure which of a series of
pointers (to a single resource) will have the longest lifetime. If it's known it will outlast the
others, use a unique pointer with a number of observers.

[Google]
A stack frame is the collection of all information on the stack pertaining to a subprogram call.
In general this includes:
- parameters that are passed into the subprogram
- return address after the subprogram has finished running
- EBP (extended base pointer)
- local variables within the scope of the subprogram

A subprogram is any component of a program - main function, individual functions, etc.

# Stack Unwinding

5. Stack unwinding is the process of exiting the stack frames until we can find an exception 
handler for the funcion.

During this process, destructors are called on relevant objects on the way out; and any 
exceptions (known or unknown) thrown on a destructor (that aren't caught and handled) cause 
std::terminate to be called.

This can cause the inappropriate release of resources that were allocated before an allocation
throw. The solution to this is to ensure that every resource is owned by another resource/stack
or unnamed temporary variable.

6. 4 Exception Safety Levels:
- No-throw (failure transparency): operations guaranteed to succeed
- Strong exception safety (commit or rollback): operations can fail, but failed operations will
have no side effects
- Weak exception safety (no leak): may cause side effects, but no memory leaks will occur.
- No exception safety

Guarantee success -> side effects -> memory leaks -> no safety

7. Constructor is not finished when the exception is thrown. And if an exception is thrown 
because no string was provided for the name, the destructor will not get called.

We can use a uniqueptr instead of a raw * pointer. While the object is not fully constructed,
the subobjects (int* ptr and std::string name) will be. So this will solve the issue.

You could also ensure that any potential exceptions are thrown before we obtain resources.
You can do this by swapping the order ptr_ and name_ and ensure that the exception is thrown in 
the initialiser list.




