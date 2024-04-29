#include <iostream>
// FIXME include vector library
#include <vector>
#include <string>
using namespace std;

int main() {

   /* Type your code here. */
   // jersey vector and rating vector with the info of each player at corresponding indeces
   //initialize vectors and const vecor size
   const int vsize= 5;
   vector<int> jersies(vsize);
   vector<int> ratings(vsize);
   
   //output prompts jersey, then rating for 5 players
   for (int i = 0; i < vsize; i++)
   {
      cout << "Enter player " << i + 1 << "'s jersey number:" << endl;
      cin >> jersies.at(i);
      cout << "Enter player " << i + 1 << "'s rating:" << endl;
      cin >> ratings.at(i);
      cout << endl;
   }
   //output roster

   cout << "ROSTER" << endl;
   
   for (unsigned int i = 0; i < jersies.size(); i++) {
      cout << "Player " << i + 1 << " -- Jersey number: " << jersies.at(i) << ", Rating: " << ratings.at(i) << endl;
   }

   //output menu
   char in;
   while (in != 'q') {
      cout << endl << "MENU" << endl;
      cout << "a - Add player" << endl;
      cout << "d - Remove player" << endl;
      cout << "u - Update player rating" << endl;
      cout << "r - Output players above a rating" << endl;
      cout << "o - Output roster" << endl;
      cout << "q - Quit" << endl << endl;
      
      //run available options
      
      cout << "Choose an option:";
      cin >> in;
      //cout << endl;
      
      if (in == 'a') {
         int newJ;
         int newR;
         cout << "Enter a new player's jersey number:" << endl;
         cin >> newJ;
         cout << "Enter the player's rating:";
         cin >> newR;
         jersies.push_back(newJ);
         ratings.push_back(newR);
      }
      else if (in == 'd') {
         int jnum;
         //int ind;
         cout << "Enter a jersey number:" << endl;
         cin >> jnum;
         //ind = find(jersies.begin(), jersies.end(), jnum)
         //remove(jersies.begin(), jersies.end(), jersies.at(ind));
         //remove(ratings.begin(), ratings.end(), ratings.at(ind));
         for (size_t i = 0; i < jersies.size(); i++) {
            if (jersies.at(i) == jnum) {
               jersies.erase(jersies.begin() + i);
               ratings.erase(ratings.begin() + i);
            }
         }
      }
            
      else if (in == 'u') {
         int jnum;
         int newR;
         cout << "Enter a jersey number:" << endl;
         cin >> jnum;
         cout << "Enter a new rating for player:" << endl;
         cin >> newR;
         for (size_t i = 0; i < jersies.size(); i++) {
            if (jersies.at(i) == jnum) {
               ratings.at(i) = newR;
            }
         }
      }
      else if (in == 'r') {
         int rnum;
         //int count = 1;
         cout << endl << "Enter a rating:" << endl;
         cin >> rnum;
         cout << endl << "ABOVE " << rnum << endl;
         
         for (size_t i = 0; i < ratings.size(); i++) {
            if (ratings.at(i) > rnum) {
               cout << "Player " << i + 1 << " -- Jersey number: " << jersies.at(i) << ", Rating: " << ratings.at(i);
            }
         }
      }
            
      else if (in == 'o'){
         cout << endl << "ROSTER";
         for (unsigned int i = 0; i < jersies.size(); i++) {
            cout << endl;
            cout << "Player " << i + 1 << " -- Jersey number: " << jersies.at(i) << ", Rating: " << ratings.at(i);
         }
         

      }
      
      cout << endl;
   }
   

   return 0;
}