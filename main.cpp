#include "engine.hh"
#include "game_loop.hh"
#include "ranking.hh"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
using std::priority_queue;
using std::string;
using std::vector;

string hidden_word;
void random_target_selection() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, word_list.size());
  hidden_word = word_list[dist(gen)];
}
void taking_valid_custom_input() {
  string input_target_word;
  while (true) {
    bool valid_input = false;
    std::cout << "Input a valid 5-letter string\n";
    std::cin >> input_target_word;
    bool found =
        binary_search(word_list.begin(), word_list.end(), input_target_word);
    if (found) {
      hidden_word = input_target_word;
      break;
    } else {
      std::cout << "Sighhh!!!\nTry Again\n";
    }
    // Better to just check if work exists in list rather than check for
    // constraints
    /*if(input_target_word.size()==5){
      bool contains_alphachar =
    find_if(input_target_word.begin(),input_target_word.end(),[](char c){return
    !is_alpha(c);})!=input_target_word.end(); if(!contains_alphachar){
            }
    }
    }*/
  }
}
int limit = 0;
int main() {
  std::cout << "Welcome!\n";
  std::cout
      << "This is an assisted wordle game, where a bot will play with you and "
         "suggest you with best word to play!\n\n";
  std::cout << "You can choose any word from given list of possible words, "
               "more the entropy earlier you finish the game!\n";
  /*
   *TODO: user interaction improvement
   */
  std::cout << "How do you want to play the game?(input 1 or 2)\n";
  std::cout << "1. Play with a Random Target Word!\n";
  std::cout << "2. Play with your own Target Word!\n";
  int game_type = 0;
  while (true) {
    bool try_again = false;
    std::cin >> game_type;
    switch (game_type) {
    case 1:
      printf("Starting a game with Random Target word\n");
      random_target_selection();
      break;
    case 2:
      printf("Starting a custom game\n");
      taking_valid_custom_input();
      break;
    default:
      printf("Invalid Input. Try again!\n");
      try_again = true;
    }
    if (!try_again)
      break;
  }

  limit = 0;

  std::cout << "\t\t\t\t" << "Possible Words\n\n";
  for (auto it : ranking_list) {
    std::cout << "\t\t\t\t" << it.word << " : " << it.entropy << std::endl;
    if (limit == 20) {
      break;
    }
    limit++;
  }
  for (int i = 0; i < 6; i++) {
    game_loop(hidden_word);
    if (end_game) {
      end_game = false;
      break;
    }
    float max_entropy = -1.0f;
    string max_entropy_word = "";
    float entropy = 0.0f;
    priority_queue<Word, vector<Word>, CompareEntropy> rank_list;
    int index = 1;
    for (auto guess_word : updated_word_list) {
      Word gw;
      gw.word = guess_word;
      entropy = entropy_for_word(gw, updated_word_list);
      rank_list.push({guess_word, entropy});
    }
    limit = 0;
    std::cout << "\t\t\t\t" << "Possible Words\n\n";
    while (!rank_list.empty() && limit < 20) {
      std::cout << "\t\t\t\t" << rank_list.top().word << " : "
                << rank_list.top().entropy << std::endl;
      rank_list.pop();
      limit++;
    }
  }
  // testing_performance();
  // performance_result();
  //  string input_word;
  //  what pattern will to show?

  /* Word gw;
   gw.word = "adobe";
   std::cout << entropy_for_word(gw);*/
  return 0;
}
//         ---->ranking_list.hh
// main.cpp|--->engine.hh->word_list.hh
// engine.cc----^
