#include "tutorials/week3/dictionary_library.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

// TODO(tutors): Discuss how the use of istream instead of ifstream improves ease of testing.
std::vector<std::string> ToWordList(std::istream& input) {

	// istream = input stream
	// istream_iterator = reads successive objects of type T (in this case std::string)
	return {std::istream_iterator<std::string>{input}, std::istream_iterator<std::string>{}};

	// by default cpp can only return 1 value, but you can return multiple values if you
	// wrap them into a class or object using {}
	//
	// this allows the return value to be both a word list and string

}

// We only ever pass std::cin and std::cout to input and output respectively.
// TODO(tutors): Discuss why we don't just use std::cin and std::cout with respect to testing.
void PrintValidWords(const std::vector<std::string>& valid_words,
                     std::istream& input,
<<<<<<< HEAD
                     std::ostream& output) {

	std::copy_if(
			std::istream_iterator<std::string>{input},
			std::istream_iterator<std::string>{},
			std::ostream_iterator<std::string>{output, " "},
			[&] (const std::string& s) {
				return std::find(valid_words.begin(), valid_words.end(), s) != valid_words.end();
			});

	// use standard algorithms to split the string into words, filtered to only words in the 
	// word_dict and reconstruct this into a string
	//
}
=======
                     std::ostream& output) {}
>>>>>>> upstream/master
