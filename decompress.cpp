//
//  main.cpp
//  FinalProject
//
//  Created by Abram Himmer on 4/9/18.
//  Copyright © 2018 Abram Himmer. All rights reserved.
//

#include <string>
#include <map>
#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Node.hpp"
#include <cstring>

using namespace std;

vector<Node*> huffTree;
map<char, int> charFreq;
map<string, char> huffCodes;



// convert a group of 8 digits to a character
string ascii_to_bin(char c) {
    bitset<8> temp(c);
    return temp.to_string();
}

/* !----------------------------------------------------------------------------------------------------------! */


int main(int argc, const char * argv[]) {
    time_t startTotal;
    time_t endTotal;
    startTotal = clock();

    
    //scan thru file with ifs object
    
    ifstream file; //takes in the file
    
    
    /* !-----------------------------------------------OPEN FILE AND MAKE THE NEW FILE NAME-----------------------------------------------------------! */

    file.open(argv[1], ios::in);
    string inputfile = argv[1];
    string filename = argv[1];
    
    if (!file){
        cout << "File can not be opened. Try again" << endl;
        exit(1);
    }
    
    int n = filename.length();
    string prefix = inputfile.substr(0, n-7); //grab everything but the .txt
    string outfile = prefix + "2.txt";
    
    /* !-----------------------------------------------Save HuffCodes to Hashtable-----------------------------------------------------------! */

    
    string line, code, value;
    char trueValue;
    while (getline(file, line) && line != "*****"){
        stringstream s(line);
        getline(s, code, ' ');
        s >> value;
        if (value == "newline"){
            trueValue = '\n';
            huffCodes[code] = trueValue;
        } else if (value == "tab"){
            trueValue = '\t';
            huffCodes[code] = trueValue;
        } else if (value == "return"){
            trueValue = '\r';
            huffCodes[code] = trueValue;
        } else if (value == "space") {
            trueValue = ' ';
            huffCodes[code] = trueValue;
        } else {
            trueValue = value[0];
            huffCodes[code] = trueValue;
        }
    }
    
    
    //LINE = *****
    /* !-----------------------------------------------Decode ASCII chars to binary-----------------------------------------------------------! */
    string bitNumber;
    getline(file, bitNumber);
    //cout << bitNumber << endl;
    //cout << bitNumber << endl;
    int bitNum = stoi(bitNumber);
    if (bitNum % 8 != 0){
        cout << "need to delete stuff at the end" << endl;
    }
    char c;
    string textOfCodes;
    //ACCOUNT FOR THE 0's AT THE END
    //APPEND THEM BY SUBTRACTING THE DIFF BETWEEN THE ACTUAL LENGTH AND THE GIVEN LENGHT
    while (file.get(c)){
        textOfCodes += ascii_to_bin(c);
    }
    //cout << textOfCodes << endl;
    string tmp;
    string actualText;
    
    for(char c : textOfCodes){
        tmp += c;
        if (//huffCodes.count(tmp) != 0){
            huffCodes.find(tmp) != huffCodes.end()){
            
            actualText += huffCodes[tmp];
            tmp = "";
        }
    }
    //cout << actualText << endl;
    ofstream ofs; //write to file object
    ofs.open(outfile);//open file with file name
    ofs << actualText;
    
    file.close();
    ofs.close();
    
    
    endTotal = clock();
    time_t diff = endTotal - startTotal;
    cout << "Decompression total time: " << (float)diff/CLOCKS_PER_SEC << endl;
        return 0;
}

