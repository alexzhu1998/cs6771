#include "assignments/wl/word_ladder.h"

// TODO(students): Add your stuff here

// print ladder
void PrintLadder(std::vector<std::string> ladder) {
  for (auto& word : ladder) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}

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

// function that generates a vector of one different character using lexicons with same length
std::vector<std::string> DifferentLetterGen(std::string start,
                                            std::unordered_set<std::string> same_length_lexicon) {
  std::vector<std::string> permutations;
  const std::string original = start;

  // have a count for the number of characters which are different
  // if they are more than 1, break immediately and move to the next
  // letter in the same_length_lexicon

  // for every word in the same_length_lexicon
  for (auto& target : same_length_lexicon) {
    int differences = 0;
    // for every character in the length of the words/sl.lexicon
    for (int i = 0; i < static_cast<int>(start.size()); i++) {
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

// separate function because the results need to be generated/recursed.
void generateResults(std::string& start,
                     std::string last,
                     std::unordered_map<std::string, std::vector<std::string>>& map,
                     std::priority_queue<std::vector<std::string>,
                                         std::vector<std::vector<std::string>>,
                                         std::greater<std::vector<std::string>>>& results,
                     std::vector<std::string>& path) {
  if (last == start) {
    reverse(path.begin(), path.end());
    results.push(path);
    reverse(path.begin(), path.end());
  } else {
    for (int i = 0; i < static_cast<int>(map[last].size()); i++) {
      path.push_back(map[last][i]);
      generateResults(start, map[last][i], map, results, path);
      path.pop_back();
    }
  }
}

// bfs algorithm, takes in start word, same_length_lexicon
std::vector<std::vector<std::string>> BFSAlgorithm(
    std::string start, std::string finish, std::unordered_set<std::string> same_length_lexicon) {

  // bfs setup
  // 1. unorderedmap < str, vec<str>> - to map current words to previously visited
  // 2. priority_queue of vector strings to hold results - allows alphabetical insertion
  // 3. vector string: path - the vector string that valid paths will be recursed back into
  std::unordered_map<std::string, std::vector<std::string>> map;
  // pqueue of vector strings to store result ladders
  std::priority_queue<std::vector<std::string>, std::vector<std::vector<std::string>>,
                      std::greater<std::vector<std::string>>>
      results;
  std::vector<std::string> path;

  // the backtracing solution involves storing previous paths in a unordered_map(hashmap),
  // each depth of movement will be stored in an unordered_set for memory management
  // the next depth of movement contains the word to be found, it will generate all the
  // previous movements from the previous paths stored in the unordered_map, recursively

  std::unordered_set<std::string> current_depth;
  std::unordered_set<std::string> next_depth;
  current_depth.insert(start);
  path.push_back(finish);

  // real meat of the BFS
  while (true) {
    for (auto& word : current_depth) {
      same_length_lexicon.erase(word);
    }
    for (auto& word : current_depth) {
      // for all permutations with one letter difference:
      // next_ladder.insert(permutations)
      // map[permutations].push_back(word)
      auto permutations = DifferentLetterGen(word, same_length_lexicon);
      for (auto& p : permutations) {
        next_depth.insert(p);
        map[p].push_back(word);
      }
    }

    if (next_depth.empty())
      break;

    // if finish word is found in the next ladder, generate results recursively
    if (next_depth.find(finish) != next_depth.end()) {
      generateResults(start, finish, map, results, path);
      break;
    }
    current_depth = next_depth;
    next_depth.clear();
  }

  // convert priority queue into vector of vector strings
  std::vector<std::vector<std::string>> results_vector;
  while (results.empty() == false) {
    results_vector.push_back(results.top());
    results.pop();
  }

  return results_vector;
}
