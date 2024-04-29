#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


void addFileToVector(vector<string>& words, string fileName, int position) {
  ifstream inFS;
  string currWord;
  int count = -1; //used to add to position if another file needs to be opened
  int pos = position; //used to insert words into right vector position
  bool nextFile = false;

  inFS.open(fileName);
  if (!inFS.is_open()) {return;} // stop execution if needed
  //loop file words
  while (!inFS.eof()) {
    if (inFS >> currWord) {
      count++;
      //inFS >> currWord;
      //cout << ":" << currWord;
      if (count == 0) {
        words.at(pos) = currWord;
        pos++;
      }
      else {
        words.insert(words.begin() + pos, currWord);
        pos++;
      }
      
      if (currWord[0] == '@') {
        position += count; //get index of next file
        nextFile = true;
      } 
    }
  }
  inFS.close();

  if (nextFile) {
    currWord = words.at(position).substr(1);
    //cout << currWord << endl;
    addFileToVector(words, currWord, position);
  }
}


int main(int argc, char* argv[]) {
  string currWord;
  vector<string> words;
  
  if (argc < 2) 
  {
    cout << "Need a file to read" << endl;
    return 1;
  }

  for (int i = 1; i < argc; i++) //i = 1 because that's our file to run
  {
    currWord = argv[i];
    if (currWord[0] == '@') {
      words.push_back(currWord);
      currWord = currWord.substr(1); //get rid of @
      addFileToVector(words, currWord, i - 1); //i - 1 because it is one ahead of position
    }
    else {words.push_back(currWord);}
  }

  cout << words.size() << " items:" << endl << endl;
  for (string word : words) {
    cout << word << endl;
  }
  
  return 0;
}