# Week8

1. What is iterator invalidation?
Iterator invalidation occurs when a mutable operationg changes the state of a container in such a 
way that any previous iterators for the container are no longer valid.

This may occur simply because the object no longer exists - EG after using something like
std::set::erase because the iterator was stored internally as a pointer and the object has been
moved, or for some other reason.

EG - and just an idea - maybe you can use something like shrinktofit

2. Abstracting a container of containers as a single container - vector<vector<int>>
by storing an outer iterator and an inner iterator.

Some of the issues involved with this include:
- Comparing end iterators 
(no inner iterator exists, and trying to access one is undefined behaviour)
- ++ operator on an empty vector in the middle (if the outer iteraotr)
- begin() with an empty vector at the start

Solution: Store a sentinel value (you need to know when it's the end, so that you can know when 
not to check the inner iterator)
