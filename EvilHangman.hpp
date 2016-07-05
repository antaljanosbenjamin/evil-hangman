#ifndef EVILHANGMAN_HPP
#define EVILHANGMAN_HPP

class EvilHangman;


#include "EvilWord.hpp"
#include <string>
#include <set>

class EvilHangman {
public:
    std::set<std::string> dictionary_;
    std::set<int> wordLengths_;

public:
    EvilHangman(std::string inputDict);

    static bool IsRightLength(size_t length, std::string str);

    EvilWord getNewWord(size_t length);
};

#endif
