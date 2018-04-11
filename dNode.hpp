//
//  Node.hpp
//  FinalProject
//
//  Created by Abram Himmer on 4/9/18.
//  Copyright © 2018 Abram Himmer. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#pragma once
#include <string>

#include <stdio.h>
class Node
{
private:
    int sum;
    Node* left;
    Node* right;
    char ch;
    std::string encoding;
public:
    Node();
    Node(Node*, Node*); //parent nodes
    Node(char, Node*, Node*); //leaf nodes
    Node(char, int);
    char getChar();
    int getSum();
    Node* getLeft();
    Node* getRight();
    void addZero();
    void addOne();
    std::string writeMe();
    std::string getEncoding();
    void setEncoding(std::string);
    
};

#endif /* Node_hpp */
