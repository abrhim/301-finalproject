//
//  main.cpp
//  FinalProject
//
//  Created by Abram Himmer on 3/30/18.
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
map<char, string> huffCodes;
int comp;
int exch;
string divider = "-----------------------------------------";


// convert a group of 8 digits to a character
char bin_to_ascii(string group)
{
    bitset<8> temp(group);
    return temp.to_ulong();
}


//Recursive code assignment/Traversal algorithm
void traverse(Node* n, string code){
    if (n->getLeft() == 0x0 && n->getRight() == 0x0){
        //n->setEncoding(code);
        huffCodes[n->getChar()] = code; //add getChar() to hashMap with encoding as its value
        return;
    }
    traverse(n->getLeft(), code +"0");
    traverse(n->getRight(), code+"1");
}

//partition algorithm
int partition(int p, int r) {
    //helper variables
    Node* tmp1;
    Node* tmp2;
    
    //x object --> this x variable serves as the pivot object
    Node* x = huffTree[r];
    
    //i variable --> serves as the indice holder for the top of the smaller portion of the array
    int i = p - 1;
    //j=bottom bound of the array
    for (int j = p; j <= r-1; j++) {
        //count number of comparisons
        comp++;
        
        //actual comparison of the bottom bound and the pivot.  if bottom bound is greater than the pivot,
        //then the indice holder for the lower array is increased (i), and the object in comparison (A[j]) is switched
        //with the upper (A[i])
        if (huffTree[j]->getSum() <= x->getSum()) {
            i++;
            tmp1 = huffTree[i];
            huffTree[i] = huffTree[j];
            huffTree[j] = tmp1;
            exch++;
        }
        
    }
    tmp2 = huffTree[i+1];
    huffTree[i+1] = huffTree[r];
    huffTree[r] = tmp2;
    exch++;
    return i+1;
}


void quickSort(int p, int r){
    //p --> lower bounds, r is highest bounds
    if (p < r) {
        int q = partition(p,r);
        quickSort(p, q-1);
        quickSort(q+1, r);
    }
}

