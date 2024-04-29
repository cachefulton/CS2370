#include <iostream>
using namespace std;

int main() {
   int highwayNumber;
   
   cin >> highwayNumber;

   /* Type your code here. */
   int modNum = highwayNumber % 2; // 1 or 2
   if (highwayNumber >= 1 && highwayNumber <= 99) {
      if (modNum == 1) {
         cout << "I-" << highwayNumber << " is primary, going north/south." << endl;
      }
      else {
         cout << "I-" << highwayNumber << " is primary, going east/west." << endl;
      }
   }
   else if (highwayNumber >= 101 && highwayNumber <= 999) {
      int lastTwo = highwayNumber % 100;
      if (lastTwo == 0) {
         cout << highwayNumber << " is not a valid interstate highway number." << endl;
      }
      else if (lastTwo % 2 == 1) {
         cout << "I-" << highwayNumber << " is auxiliary, serving I-" << lastTwo << ", going north/south." << endl;
      }
      else if (lastTwo % 2 == 0) {
         cout << "I-" << highwayNumber << " is auxiliary, serving I-" << lastTwo << ", going east/west." << endl;
      }
   }
   else {
      cout << highwayNumber << " is not a valid interstate highway number." << endl;
   }

   return 0;
}
