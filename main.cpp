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
    pattern[k] = pattern_index % 3;
    pattern_index = pattern_index / 3;
    k--;
  }
  printf("\n");
  for (auto p : pattern) {
    printf("%d ", p);
  }
}
// adore
// lares
//_YYY_
// tarre

bool check_word(string &word, int (&pattern)[5], string &input_word) {
  int input_word_freq_count[26] = {0};
  for (auto w : input_word) {
    input_word_freq_count[w - 'a'] += 1;
  }
  for (int i = 0; i < 5; i++) {
    bool is_iw_freq_count_zero = input_word_freq_count[word[i] - 'a'] == 0;
    bool is_char_present_in_word = word.find(input_word[i]) != string::npos;
    if (pattern[i] == 2) {
      if (is_iw_freq_count_zero || word[i] != input_word[i]) {
        return false;
      } else {
        input_word_freq_count[word[i] - 'a']--;
      }
    } else if (pattern[i] == 1) {
      if (is_iw_freq_count_zero || !is_char_present_in_word) {
        return false;
      } else {
        input_word_freq_count[word[i] - 'a']--;
      }
    } else {
      if (is_char_present_in_word)
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
  printf("\nNew size : %d", local_list.size());
  updated_word_list = local_list;
}
void game_loop() {
  printf("\n_ _ _ _ _\n");
  string input_word;
  /*for (int i = 0; i < 5; i++) {
    char c;
    std::cin >> c;
    input_word[i] = c;
  }*/
  std::cin >> input_word;
  printf("\n_ _ _ _ _\n");
  Word iw;
  iw.word = input_word;
  int pattern_index = pattern_matcher(iw, hidden_word);
  printf("%d", pattern_index);
  int pattern[5] = {0};
  pattern_from_pattern_index(pattern, pattern_index);
  for (auto p : pattern) {
    if (p == 1)
      std::cout << "\033[1;43m _ \033[0m";
    else if (p == 2)
      std::cout << "\033[1;42m _ \033[0m";
    else
      std::cout << "\033[1;40m _ \033[0m";
  }
  update_word_list(pattern, input_word);
}

int main() {
  int limit = 0;
  for (auto it : ranking_list) {
    std::cout << "\t\t\t\t" << it.word << " : " << it.entropy << std::endl;
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
      entropy = entropy_for_word(gw, updated_word_list);
      ranking_list.push({guess_word, entropy});
    }
    limit = 0;
    while (!ranking_list.empty() && limit < 20) {
      std::cout << "\t\t\t\t" << ranking_list.top().word << " : "
                << ranking_list.top().entropy << std::endl;
      ranking_list.pop();
      limit++;
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