int main(int argc, const char * argv[]) {
    time_t startTotal;
    time_t endTotal;
    startTotal = clock();
    
    
    
    
    /*!-------STEP 1. counting the frequencies-------!*/
    time_t startFreq;
    time_t endFreq;
    startFreq = clock();
    
    //scan thru file with ifs object
    
    ifstream file; //takes in the file
    
    file.open(argv[1], ios::in);
    string inputfile = argv[1];
    
    if (!file){
        cout << "File can not be opened. Try again" << endl;
        exit(1);
    }
    
    //get char method -- get char and increment the freq in the map
    char c;
    while (file.get(c)){
        charFreq[c]++;
    }
    
    endFreq = clock();
    time_t diffFreq = endFreq - startFreq;
    cout << "Counting Chars: " << ((float)diffFreq/CLOCKS_PER_SEC) << endl;
    
    
    
    /* !---------------------------- STEP 2. Create a huffman graph ----------------------------! */
    
    time_t startGraph;
    time_t endGraph;
    startGraph = clock();
    
    //Place all nodes into a vector
    int iterator = 0;
    for (auto e : charFreq){
        Node* n = new Node(e.first, e.second);
        huffTree.push_back(n);
        iterator++; //to be used for the quick sort algorithm.
    }
    
    //sort the vector
    quickSort(0, iterator-1);
    
    //connect the nodes in huffman style
    
    int huffSize = huffTree.size();
    //int q = huffSize;
    for (int i = 1; i <= huffSize-1; i++){
        Node* z = new Node(huffTree[0],huffTree[1]);
        huffTree.erase(huffTree.begin()+0);
        huffTree.erase(huffTree.begin()+0);
        huffTree.push_back(z);
        quickSort(0, huffTree.size()-1);
    }
    
    
    //Print out the total sum for the frequencies in the file.
    //cout << huffTree[0]->getChar() << "sum: " << huffTree[0]->getSum() << endl;
    
    
    endGraph = clock();
    time_t diffGraph = endGraph - startGraph;
    cout << "Making Huff Graph: " << ((float)diffGraph/CLOCKS_PER_SEC) << endl;
    
    /* !-------------------- Step 3. Assign an encoding to each Char ----------------------! */
    
    time_t startTraverse;
    time_t endTraverse;
    startTraverse = clock();
    traverse(huffTree[0],"");
    endTraverse = clock();
    time_t diffTraverse = endTraverse - startTraverse;
    cout << "Assigning Huff Codes: " << ((float)diffTraverse/CLOCKS_PER_SEC) << endl;
    
    
    
    
    /* !-------------------- Step 4. Writing the header for the compressed file ----------------! */
    //write reorganized data to new file
    time_t startWriting;
    time_t endWriting;
    startWriting = clock();
    
    
    //naming the output file name the same as the input file name.
    
    int n = inputfile.length();
    string prefix = inputfile.substr(0, n-4); //grab everything but the .txt
    string outfile = prefix + ".zip301"; //append .zip301 to the end of the file
    ofstream ofs; //write to file object
    ofs.open(outfile);//open file with file name
    
    //write organized data into file
    for (auto e : huffCodes) {
        if(e.first == '\t'){
            ofs <<  e.second << " tab" <<endl;
        }else if (e.first == '\r'){
            ofs << e.second << " return" << endl;
        }else if (e.first == '\n'){
            ofs << e.second << " newline" <<  endl;
        }else if (e.first == ' ') {
            ofs <<  e.second << " space " <<endl;
        }else{
            ofs << e.second << " " << e.first <<endl;
        }
    }
    
    ofs << "*****" << endl;
    
    
    endWriting = clock();
    time_t diffWriting = endWriting - startWriting;
    cout << "Writing header: " << ((float)diffWriting/CLOCKS_PER_SEC) << endl;
    
    
    
    /* !------------------ Step 5. Converting original file into binary code and writing it-----------------! */
    
    
    time_t startConvert;
    time_t endConvert;
    time_t countChars2;
    time_t countChars2e;
    time_t addZero;
    time_t addZeroe;
    time_t binToA;
    time_t binToAe;
    
    startConvert = clock();
    
    
    //place the ifstream object's pointer to the beginning of the file
    file.clear(); //clear the "fail bit"
    file.seekg(0); //point to the beginning of the file
    
    int fileLen=0; //helper string to store binary encoding to
    string bin;
   // string outputS="";
    countChars2 = clock();
    
    while (file.get(c)){
        //fileLen++;
        bin+=huffCodes[c]; //add the char to the output string
        /*
        for (char cc : bin){
            outputS += cc;
            if (outputS.length() == 8){
                ofs<< bin_to_ascii(outputS);
                outputS = "";
            }
        }
         */
    }
    //ofs << "write test" << endl;
    //ofs << bin << endl;
    
    /*if (8 - outputS.length() > 0 ){
        for (int i = 0; i < 8-outputS.length(); i++){
            outputS+='0';
        }
        //ofs << bin_to_ascii(outputS);
    }
    cout << "got past the bin_to_ascii" << endl;
    */
    
    countChars2e = clock();
    time_t diff = countChars2e - countChars2;
    cout << "countChars2: " << ((float)diff/CLOCKS_PER_SEC) << endl;
    
    //addZero = clock();
    ofs << bin.size() << endl; //writing number of bits to file
    long binLen = bin.length() % 8 ; // checking if it is a multiple of 8
    
    //add requisite number of 0's on the end to make the total number of chars a multiple of 8.
    if (binLen != 0){
        for (int i = 0; i < 8-binLen; i++){
            bin += "0";
        }
    }
    
    
    //addZeroe = clock();
    //diff = addZeroe-addZero;
    //cout << "addZero: " << ((float)diff/CLOCKS_PER_SEC) << endl;
    string output;
    binToA = clock();
    //change binary into ASCII chars
    //creating helper string to output as ASCII chars
    for (char c : bin){
        output+=c; //add the char to the output string
        if (output.size() == 8){ //if the output string len == 8 --> switch it to an ASCII char and write
            ofs << bin_to_ascii(output);
            output = ""; //switch it back to empty string.
        }
    }
    
    binToAe = clock();
    
    diff = binToAe - binToA;
    cout << "binToA: " << ((float)diff/CLOCKS_PER_SEC)<< endl;
    

    endConvert = clock();
    time_t diffConvert = endConvert - startConvert;
    cout << "Converting file to binary: " << ((float)diffConvert/CLOCKS_PER_SEC) << endl;
    
    
    
    /* !----------------------------- Step 6. Add file name and extension -----------------------------! */
    
    endTotal = clock();
    time_t diffTotal = endTotal - startTotal;
    cout << "Total time: " << ((float)diffTotal/CLOCKS_PER_SEC) << endl;
    
    
    file.close();
    ofs.close();
    return 0;
    
    
}



/*
 //Making the tree of nodes for the frequencies
 vector<Node*> huffTree;
 for (each frequency){
 huffTree.push_back(new Node(char ch, int freq));
 }
 sort huffTree;
 
 
 while (huffTree.size() > 1){
 node n1 = get first element of huffTree;
 node n2 = get 2nd element of huffTree;
 remove first 2 values from vector;
 node n3 = new node (n1,n2);
 add n3 to vector
 sort vector
 }
 
 
 //Making the encoding for the tree;
 
 write a function called "Traverse"
 traverse(Node* n, string code){
 if n != a leaf (check to see if the node has a char)
 traverse (n->left, code+0)
 traverse (n->right, code+1)
 else //it is a leaf
 char2bin[n_.ch] = code
 bin2char[code] = n->ch;
 }
 
 call the function by:
 traverse (root, "");
 
 
 <!--- THIS IS HOW TO SEE HOW LONG A FUNCTION TAKES
 time_t start;
 time_t end;
 start = clock();
 //double pi = 3.14;
 for ( int i = 0 ; i < 1000; i++){
 //pi *= pi;
 cout << "time killer" << endl;
 }
 end = clock();
 time_t diff = end - start;
 cout << "Elapse time: " <\< ((float)diff/CLOCKS_PER_SEC) << endl;
 */


//how to collect time taken to complete program.
//-->   use the time function. #include <ctime>
// see above!


//TODO how to name the output file the same as the input file
/*
 string inputfile;
 int n = inputfile.length();
 string prefix = inputfile.substr(0, n-4); //check the documentation on this
 string outfile = prefix + ".zip301";
 */

//TODO: how to loop thru each value of a hashtable (map)
//KEYWORD 'auto' --> this is an automatic assignment of whatever value it is to the correct data type. "auto x = 'iam a string';" and "auto x = 3;" both are correct assignments
/*
 for (auto* e : mapName){
 cout << e->first #(first is the field for key for C++'s hashtable map class)
 << e->second; #(second is the filed for value for C++'s hashtable map class)
 */
