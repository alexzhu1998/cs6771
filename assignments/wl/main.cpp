#include <iostream>

// custom #includes
#include <string>
#include <vector>
#include <queue>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"


// print ladder
void printLadder(std::vector<std::string> ladder ) {
  for (auto& word: ladder) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}

// function that generates a vector of same length
std::vector<std::string> sameLengthGen(std::string start, 
                                       std::unordered_set<std::string> lexicon) {
  
  std::vector<std::string> same_length_lexicon;

  for (auto& word : lexicon) {
    // check if the length is the same
    if (word.size() == start.size()) {
      same_length_lexicon.push_back(word);
    }
  }

  return same_length_lexicon;
}

// function that generates a vector of one different character using same length
// should take in same_length_lexicon
std::vector<std::string> differentLetterGen(std::string start, 
                                            std::vector<std::string> same_length_lexicon) {

  std::vector<std::string> permutations;
  const std::string original = start;


  // have a count for the number of characters which are different
  // if they are more than 1, break immediately and move to the next
  // letter in the same_length_lexicon

  // for every word in the same_length_lexicon
  for (auto& target : same_length_lexicon) {
    int differences = 0;
    std::cout << "target = " << target << "\n";
    // for every character in the length of the words/sl.lexicon
    for (int i = 0; i < int(start.size()); i++) {
      if (start[i] != target[i]) {
        differences++;
        if (differences > 1)
          break;
      }
    }

    if (differences == 1) {
      permutations.push_back(target);
    }
  }

  // // for each letter in start
  // for (auto& letter : start) {
  //   // for a range between 0 and 26
  //   for (int i=0; i < 25; i++) {
  //     letter++;
  //     // if ascii passes 122 "z", reset to 97 "a"
  //     if (int(letter) > 'z') {
  //       letter = 'a';
  //     }
  //     permutations.push_back(start);
  //   }
  //   letter++;
  //   if (int(letter) > 'z') {
  //     letter = 'a';
  //   } 
  // } 
  // // run permutations through dictionary to determine which are words
  // // TODO: don't use primitive pointers
  // for (auto p = permutations.begin(); p != permutations.end(); ) {
  //   auto search_lexicon = lexicon.find(*p);
  //   if (search_lexicon == lexicon.end()) {
  //     // not found, remove from permutations
  //     permutations.erase(p);
  //   } else {
  //     p++;
  //   }
  // }

  return permutations;
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

  // this may all be handled by word_ladder.cpp in the future

  // queue of vectors to store ladders
  std::queue<std::vector<std::string>> q;
  // vector of vector strings to store valid ladders
  std::vector<std::vector<std::string>> results;

  auto same_length_lexicon = sameLengthGen(start, lexicon);
  auto initial_permutations = differentLetterGen(start, same_length_lexicon);
  printLadder(initial_permutations);
  // setting up queue with "ladders" using vector container
  for (auto &p : initial_permutations) {
    std::vector<std::string> temp;
    temp.push_back(start);
    temp.push_back(p);
    q.push(temp);
  }

  // ACTUAL MEAT OF THE BFS
  while (q.empty() == false) {
    std::vector<std::string> front_of_queue = q.front();
    printLadder(front_of_queue);

    // if the back of the front_of_queue is equal to finish
    // add to results vector
    if (front_of_queue.back() == finish) {
      results.push_back(front_of_queue);
      break;
      
    // I think you also have to record the length of the vector as the minimum
    // so that you don't keep going to find longer paths afterwards
    } else {
      // re-permute using the end of the vector to create more variations
    auto permutations = differentLetterGen(front_of_queue.back(), same_length_lexicon);
    for (auto &p : permutations) {
        // copying contents from vector in front to new vector
        std::vector<std::string> temp = front_of_queue;
        // adding all possible combinations of p to end of new vector
        temp.push_back(p);
        // pushing new vector to end of queue
        q.push(temp);
      }
    }
    q.pop();
  }

  // keep track of what nodes visited

  // spew out output
  for (auto &ladder : results) {
    printLadder(ladder);
  }

}
