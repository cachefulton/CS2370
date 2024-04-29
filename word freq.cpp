#include <iostream>
#include <vector> 
#include <string>
#include <cctype>
using namespace std;

/* Define your function here */
int GetWordFrequency(const vector<string>& wordsList, string currWord) 
{
  
   int counter = 0;
   bool match = true;
   for (char& ch : currWord) {ch = tolower(ch);}
   //cout << currWord;
   for (string word : wordsList) {
      //cout << word;
      if (word.size() == currWord.size()) {
         for(char& c : word) {
            //cout << c << endl;
            c = tolower(c);
         }
         if (word == currWord)
         counter++;
      }
      
   }
   return counter;
}

int main() {
   /* Type your code here */
   int numOfWords;
   cin >> numOfWords;
   
   string word;
   vector<string> wordList(numOfWords);
   for (int i = 0; i < numOfWords; i++) 
   {
      cin >> word;
      wordList.at(i) = word;
   }
   for (string word : wordList) 
   {
      
      int freq = GetWordFrequency(wordList, word);
      cout << word << " " << freq << endl;
   }
   
   return 0;
}
