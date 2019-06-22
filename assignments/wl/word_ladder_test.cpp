/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

  Main testable functionality of the word_ladder assignment involves ensuring that
  the algorithm develops the correct output, and making sure that the outputs involving
  multiple paths are printed out in alphabetical order.

  The following tests aim to make sure the algorithm produces the correct output
  regardless of length of ladders and outputs the orders in alphabetical order.

  Testing a 1 path, 1 movement scenario
  Testing a 2 path, 2 movement scenario
  Testing a 2 path, 3 movement scenario
  Testing a 7 path, 10 movement scenario

  Testing edge and other cases for input is mostly not necessary because input
  will only involve lowercase alphabetical characters. Therefore, the only major test
  here is testing inputs without paths.

*/

#include "assignments/wl/word_ladder.h"
#include "catch.h"

// TODO(students): Fill this in.
SCENARIO("1 path, 1 movement scenario") {
  GIVEN("start: cat, finish: car") {
    std::string start = "cat";
    std::string finish = "car";
    REQUIRE(start.size() == finish.size());

    std::unordered_set<std::string> lexicon = {"cat",
                                               "car",
                                               "work",
                                               "worm",
                                               "form",
                                               "foam",
                                               "hello",
                                               "goodbye",
                                               "whale",
                                               "trait",
                                               "trams"
                                               "heals",
                                               "heads",
                                               "brawn",
                                               "brain",
                                               "train",
                                               "hells",
                                               "beads",
                                               "brads",
                                               "braws",
                                               "brawn"};

    WHEN("Word ladder has been generated") {
      std::unordered_set<std::string> same_length_lexicon = SameLengthGen(start, lexicon);
      std::vector<std::vector<std::string>> returned = BFSAlgorithm(start, finish, lexicon);
      std::vector<std::vector<std::string>> expected;

      THEN("Check that returned values are correct") {
        expected.push_back({"cat", "car"});
        REQUIRE(returned.size() == expected.size());
        REQUIRE(returned == expected);

        // checking each individual word in returned vs expected
        for (int i = 0; i < static_cast<int>(expected.size()); i++) {
          REQUIRE(returned[i] == expected[i]);
          REQUIRE(returned[i].size() == expected[i].size());
        }
      }
    }
  }
}

SCENARIO("2 path, 2 movement scenario") {
  GIVEN("start: cat, finish: ear") {
    std::string start = "cat";
    std::string finish = "ear";
    REQUIRE(start.size() == finish.size());

    std::unordered_set<std::string> lexicon = {"cat",
                                               "car",
                                               "work",
                                               "worm",
                                               "form",
                                               "foam",
                                               "hello",
                                               "goodbye",
                                               "whale",
                                               "trait",
                                               "trams"
                                               "heals",
                                               "heads",
                                               "brawn",
                                               "brain",
                                               "train",
                                               "hells",
                                               "beads",
                                               "brads",
                                               "braws",
                                               "brawn",
                                               "ear",
                                               "eat"};

    WHEN("Word ladder has been generated") {
      std::unordered_set<std::string> same_length_lexicon = SameLengthGen(start, lexicon);
      std::vector<std::vector<std::string>> returned = BFSAlgorithm(start, finish, lexicon);
      std::vector<std::vector<std::string>> expected;

      THEN("Check that returned values are correct") {
        expected.push_back({"cat", "car", "ear"});
        expected.push_back({"cat", "eat", "ear"});
        REQUIRE(returned.size() == expected.size());
        REQUIRE(returned == expected);

        // checking each individual word in returned vs expected
        for (int i = 0; i < static_cast<int>(expected.size()); i++) {
          REQUIRE(returned[i] == expected[i]);
          REQUIRE(returned[i].size() == expected[i].size());
        }
      }
    }
  }
}

SCENARIO("2 path, 3 movement scenario") {
  GIVEN("start: work, finish: foam") {
    std::string start = "work";
    std::string finish = "foam";
    REQUIRE(start.size() == finish.size());

    std::unordered_set<std::string> lexicon = {"cat",
                                               "car",
                                               "work",
                                               "worm",
                                               "form",
                                               "foam",
                                               "hello",
                                               "goodbye",
                                               "whale",
                                               "trait",
                                               "trams"
                                               "heals",
                                               "heads",
                                               "brawn",
                                               "brain",
                                               "train",
                                               "hells",
                                               "beads",
                                               "brads",
                                               "braws",
                                               "brawn",
                                               "ear",
                                               "eat",
                                               "fork"};

    WHEN("Word ladder has been generated") {
      std::unordered_set<std::string> same_length_lexicon = SameLengthGen(start, lexicon);
      std::vector<std::vector<std::string>> returned = BFSAlgorithm(start, finish, lexicon);
      std::vector<std::vector<std::string>> expected;

      THEN("Check that returned values are correct") {
        expected.push_back({"work", "fork", "form", "foam"});
        expected.push_back({"work", "worm", "form", "foam"});
        REQUIRE(returned.size() == expected.size());
        REQUIRE(returned == expected);

        // checking each individual word in returned vs expected
        for (int i = 0; i < static_cast<int>(expected.size()); i++) {
          REQUIRE(returned[i] == expected[i]);
          REQUIRE(returned[i].size() == expected[i].size());
        }
      }
    }
  }
}

