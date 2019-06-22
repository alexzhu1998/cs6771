#include "assignments/wl/word_ladder.h"

// TODO(students): Add your stuff here

// print ladder
void PrintLadder(std::vector<std::string> ladder ) {
  for (auto& word: ladder) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}

// function that generates a vector of one different character using same length
std::vector<std::string> DifferentLetterGen(std::string start, 
                                            std::vector<std::string> same_length_lexicon) {

  std::vector<std::string> permutations;
  const std::string original = start;

  // have a count for the number of characters which are different
  // if they are more than 1, break immediately and move to the next
  // letter in the same_length_lexicon

  // for every word in the same_length_lexicon
  for (auto& target : same_length_lexicon) {
    int differences = 0;
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

  return permutations;
}

// bfs algorithm, takes in start word, same_length_lexicon, results (by reference)
std::vector<std::vector<std::string>> BfsAlgorithm(std::string start, std::string finish, std::vector<std::string> same_length_lexicon) {
  
  // queue of ladders
  std::queue<std::vector<std::string>> ladders_queue;  
  // pqueue of vector strings to store result ladders
  std::priority_queue<std::vector<std::string>, 
                      std::vector<std::vector<std::string>>, 
                      std::greater<std::vector<std::string>>> results;

  // setting up ladder queue with initial permutation of word
  auto initial_permutations = DifferentLetterGen(start, same_length_lexicon);
  for (auto &p : initial_permutations) {
    std::vector<std::string> temp;
    temp.push_back(start);
    temp.push_back(p);
    ladders_queue.push(temp);
  }

  // ACTUAL MEAT OF THE BFS
  int shortest_size = MAX_LENGTH;
  while (ladders_queue.empty() == false) {
    std::vector<std::string> front_of_queue = ladders_queue.front();
    PrintLadder(front_of_queue);
    
    // if greater than the shortest size, break
    if (int(front_of_queue.size()) > shortest_size) 
      break;

    // if the back of the front_of_queue is 
    // equal to finish add to results vector
    if (front_of_queue.back() == finish) {
      results.size();
      results.push(front_of_queue);
      shortest_size = front_of_queue.size();
      
    } else {
      // re-permute using the end of the vector to create more variations
      auto permutations = DifferentLetterGen(front_of_queue.back(), same_length_lexicon);
      for (auto &p : permutations) {
        // copying contents from vector in front to new vector
        std::vector<std::string> temp = front_of_queue;
        // adding all possible combinations of p to end of new vector
        temp.push_back(p);
        // pushing new vector to end of ladders queue
        ladders_queue.push(temp);
      }
    }
    ladders_queue.pop();
  }

  // convert priority queue into vector of vector strings
  std::vector<std::vector<std::string>> results_vector;
  while (results.empty() == false) {
    results_vector.push_back(results.top());
    results.pop();
  }

  return results_vector;
}