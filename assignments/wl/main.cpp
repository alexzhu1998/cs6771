#include <iostream>
#include <string>
#include <unordered_set>

#define MAX_LENGTH 100

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

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
  auto results = BFSAlgorithm(start, finish, same_length_lexicon);

  if (static_cast<int>(results.size()) == 0) {
    std::cout << "No ladder found\n";
  } else {
    std::cout << "Found ladder: ";
    for (auto& r : results) {
      PrintLadder(r);
    }
  }
}
