#include "EvilWord.hpp"
#include <iostream>
#include <functional>

EvilWord::EvilWord(unsigned int health, size_t length, std::vector<std::string> defaultDict)
        : health_{health},
          length_{length},
          letters_{},
          fittingWords_{defaultDict},
          tippedLetters_{} {
    letters_.resize(length_);
    for (char &c : letters_)
        c = '.';
}

std::string EvilWord::getWordState() {
    std::string wordState;
    std::copy(letters_.begin(), letters_.end(), std::back_inserter(wordState));
    return wordState;
}

void EvilWord::removeNotFitting(std::regex reg) {
    std::function<bool(std::string &)> match = [&](std::string &str) { return !std::regex_match(str, reg); };
    fittingWords_.erase(std::remove_if(fittingWords_.begin(), fittingWords_.end(), match), fittingWords_.end());
}

void EvilWord::removeFitting(std::regex reg) {
    std::function<bool(std::string &)> match = [&](std::string &str) { return std::regex_match(str, reg); };
    fittingWords_.erase(std::remove_if(fittingWords_.begin(), fittingWords_.end(), match), fittingWords_.end());
}

bool EvilWord::guessLetter(char letter) {
    letter = ::toupper(letter);
    if (std::find(tippedLetters_.begin(), tippedLetters_.end(), letter) != tippedLetters_.end()) {
        std::string exceptionMessage = "You have already guessed the letter ";
        exceptionMessage += letter;
        exceptionMessage += "!";
        throw std::invalid_argument{exceptionMessage};
    }
    tippedLetters_.push_front(letter);
    tippedLetters_.sort();
    bool wordWithoutLetter = false;
    for (std::string str : fittingWords_) {
        if (str.find(letter) == std::string::npos) {
            wordWithoutLetter = true;
            break;
        }
    }
    if (wordWithoutLetter) {
        // there are at least one word, without the letter
        std::string regExp = "(.*)";
        regExp = regExp + letter + regExp;
        removeFitting(std::regex{regExp});
        health_--;
        return false;
    } else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> wordPicker(0, fittingWords_.size() - 1);
        int choosenIndex = wordPicker(mt);
        std::string &choosenWord = fittingWords_.at(choosenIndex);
        size_t index = 0;
        std::for_each(choosenWord.begin(), choosenWord.end(), [&](const char c) {
            if (c == letter)
                letters_[index] = c;
            index++;
        });
        std::string regExp(letters_);
        std::string negateLetter = "[^";
        negateLetter = negateLetter + letter;
        negateLetter = negateLetter + "]";

        while (std::find(regExp.begin(), regExp.end(), '.') != regExp.end()) {
            int pointPos = std::find(regExp.begin(), regExp.end(), '.') - regExp.begin();
            regExp.erase(regExp.begin() + pointPos);
            regExp.insert(pointPos, negateLetter);
        }
        removeNotFitting(std::regex{regExp, std::regex_constants::basic});
        return true;
    }
}

void EvilWord::letsPlay() {
    while (std::find(letters_.begin(), letters_.end(), '.') != letters_.end() && health_ > 0) {
        std::cout << "Current word: " << getWordState() << std::endl;
        std::cout << "Lives: " << health_ << std::endl;
        char c;
        std::cout << "Guessed letters: ";
        for (char c : tippedLetters_)
            std::cout << c << " ";
        std::cout << std::endl;
        std::cout << "Guess a letter!" << std::endl;
        std::cin >> c;
        try {
            if (guessLetter(c))
                std::cout << "Correct!" << std::endl;
            else
                std::cout << "Missed :(" << std::endl;
            // Uncomment this line to show the filtered words in each cycle
            printWords();
        } catch (std::invalid_argument exception) {
            std::cout << exception.what() << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    if (health_ > 0)
        std::cout << "Congratulation, you won! The word to guess was " << fittingWords_[0] << "." << std::endl;
    else
        std::cout << "You lose :(. The word to guess was " << fittingWords_[0] << "." << std::endl;
}

void EvilWord::printWords() {
    std::cout << "Current pattern: " << getWordState() << std::endl << "Words:" << std::endl;
    for (std::string word : fittingWords_) {
        std::cout << word << std::endl;
    }
}