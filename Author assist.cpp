#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/* Define your functions here. */
int GetNumOfNonWSCharacters(const string& userText) {
   int count = 0;
   for (char c : userText) {
      if (!isspace(c)){
         count++;
      }
   }
   return count;
}

int GetNumOfWords(const string& userText) {
   int count = 0;
   size_t ind = -1;
   char follow = '0';
   char c;
   do {
      ind++;
      //cout << ind;
      c = userText[ind];
      if ((isspace(c) && isalnum(follow)) || (ispunct(c) && c != '\'' && isalnum(follow))) {
         //if (!isspace(follow) || !ispunct(follow)) {
         //cout << follow << c << endl;
         count++;
         //}
      }
      follow = c;
      
   }
   while (ind < userText.size() - 1);
   return count;
}

int FindText(const string& wp, const string& userText) {
   int count = 0;
   size_t ind = -1;
   size_t ind2;
   do {
      ind2 = 0;
      ind++;
      if (userText[ind] == wp[ind2]) {
         while (userText[ind] == wp[ind2]) {
            ind++;
            ind2++;
            if (ind2 == wp.size()) {
               count++;
               ind--; //makes it so individual letters put next to each other work
            }
         }
      }
   }
   while (ind < userText.size() - 1);
   
   return count;
}

void ReplaceExclamation(string& userText) {
   size_t ind = -1;
   do {
      ind++;
      if (userText[ind] == '!') {
         userText[ind] = '.';
      }
   }
   while (ind < userText.size() - 1);
}

void ShortenSpace(string& userText) {
   int count = 0;
   size_t ind = -1;
   char follow = '0';
   char c;
   do {
      ind++;
      c = userText[ind];
      if (isspace(c) && isspace(follow)) {
         //ind++
         //c = userText[ind + 1];
         //userText[ind] = c;
         size_t tempInd = ind;
         while (isspace(userText[tempInd])) {
            tempInd++;
         }
         size_t exTempInd = ind;
         int delSpace = tempInd - ind;
         while (tempInd < userText.size()) {
            userText[exTempInd] = userText[tempInd];
            exTempInd++;
            tempInd++;
         }
         userText.erase(exTempInd, delSpace);
         
      }
   follow = c;
   }
   while (ind < userText.size() - 1);
}

void PrintMenu() {
   cout << "MENU" << endl;
   cout << "c - Number of non-whitespace characters" << endl;
   cout << "w - Number of words" << endl;
   cout << "f - Find text" << endl;
   cout << "r - Replace all !'s" << endl;
   cout << "s - Shorten spaces" << endl;
   cout << "q - Quit" << endl << endl;
}

void ExecuteMenu(char userOpt, string userText) {
   string wp;
   int tempNum;
   switch (userOpt) {
      case 'c':
         tempNum = GetNumOfNonWSCharacters(userText);
         cout << "Number of non-whitespace characters: " << tempNum << endl << endl;
         break;
      case 'w':
         tempNum = GetNumOfWords(userText);
         cout << "Number of words: " << tempNum << endl << endl;
         break;
      case 'f':
         cout << "Enter a word or phrase to be found:" << endl;
         cin.ignore();
         getline(cin, wp);
         tempNum = FindText(wp, userText);
         cout << '"' << wp << '"' << " instances: " << tempNum << endl << endl;
         break;
      case 'r':
         ReplaceExclamation(userText);
         cout << "Edited text: " << userText << endl << endl;
         break;
      case 's':
         ShortenSpace(userText);
         cout << "Edited text: " << userText << endl << endl;
         break;
      default:
         break;
   }
}

int main() {

   /* Type your code here. */
   string text;
   string line;
   //bool checker = true;
   cout << "Enter a sample text:" << endl << endl;
   getline(cin, text);
   
   /*while(checker == true)
   {
      getline(cin, line);
      //cout << line;
      checker = (text == "");
      text += line;
   }*/
   
   cout << "You entered: " << text << endl << endl;
   
   char opt;
   do {
      PrintMenu();
      cout << "Choose an option:" << endl;
      cin >> opt;
      ExecuteMenu(opt, text);
   }
   while (opt != 'q');

   return 0;
}