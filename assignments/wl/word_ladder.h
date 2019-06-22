#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

// TODO(students): Add some stuff here

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_set>

#define MAX_LENGTH 100

void PrintLadder(std::vector<std::string>);
std::vector<std::string> DifferentLetterGen(std::string start, 
                                            std::vector<std::string> same_length_lexicon);
std::vector<std::vector<std::string>> BfsAlgorithm(std::string start, std::string finish, std::unordered_set<std::string> same_length_lexicon);
std::vector<std::string> RemoveFromLexicon(std::vector<std::string> remove, 
                                           std::vector<std::string> lexicon);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
