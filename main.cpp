#include "engine.hh"
#include "word_list.hh"

#include <iostream>
#include <string>
#include <unordered_map>
using std::priority_queue;
using std::string;
using std::unordered_map;
using std::vector;

vector<string> updated_word_list;
void pattern_from_pattern_index(int[] & pattern, int pattern_index) {
  int k = 4;
  while (pattern_index > 0) {
    pattern_index = pattern_index / 3;
    pattern[k] = pattern_index % 3;
    k--;
  }
}

void game_loop() {
  string input_word;
  int pattern_index = pattern_matcher(input_word, hidden_word);
  printf("\n %d", pattern_index);
  int pattern[5] = {0};
  pattern_from_pattern_index(pattern, pattern_index);
  update_word_list(pattern);
}
bool check_word(string word) {
  for (int i = 0; i < 5; i++) {
    if (pattern[i] == 0)
  }
}
void update_word_list(int[] & pattern) {
  vector<char> grey_chars;
  vector<char> yellow_chars;
  vector<char> green_chars;
  for (int i = 0; i < 5; i++) {
    if (pattern[i] == 0) {
      grey_chars.push_back(word[i]);
    } else if (pattern[i] = 1) {
      yellow_chars.push_back(word[i]);
    } else {
      green_chars.push_back(word[i]);
    }
  }
  for (auto word : word_list) {
    for (auto c : word) {
    }
  }
}
int main() {
  float max_entropy = -1.0f;
  string max_entropy_word = "";
  float entropy = 0.0f;
  priority_queue<Word, vector<Word>, CompareEntropy> ranking_list;
  int index = 1;
  for (auto guess_word : word_list) {
    Word gw;
    gw.word = guess_word;
    entropy = entropy_for_word(gw);
    ranking_list.push({guess_word, entropy});
  }
  while (!ranking_list.empty()) {
    std::cout << ranking_list.top().word << " : " << ranking_list.top().entropy
              << std::endl;
    ranking_list.pop();
  }
  // string input_word;
  // what pattern will to show?

  /* Word gw;
   gw.word = "adobe";
   std::cout << entropy_for_word(gw);*/
  return 0;
}
