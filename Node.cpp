//
//  Node.cpp
//  FinalProject
//
//  Created by Abram Himmer on 4/6/18.
//  Copyright © 2018 Abram Himmer. All rights reserved.
//

#include "Node.hpp"

Node::Node(){
    left = NULL;
    right = NULL;
    sum = 0;
    ch = NULL;
    encoding = "null";
}
Node::Node(Node* n1, Node* n2){
    left = n1;
    right = n2;
    sum = n1->getSum()+n2->getSum();
    ch = NULL;
    encoding = "";
}

Node::Node(char cha, Node* n1, Node* n2){
    left = n1;
    right = n2;
    sum = 0;
    ch = cha;
    encoding = "";
}

Node::Node(char cha, int freq){
    left = NULL;
    right = NULL;
    sum = freq;
    ch = cha;
    encoding = "";
}

char Node::getChar(){
    return ch;
}

int Node::getSum(){
    return sum;
}
Node* Node::getLeft(){
    return left;
}

Node* Node::getRight(){
    return right;
}

std::string Node::getEncoding(){
    return encoding;
}

void Node::setEncoding(std::string huffCode){
    encoding = huffCode;
}

std::string Node::writeMe(){
    return encoding;
}
;
