#include "EvilHangman.hpp" 

#include <iostream>
#include <fstream>

using namespace std;

EvilHangman::EvilHangman(std::string inputDict)
        : dictionary_{}, wordLengths_{} {
    std::ifstream ifs(inputDict, std::ifstream::in);
    std::string inputWord;
    if (!ifs.good())
        std::cout << "Bad input file!" << std::endl;
    while (ifs.good()) {
        ifs >> inputWord;
        if (inputWord.find(".") == std::string::npos) {
            std::transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::toupper);
            wordLengths_.insert(inputWord.length());
            dictionary_.insert(inputWord);
        }
    }
}

bool EvilHangman::IsRightLength(size_t length, std::string str) {
    size_t actLength = 0;
    auto s = str.begin();
    while (s != str.end())
        actLength += (*s++ & 0xc0) != 0x80;
    return actLength == length;
}

EvilWord EvilHangman::getNewWord(size_t length) {

    std::srand(std::time(0));
    std::function<bool(std::string)> pred = std::bind(IsRightLength, length, std::placeholders::_1);
    std::vector<std::string> defaultDict;
    std::copy_if(dictionary_.begin(), dictionary_.end(),
                 std::insert_iterator<std::vector<std::string>>(defaultDict, defaultDict.end()), pred);
    unsigned int health = 10;
    return EvilWord{health, length, defaultDict};
};