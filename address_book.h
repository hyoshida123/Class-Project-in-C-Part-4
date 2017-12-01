//
//  address_book.h
//  HYoshidaAddressBook
//
//  Created by Hideaki Yoshida on 4/12/17.
//  Copyright © 2017 Hideaki Yoshida. All rights reserved.
//

#ifndef address_book_h
#define address_book_h

typedef struct contact Node;
// Structure of contract
struct contact {
    char firstname[100];
    char lastname[100];
    char email[100];
    char phoneNum[100];
    Node* next;
};

typedef Node* pNode;

void add(int ndx, char str[], pNode* top);

void delete(int ndx, int num, pNode* top);

void getContact(int ndx, pNode* top);

void getField(int ndx, char str[], pNode* top);

int getNum(pNode* top);

void load(char str[], pNode* top);

void save(char str[], pNode* top);

void edit(int ndx, char str1[], char str2[], pNode* top);

void sort(pNode* top);

void swap(pNode* first, pNode* seond);

#endif /* address_book_h */
