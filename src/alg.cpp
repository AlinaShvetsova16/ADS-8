// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    // Обрабатываем последнее слово, если файл не заканчивается небуквенным символом
    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies;
    tree.getFrequencies(frequencies);

    // Сортируем по убыванию частоты
    std::sort(frequencies.begin(), frequencies.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    // Выводим на экран
    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Сохраняем в файл
    std::ofstream outFile("result/freq.txt");
    if (outFile) {
        for (const auto& pair : frequencies) {
            outFile << pair.first << ": " << pair.second << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
    }
}
