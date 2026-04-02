#include "answer_list.hh"
#include "word_list.hh"

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using std::map;
using std::string;
using std::unordered_map;
using std::vector;
enum COLOR_SET { GREEN = 1, YELLOW = 1 << 2, GREY = 1 << 3 };

unordered_map<string, unordered_map<int, int>> word_color_map;

int colour_code_of_word(const string &guess_word, const string &target_word) {
  enum COLOR_SET color;
  int COLOR_CODE[5] = {0};
  int target_word_freq_count[26] = {0};
  for (auto t_w : target_word) {
    target_word_freq_count[t_w - 'a'] += 1;
  }
  // Mapping to counter repititve characters in guess word.
  for (int i = 0; i < 5; i++) {
    color = GREY;
    bool is_tw_freq_count_not_zero =
        target_word_freq_count[guess_word[i] - 'a'] > 0;
    if (is_tw_freq_count_not_zero && guess_word[i] == target_word[i]) {
      color = GREEN;
      target_word_freq_count[guess_word[i] - 'a']--;
    }
    COLOR_CODE[i] = color;
  }
  for (int i = 0; i < 5; i++) {
    bool is_tw_freq_count_not_zero =
        target_word_freq_count[guess_word[i] - 'a'] > 0;
    if (is_tw_freq_count_not_zero &&
        target_word.find(guess_word[i]) != std::string::npos) {
      color = YELLOW;
      target_word_freq_count[guess_word[i] - 'a']--;
    } else {
      color = GREY;
    }
    if (COLOR_CODE[i] != 1) {
      COLOR_CODE[i] = color;
    }
  }
  int COLOR_CODE_NUM = 0;
  for (auto c : COLOR_CODE) {
    COLOR_CODE_NUM = (COLOR_CODE_NUM * 10) + c;
  }
  return COLOR_CODE_NUM;
}

// Entropy calculation
float entropy_for_word(const string guess_word) {
  float entropy = 0.0f;
  float total_words = (float)answer_list.size();
  for (auto pattern : word_color_map[guess_word]) {
    float prob = pattern.second / total_words;
    entropy += (-prob * log2(prob));
  }
  return entropy;
}
int main() {
  float max_entropy = -1.0f;
  string max_entropy_word = "";
  float entropy = 0.0f;
  for (auto word : word_list) {
    for (auto target_word : answer_list) {
      int color_code = colour_code_of_word(word, target_word);
      // Map to keep track of color patterns for a particular word.
      word_color_map[word][color_code] += 1;
    }
  }
  for (auto word : word_list) {
    entropy = entropy_for_word(word);
    if (entropy > max_entropy) {
      max_entropy = entropy;
      max_entropy_word = word;
    }
    std::cout << "entropy of " << word << " : " << entropy << std::endl;
  }

  std::cout << "Max entropy : " << max_entropy;
  std::cout << "\nMax Entropy word : " << max_entropy_word;
  return 0;
}
