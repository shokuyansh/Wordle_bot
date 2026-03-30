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

map<string, unordered_map<int, int>> word_color_map;

vector<string> word_list = {"adore", "tiger", "model", "munch", "pound",
                            "stare", "brand", "light", "alone", "snore"};

int colour_code_of_word(const string guess_word, const string target_word) {
  enum COLOR_SET color;
  int COLOR_CODE = 0;
  // Mapping to counter repititve characters in guess word.
  unordered_map<char, bool> target_word_map;
  for (int i = 0; i < 5; i++) {
    if (guess_word[i] == target_word[i]) {
      color = GREEN;
    } else if (guess_word[i] != target_word[i]) {
      if (target_word.find(guess_word[i]) != std::string::npos) {
        color = YELLOW;
      } else {
        color = GREY;
      }
    }
    COLOR_CODE = COLOR_CODE * 10 + color;
  }
  return COLOR_CODE;
}

// Entropy calculation
float entropy_for_word(const string guess_word) {
  float entropy = 0.0f;
  for (auto pattern : word_color_map[guess_word]) {
    float prob = pattern.second / (float)10;
    entropy += (-prob * log2(prob));
  }
  return entropy;
}
int main() {
  float max_entropy = -1.0f;
  float entropy = 0.0f;
  for (auto word : word_list) {
    for (auto target_word : word_list) {
      int color_code = colour_code_of_word(word, target_word);
      // Map to keep track of color patterns for a particular word.
      word_color_map[word][color_code] += 1;
    }
  }
  for (auto word : word_list) {
    entropy = entropy_for_word(word);
    if (entropy > max_entropy) {
      max_entropy = entropy;
    }
    std::cout << "entropy of " << word << " : " << entropy << std::endl;
  }

  std::cout << "Max entropy : " << max_entropy;
  return 0;
}
