#include <iostream>

// custom #defines
#define MAX_LENGTH 100

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"


// generates a filtered lexicon only containing words 
// with the same length as the start
std::unordered_set<std::string> SameLengthGen(std::string start, 
                                       std::unordered_set<std::string> lexicon) {
  
  std::unordered_set<std::string> same_length_lexicon;

  for (auto& word : lexicon) {
    // check if the length is the same
    if (word.size() == start.size()) {
      same_length_lexicon.insert(word);
    }
  }

  return same_length_lexicon;
}


int main() {

  // deprecated GetLexicon("assignments/wl/words.txt")
  auto lexicon = GetLexicon("words.txt");

  // TODO(students): Replace this with your code (thanks hayden)

  // take in input
  std::string start, finish;
  std::cout << "Enter start word (RETURN to quit): ";
  std::cin >> start;
  std::cout << "Enter destination word: ";
  std::cin >> finish;

  // Only lexicons of the same length are needed
  auto same_length_lexicon = SameLengthGen(start, lexicon);
  auto results = BfsAlgorithm(start, finish, same_length_lexicon);

  if (int(results.size()) == 0) {
    std::cout << "No ladder found\n";
  } else {
    std::cout << "Found ladder: ";
    for (auto &r : results) {
      PrintLadder(r);
    }
  }
}
