#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

#include "trie.h"


int main() {
  Trie trie;
  std::ifstream file("words.txt");
  if (!file) {
    std::cerr << "Failed to open file" << std::endl;
    return 1;
  }
  std::string word;
  int count = 0;
  while (std::getline(file, word)) {
    trie.insert(word.c_str());
    count++;
  }
  file.close();
  std::cout << "Inserted " << count << " words" << std::endl;

  std::string searchWord;
  while (true) {
    std::cout << "Enter a word to search (or 'exit' to quit): ";
    std::cin >> searchWord;
    if (searchWord == "exit") {
      break;
    }
    auto start = std::chrono::high_resolution_clock::now();
    bool found = trie.search(searchWord.c_str());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Search took " << duration.count() << " microseconds" << std::endl;
    if (found) {
      std::cout << "Found " << searchWord << std::endl;
    } else {
      std::cout << "Not found " << searchWord << std::endl;
    }
  }

  return 0;
}