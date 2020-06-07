//
//  main.cpp
//  FinalProject
//
//  Created by Kevin Jin on 6/6/20.
//  Copyright © 2020 Kevin Jin. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// main and menu function with input checking
int main() {
    cout << "San Jose Housing Listing Service" << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Add new data" << endl;
    cout << "2. Delete data" << endl;
    cout << "3. Search and display data using the primary key" << endl;
    cout << "4. List data in hash table sequence" << endl;
    cout << "5. List data in sorted key sequence" << endl;
    cout << "6. Print indented tree" << endl;
    cout << "7. Efficiency" << endl;
    // TODO: team choice menu option
    cout << "8. Team choice menu option" << endl;
    cout << "9. Quit" << endl << endl;
    
    string input = "";
    int num = 0;
    bool isNum = true;
    do {
        cout << "Enter a number to perform the corresponding function: ";
        cin >> input;
        for (int i = 0; i < input.length(); ++i)
            if (input[i] < '0' || input[i] > '9')
                isNum = false;
        
        // integer == input[i] - '0'
        // when subtracting '0' from input[i], subtracting the ascii codes
        // the ascii code for 0 is 48, so when '0' - 48, returns integer value 0
        if (isNum == true) {
            for (int i = 0; i < input.size(); ++i) {
                int numZeros = pow(10, input.size() - i - 1);
                num = (input[i] - '0') * numZeros;
            }
            
            if (!(num > 0 && num < 10))
                cout << "The array size is not in the bounds. Try again." << endl;
        }
    } while (!(num > 0 && num < 10));

    do {
        switch (num) {
            case 1: {
                break;
            } case 2: {
                break;
            } case 3: {
                break;
            } case 4: {
                break;
            } case 5: {
                break;
            } case 6: {
                break;
            } case 7: {
                break;
            } case 8: {
                break;
            } case 9: {
                break;
            } default: {
                cout << "Please enter an integer between 1 and 9 inclusive: ";
                cin >> num;
                break;
            }
        }
    } while (num != 9);
    
    return 0;
}
