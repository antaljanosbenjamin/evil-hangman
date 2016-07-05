#ifndef EVILWORD_HPP
#define EVILWORD_HPP

class EvilWord;

#include "EvilHangman.hpp"
#include <string>
#include <regex>
#include <forward_list>

class EvilWord {
public:

    unsigned int health_;
    size_t length_;
    std::string letters_;
    std::vector<std::string> fittingWords_;
    std::forward_list<char> tippedLetters_;

    EvilWord(unsigned int health_, size_t length, std::vector<std::string> defaultDict);

    void printWords();

    void removeNotFitting(std::regex reg);

    void removeFitting(std::regex reg);

public:
    std::string getWordState();

    bool guessLetter(char letter);

    void letsPlay();

    friend EvilHangman;
};

#endif