SCENARIO("7 path, 9 movement scenario") {
  GIVEN("start: hello, finish: train") {
    std::string start = "hello";
    std::string finish = "train";
    REQUIRE(start.size() == finish.size());

    std::unordered_set<std::string> lexicon = {
        "cat",   "car",   "work",  "worm",  "form",  "foam",  "hello", "goodbye", "whale", "trait",
        "trams", "heals", "heads", "brawn", "brain", "train", "hells", "beads",   "brads", "braws",
        "brawn", "ear",   "eat",   "fork",  "bells", "belts", "beats", "brats",   "heats", "teals",
        "teams", "trams", "traps", "trans", "trank", "traik", "trapt", "trait",   "tells"};

    WHEN("Word ladder has been generated") {
      std::unordered_set<std::string> same_length_lexicon = SameLengthGen(start, lexicon);
      std::vector<std::vector<std::string>> returned = BFSAlgorithm(start, finish, lexicon);
      std::vector<std::vector<std::string>> expected;

      THEN("Check that returned values are correct") {
        expected.push_back({"hello", "hells", "bells", "belts", "beats", "brats", "braws", "brawn",
                            "brain", "train"});
        expected.push_back({"hello", "hells", "heals", "heads", "beads", "brads", "braws", "brawn",
                            "brain", "train"});
        expected.push_back({"hello", "hells", "heals", "heats", "beats", "brats", "braws", "brawn",
                            "brain", "train"});
        expected.push_back({"hello", "hells", "heals", "teals", "teams", "trams", "trans", "trank",
                            "traik", "train"});
        expected.push_back({"hello", "hells", "heals", "teals", "teams", "trams", "traps", "trapt",
                            "trait", "train"});
        expected.push_back({"hello", "hells", "tells", "teals", "teams", "trams", "trans", "trank",
                            "traik", "train"});
        expected.push_back({"hello", "hells", "tells", "teals", "teams", "trams", "traps", "trapt",
                            "trait", "train"});

        REQUIRE(returned.size() == expected.size());
        REQUIRE(returned == expected);

        // checking each individual word in returned vs expected
        for (int i = 0; i < static_cast<int>(expected.size()); i++) {
          REQUIRE(returned[i] == expected[i]);
          REQUIRE(returned[i].size() == expected[i].size());
        }
      }
    }
  }
}

SCENARIO("No path exists") {
  GIVEN("start: airplane, finish: tricycle") {
    std::string start = "airplane";
    std::string finish = "tricycle";
    REQUIRE(start.size() == finish.size());

    std::unordered_set<std::string> lexicon = {"cat",
                                               "car",
                                               "work",
                                               "worm",
                                               "form",
                                               "foam",
                                               "hello",
                                               "goodbye",
                                               "whale",
                                               "trait",
                                               "trams"
                                               "heals",
                                               "heads",
                                               "brawn",
                                               "brain",
                                               "train",
                                               "hells",
                                               "beads",
                                               "brads",
                                               "braws",
                                               "brawn",
                                               "ear",
                                               "eat",
                                               "fork",
                                               "airplane",
                                               "tricycle"};

    WHEN("Word ladder has been generated") {
      std::unordered_set<std::string> same_length_lexicon = SameLengthGen(start, lexicon);
      std::vector<std::vector<std::string>> returned = BFSAlgorithm(start, finish, lexicon);
      std::vector<std::vector<std::string>> expected;

      THEN("Check that returned values are correct") {
        REQUIRE(returned.size() == expected.size());
        REQUIRE(returned == expected);

        // checking each individual word in returned vs expected
        for (int i = 0; i < static_cast<int>(expected.size()); i++) {
          REQUIRE(returned[i] == expected[i]);
          REQUIRE(returned[i].size() == expected[i].size());
        }
      }
    }
  }
}
