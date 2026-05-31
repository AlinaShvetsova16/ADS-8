// Copyright 2021 NNTU-CS
#include "include/alg.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  int ch;

  while ((ch = file.get()) != EOF) {
    if (std::isalpha(ch)) {
      currentWord += std::tolower(ch);
    } else {
      if (!currentWord.empty()) {
        tree.insert(currentWord);
        currentWord.clear();
      }
    }
  }

  // Обрабатываем последнее слово, если файл не заканчивается не-буквой
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getWords();

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::cout << "Words frequency analysis (top 50):" << std::endl;
  for (size_t i = 0; i < std::min(words.size(), size_t(50)); ++i) {
    std::cout << words[i].first << ": " << words[i].second << std::endl;
  }

  std::ofstream outFile("result/freq.txt");
  if (outFile) {
    for (const auto& word : words) {
      outFile << word.first << ": " << word.second << std::endl;
    }
    outFile.close();
    std::cout << "Results saved to result/freq.txt" << std::endl;
  } else {
    std::cout << "Error saving to file!" << std::endl;
  }
}
