# Week 3 Tutorial Answers

1. What is a lamdba function?
Define an anonymous function - creating a function without having to physically create
a function. Used to demonstrate some code to be run, but treated more as a variable as
opposed to an actual function in compiled code.

std::vector<std::string> vec {"we", "love", "lambda", "expressions"};
std::sort(vec.begin(), vec.end(), [](const auto& lhs, const auto& rhs) {return lhs.size() < rhs.size();});

2. When writing a lambda function, when should you capture by value and when should you capture by reference?
* Value when variable may change and you want the variable at the current time
* Value when the lifetime of the lambda may exceed the lifetime of the variable
* Reference when the variable may change and you want to stay updated
* Reference when the variable is unabled to copy // too expensive to copy

3. 
a) Discuss why separating your functions you want to test is a good idea?
You can't test any file with a main function in it. Additionally, testing is much easier when you have
several small parts to test.

b) Assume that the word list and strings are very large - what do make it faster?
In theory you would use something like a linked list. A std::set would be faster, followed by a
std::binary_search on a std::vector and then a std::unordered_set.

c) Discuss the effect of automatic type deduction
When you change the type of the function, only the things that specifically declared their type had to be
changed. Anything that declared itself as auto was able to use the same constructors.

