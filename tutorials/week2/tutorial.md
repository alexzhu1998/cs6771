# Tutorial 2 Answers

2. Iterators are used to point to the memory addresses of STL containers.
If the STL container is an object, then an iterator is a method for the object to access part
of the object's data. (container)

- An input iterator allows read and increment. However it cannot make multiple passes when
incrementing - An output iterator allows write and increment. ^^ same as above.
- A forward iterator allows read, write and increment
- A bidirectional iterator allows read, write, increment and decrement
- A random access iterator allows read, write, increment decrement, +x, and -x.

Multiple passes means you can read an old value of an iterator
- Does that mean a single pass can only read the value of an iterator once?

```
Think like you can do 	(vector.begin())++; 		- for increment eg
				 and like 	vector.begin() = foo; 	- for a write example
				 read means you can only read and you can't modify that value

				 They act essentially as permissions for the "methods" used to access containers

```

3. 2 ways you can go about this:
* Use a list of <int> types, and find the medianIndex using .size() / 2
* Use a vector and perform .at(2) to find median

4. Const iterator do not allow modification of the value the iterator refers to.

5. To iterate in the reverse direction:
* start the for loop at the temperature.size() - 1
* finish the loop at i > = 0
* use the --i iterator to decrement the index

* use crbegin and crend - r indicates a reverse iterator

for (auto iter = temperatures.crbegin(); iter != temperatures.crend(); ++iter) {
}

6. 

```
const std::vector<int> vec;
std::list<int> li;
std::forward_list<double> forward_li;
std::string s;

vec.begin(); 							// const random access iterator
vec.cbegin();							// const random access iterator
(*vec.begin())++;						// fail to compile because vector is const, this line
											// tries to modify that value, which is now allowed
li.cbegin();							// const bidirectional iterator
li.rbegin();							// non-const bidirectional iterator
forward_li.cbegin();					// const forward iterator
(*forward_li.cbegin())++;			// forward iterator
forward_li.crbegin();				// fails to compile because it modifies non-const iterator
s.begin();								// non-const random access iterator
std::back_inserter(vec);			// Compiles. Can't invoke the dereference operator to insert
											// anything because you'll get a compile time error (???)
std::back_inserter(li); 			// Output iterator
std::istream_iterator<int>(std::cin); 			// input iterator
std::ostream_iterator<int>(std::cout, " "); 	// output iterator

```

7.

Function overloading - the ability to create multiple functions of the same name with
different implementation, calls of the overloaded functions will run the specific 
implementation of that function appropriate to the context of the call.

Change the function names to be the same

8.
```
template <typename T>
T min<T a, T b> {
	return a < b ? a : b;
}

```

9. maps - a hashmap/dictionary is an unordered data structure containing a list of items

10. Each container defines an iterator which acts as an API which is used by algorithms.
Algorithms, which despite knowing nothing about the containers, are able to access them
through zero-overhead abstractions through iterators.

The relationship is very important, since it allows us to write generic code that doesn't
need to be rewritten and retested for different types. It also means we can swap out types
without the need to make any changes.

It relates to the Don't Repeat Yourself principle in that we need to write m Containers +
n algorithms instead of m containers * n algorithms. (good point)
