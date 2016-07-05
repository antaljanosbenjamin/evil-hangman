//
// Created by János Benjamin Antal on 7/4/16.
//
#include "EvilHangman.hpp"
#

int main(){
    EvilHangman evilHangman("/home/kovi/git/evil-hangman/english_dictionary.txt");
    EvilWord ew = evilHangman.getNewWord(6);
    ew.letsPlay();
}