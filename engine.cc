#include "engine.hh"
#include "word_list.hh"
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

// Each Word -> Prob for all possible patterns -> cal. entropy accordingly

int pattern_matcher(const Word &guess_word, const string &word) {
  enum COLOR_SET color;
  int COLOR_CODE[5] = {0};
  int word_freq_count[26] = {0};
  const string gw = guess_word.word;
  for (auto w : word) {
    word_freq_count[w - 'a'] += 1;
  }
  // Mapping to counter repititve characters in guess word.
  for (int i = 0; i < 5; i++) {
    color = GREY;
    bool is_tw_freq_count_not_zero = word_freq_count[gw[i] - 'a'] > 0;
    if (is_tw_freq_count_not_zero && gw[i] == word[i]) {
      color = GREEN;
      word_freq_count[gw[i] - 'a']--;
    }
    COLOR_CODE[i] = color;
  }
  for (int i = 0; i < 5; i++) {
    bool is_tw_freq_count_not_zero = word_freq_count[gw[i] - 'a'] > 0;
    if (is_tw_freq_count_not_zero && word.find(gw[i]) != std::string::npos) {
      color = YELLOW;
      word_freq_count[gw[i] - 'a']--;
    } else {
      color = GREY;
    }
    if (COLOR_CODE[i] != 2) {
      COLOR_CODE[i] = color;
    }
  }
  int pattern_num = 0;
  int k = 1;
  for (int i = 4; i >= 0; i--) {
    pattern_num += (COLOR_CODE[i] * k);
    k = k * 3;
  }
  return pattern_num;
}
// adobe
// abune
// G__YG
// 2*3^4+1*3+2*1
void prob_of_all_patterns_of_a_word(Word &guess_word) {
  for (auto word : word_list) {
    int pattern_index = pattern_matcher(guess_word, word);
    // printf("pattern_index : %d", pattern_index);
    guess_word.prob_distribution[pattern_index]++;
  }
}

// Entropy calculation
float entropy_for_word(Word &guess_word) {
  float entropy = 0.0f;
  const int word_list_size = word_list.size();
  prob_of_all_patterns_of_a_word(guess_word);
  for (auto pattern_freq : guess_word.prob_distribution) {
    // printf("\n prob : %d", pattern_freq);
    float pattern_prob = (float)pattern_freq / (float)word_list_size;
    // printf("\n pattern_prob : %f", pattern_prob);
    if (pattern_prob != 0.0f)
      entropy += (-pattern_prob * log2(pattern_prob));
  }
  return entropy;
}
