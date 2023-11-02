#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// NET ID : AXE210038
// NAME: AHMED ELGHAZI

void outputA(string roman, long unsigned int pointer, fstream &file){ // output roman string
    file.seekp(pointer - 22); // the beginning of the line is 22 from the end
    file << roman; // output statement
    file.seekg(pointer);
}

void outputB(int totalNum, long unsigned int pointer, fstream &file){ // output arabic digits
    string totalNu = to_string(totalNum); // convert the integer to a string
    file.seekp(pointer-5); //
    file << totalNu;
    file.seekg(pointer);
}

void outputC(long unsigned int pointer, fstream &file) // output white space
{
    string empty = "                     ";
    file.seekp(pointer-22);
    file << empty << endl;
}


int dictionary(char c){ // this holds the values of roman numerals and returns the arabic digit value
    if (c == 'M'){return 1000;}
    else if (c == 'D'){return 500;}
    else if (c == 'C'){return 100;}
    else if (c == 'L'){return 50;}
    else if (c == 'X'){return 10;}
    else if (c == 'V'){return 5;}
    else if (c == 'I'){return 1;}
    else {return 0;}
}

void conRoman(string const arabic, string &total){ // if the value is divisible by that number, add it to the string
    // then subtract it from the arabic digit itself
    total.clear(); // resetting the value;
    int arabicM = stoi(arabic);
    while (arabicM >= 1){
        if (arabicM / 1000 >= 1){total += 'M'; arabicM = arabicM - 1000; continue;}
        if (arabicM / 900 >= 1){total += 'C'; total +='M'; arabicM = arabicM - 900; continue;}
        if(arabicM / 500 >= 1){total += 'D';arabicM = arabicM - 500;continue;}
        if (arabicM / 400 >= 1){total += 'C';total += 'D'; arabicM = arabicM - 400; continue;}
        if (arabicM / 100 >= 1){total += 'C';arabicM = arabicM - 100;continue;}
        if (arabicM / 90 >= 1){total += 'X';total += 'C'; arabicM = arabicM - 90; continue;}
        if (arabicM / 50 >= 1) {total += 'L';arabicM = arabicM - 50;continue;}
        if (arabicM / 40 >= 1){total += 'X';total += 'L'; arabicM = arabicM - 40; continue;}
        if (arabicM / 10 >= 1){total += 'X';arabicM = arabicM - 10;continue;}
        if (arabicM / 9 >= 1){total += 'I';total += 'X'; arabicM = arabicM - 9;continue;}
        if (arabicM / 5 >= 1){total += 'V';arabicM = arabicM - 5;continue;}
        if (arabicM / 4 >= 1){total += 'I';total += 'V'; arabicM = arabicM - 4; continue;}
        if(arabicM < 5){int x = arabicM/1; for (int i = 0; i < x; i++){total += 'I';} arabicM -= x;} // add multiple 1's
    }
}

void conArabic(string roman, int &totalNum){ //
    totalNum = 0; // clear the value since it is a reference
    int val1 = 0; // initialize variables
    int val2 = 0; // ^^
    for(long unsigned int i = 0; i < roman.length(); i++){
        char a  = roman.at(i); // iterate through roman
        if(i+1 < roman.length()){char b = roman.at(i+1);val2 = dictionary(b);}
        else {val2 = 0;}
        val1 = dictionary(a);
        if (val1 > val2){ totalNum += val1;} // XI equals 11 because the greater value comes first
        if (val2 > val1){totalNum += val2;totalNum -= val1;i++;} // IX equals 9 because the lower value came first
        if(val2 == val1){totalNum += val1; totalNum += val2; i++;} // If they are equal, just add two of them

    }
}

void validity(string full,bool &romanValid, bool &arabicValid,string &arabic, string &roman) {
    //checks if the strings are composed of valid characters, adjusting the boolean value accordingly
    roman.clear(); // First
    arabic.clear(); // These three lines reset the values of these variables for the next iteration
    int tot = 0; // Second

    roman = full.substr(0, 17); // Roman numerals can occupy spaces 0 to 17 on a given line
    arabic = full.substr(17,4); // Arabic digits will occupy 18 to 21 meaning count from posiiton 17

    char a = arabic.at(0);
    if (isspace(a)) {arabicValid = false; // if this char is a space, there are no arabic digits
        for (long unsigned int i = 0; i < roman.length(); i++) {
            if (roman.at(i) == 'I' || roman.at(i) == 'V' || roman.at(i) == 'X'
                || roman.at(i) == 'L' || roman.at(i) == 'C' || roman.at(i) == 'D'
                || roman.at(i) == 'M' || roman.at(i) == ' ') {}
            else {
                romanValid = false; // if the character at I is not one of these values, it is invalid
                break;
            }
        }
    }
    else {romanValid = false;
        for (long unsigned int i = 0; i < arabic.length(); i++) { // Arabic can only be digits, not punctution or alphabet
            if (isdigit(arabic[i]) || arabic[i] == ' ') {} // Check if it is a space because stirng could be "14  "
            else {arabicValid = false;} // invalid values set this to false invalidating the bool
        }

    }
    if(arabicValid){ // if arabic digits are still valid
        tot = stoi(arabic); // convert the string to an integer
        if(tot >= 5000 || tot < 1){arabicValid = false;} // Value has to be wihtin range given from instructions
        if(tot%1 != 0){arabicValid = false;} // A decimal would yield a non-zero value
    }
}

const string database = "numbers.txt";
//your filestream for the database will connect to this variable

int main(){
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    string temp;  //variable for database filename
    string batch; //variable for batch filename

    cout<<"Enter File Name: ";
    cin>>temp;

    ifstream infile(temp, ios::binary);
    ofstream outfile(database, ios::binary);
    string line;
    if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

    infile.close();
    outfile.close();
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */

    //add your code for main here
    fstream file (database, ios::binary | ios::in | ios::out);
    if(file.good()) { // Does not work if the file stream is bad
        string full, roman, arabic, total; // the strings that will be used within this code
        int totalNum = 0; //
        while (getline(file, full)) { // read line from filestream into string
            bool romanValid = true; // reset both booleans to true
            bool arabicValid = true; // ^^
            validity(full, romanValid, arabicValid, arabic, roman);
            long unsigned int pointer = file.tellg(); // can never be negative, tells where reading cursor is
            if(!arabicValid && !romanValid){outputC(pointer, file);} // print white space if both are false
            else if (arabicValid) {
                conRoman(arabic, roman);
                outputA(roman, pointer, file);
            }
            else if (romanValid) {
                conArabic(roman, totalNum);
                outputB(totalNum, pointer, file);
            }
        }
        file.close();
    }
}
