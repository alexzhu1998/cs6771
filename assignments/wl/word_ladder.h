#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

// TODO(students): Add some stuff here

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#define MAX_LENGTH 100

void PrintLadder(std::vector<std::string>);
std::vector<std::string> DifferentLetterGen(std::string start, 
                                            std::vector<std::string> same_length_lexicon);
void generateResults(std::string &start, std::string last, 
                     std::unordered_map<std::string, std::vector<std::string>> &map,
                     std::priority_queue<std::vector<std::string>, 
                                         std::vector<std::vector<std::string>>, 
                                         std::greater<std::vector<std::string>>> &results,
                     std::vector<std::string> &path);
std::unordered_set<std::string> SameLengthGen(std::string start,
                                              std::unordered_set<std::string> lexicon);
std::vector<std::vector<std::string>> 
BFSAlgorithm(std::string start, 
             std::string finish, 
             std::unordered_set<std::string> same_length_lexicon);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
