#include "game_loop.hh"

#include <iostream>
#include <string>
#include <vector>

using std::priority_queue;
using std::string;
using std::vector;

std::vector<std::string> updated_word_list = word_list;
bool end_game = false;

void pattern_from_pattern_index(int (&pattern)[5], int pattern_index) {
  int k = 4;
  while (pattern_index > 0) {
    pattern[k] = pattern_index % 3;
    pattern_index = pattern_index / 3;
    k--;
  }
  printf("\n");
  /*To test pattern correctness
   * for (auto p : pattern) {
    printf("%d ", p);
  }*/
}

void update_word_list(int pattern_index, string &input_word) {
  vector<string> local_list;
  for (auto word : updated_word_list) {
    Word candidate_word;
    candidate_word.word = input_word;
    if (pattern_matcher(candidate_word, word) == pattern_index) {
      local_list.push_back(word);
    }
  }
  printf("\nNew List size : %d\n", local_list.size());
  updated_word_list = local_list;
}
void pattern_color_display(int (&pattern)[5]) {
  for (auto p : pattern) {
    if (p == 1) {
      printf("\033[1;43m _ \033[0m");
      printf(" ");
    } else if (p == 2) {
      printf("\033[1;42m _ \033[0m");
      printf(" ");
    } else {
      printf("\033[1;40m _ \033[0m");
      printf(" ");
    }
  }
}
void game_loop(const string &hidden_word) {
  printf("\n_ _ _ _ _\n");
  string input_word;
  std::cin >> input_word;
  Word iw;
  iw.word = input_word;
  int pattern_index = pattern_matcher(iw, hidden_word);
  if (pattern_index == 242) {
    end_game = true;
  }
  // printf("%d", pattern_index);
  int pattern[5] = {0};
  pattern_from_pattern_index(pattern, pattern_index);
  pattern_color_display(pattern);
  printf("\n_ _ _ _ _\n");
  update_word_list(pattern_index, input_word);
}

void game_loop(const string &hidden_word, const string &current_guess) {
  printf("\n_ _ _ _ _\n");
  string input_word = current_guess;
  // std::cin >> input_word;
  printf("\n_ _ _ _ _\n");
  Word iw;
  iw.word = input_word;
  int pattern_index = pattern_matcher(iw, hidden_word);
  if (pattern_index == 242) {
    end_game = true;
  }
  printf("%d", pattern_index);
  int pattern[5] = {0};
  pattern_from_pattern_index(pattern, pattern_index);
  pattern_color_display(pattern);
  update_word_list(pattern_index, input_word);
}
