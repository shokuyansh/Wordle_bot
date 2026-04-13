#include "engine.hh"
#include "ranking.hh"
#include <iostream>
#include <string>
#include <unordered_map>
using std::priority_queue;
using std::string;
using std::unordered_map;
using std::vector;
string hidden_word = "adore";
vector<string> updated_word_list = word_list;
void pattern_from_pattern_index(int (&pattern)[5], int pattern_index) {
  int k = 4;
  while (pattern_index > 0) {
    pattern_index = pattern_index / 3;
    pattern[k] = pattern_index % 3;
    k--;
  }
}
bool check_word(string &word, int (&pattern)[5], string &input_word) {
  for (int i = 0; i < 5; i++) {
    if (pattern[i] == 0) {
      if (word.find(input_word[i]) != string::npos) {
        return false;
      }
    } else if (pattern[i] == 1) {
      if (word.find(input_word[i]) == string::npos) {
        return false;
      }
    } else {
      if (word[i] != input_word[i])
        return false;
    }
  }
  return true;
}
void update_word_list(int (&pattern)[5], string &input_word) {
  vector<string> local_list;
  for (auto word : word_list) {
    if (check_word(word, pattern, input_word)) {
      local_list.push_back(word);
    }
  }
  updated_word_list = local_list;
}
void game_loop() {
  string input_word;
  std::cin >> input_word;
  Word iw;
  iw.word = input_word;
  int pattern_index = pattern_matcher(iw, hidden_word);
  printf("\n %d", pattern_index);
  int pattern[5] = {0};
  pattern_from_pattern_index(pattern, pattern_index);
  update_word_list(pattern, input_word);
}

int main() {
  int limit = 0;
  for (auto it : ranking_list) {
    std::cout << it.word << " : " << it.entropy << std::endl;
    if (limit == 20) {
      break;
    }
    limit++;
  }
  for (int i = 0; i < 5; i++) {
    game_loop();
    float max_entropy = -1.0f;
    string max_entropy_word = "";
    float entropy = 0.0f;
    priority_queue<Word, vector<Word>, CompareEntropy> ranking_list;
    int index = 1;
    for (auto guess_word : updated_word_list) {
      Word gw;
      gw.word = guess_word;
      entropy = entropy_for_word(gw);
      ranking_list.push({guess_word, entropy});
    }
    while (!ranking_list.empty()) {
      std::cout << ranking_list.top().word << " : "
                << ranking_list.top().entropy << std::endl;
      ranking_list.pop();
    }
  }
  // string input_word;
  // what pattern will to show?

  /* Word gw;
   gw.word = "adobe";
   std::cout << entropy_for_word(gw);*/
  return 0;
}
//         ---->ranking_list.hh
// main.cpp|--->engine.hh->word_list.hh
// engine.cc----^
