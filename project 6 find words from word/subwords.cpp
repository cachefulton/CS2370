#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  int NWORDS = 81483;
  string theWord;
  
  //put words into vector
  vector<string> words;
  //open file stream
  ifstream infs("words.txt");
  if (!infs.is_open()) {return 1;}
  string tempWord;
  while (infs >> tempWord) {
    words.push_back(tempWord);
  }
  infs.close();

  //get word argument if it's passed
  tempWord = (argc > 1) ? argv[1] : "a"; //I pass "a" if false because any string under length of 3 will work due to next if statement
  if (tempWord.size() < 3) { //word passed as arg is less than 3 chars or no word passed
    //get word at pos n if word is bigger than 2 letters
    int wordLen = 0;
    while (wordLen < 3) {
      //randomly generate an int
      default_random_engine dre(time(nullptr));   // Seed the engine 
      uniform_int_distribution<int> di(0,NWORDS); // Use uniform distribution 
      int n = di(dre);     // Get a random int 
      theWord = words.at(n); //get word at rand int
      wordLen = theWord.size();
    }
  }
  else {
    theWord = argv[1];
  }

  //map letters as keys to count duplicate letters in our word 
  map<char, int> letters;
  for (char letter : theWord) {
    if (letters.count(letter) == 1) { //check if letter is in map
      letters.at(letter)++; //if so increment value, which is the amount of that letter
    }
    else {letters.emplace(letter, 1);}
  }

  //map dictionary words in the same way
  vector<string> subWords;
  for (string word : words) {
    bool fullWord = true; //check if the full word was iterated through
    if (word.size() > theWord.size() || word.size() < 3) {continue;}
    else {
      map<char, int> checkLetters; //temp map for matching map keys
      for (char letter : word) {
        if (letters.count(letter) == 0) {
          fullWord = false; //full word not iterated through
          break;
        }
        else if (checkLetters.count(letter) == 0) {checkLetters.emplace(letter, 1);}
        else {checkLetters.at(letter)++;}
      }
      //for loop to check if amount of each letter matches
      if (fullWord) {
        for (auto const& [key, val] : checkLetters) {
          if (val > letters.at(key)) {fullWord = false;} //letter counts don't match up
        }
        if (fullWord) {subWords.push_back(word);}
      }
    }
  }

  //sort vector
  sort(subWords.begin(), subWords.end(), 
  [](string a, string b) {
    if (a.size() != b.size()) {return a.size() < b.size();} //primarily by length
	  return a < b;  //then alphabetically
  });

  cout << "The word is " << theWord << ":" << endl << endl;
  for (string word : subWords) {
    cout << word << endl;
  }

  return 0;
}