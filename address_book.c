//
//  address_book.c
//  HYoshidaAddressBook
//
//  Created by Hideaki Yoshida on 4/12/17.
//  Copyright © 2017 Hideaki Yoshida. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

void add(int ndx, char str[], pNode* top){
    // Create a node by allocating a memory.
    pNode newNode = malloc(sizeof(Node));
    pNode cur;
    
    if (newNode) {
        newNode->next = NULL;
        // Split the string to initialize members in the node.
        strcpy(newNode->lastname, strtok(str, ","));
        strcpy(newNode->firstname, strtok(NULL, ","));
        strcpy(newNode->email, strtok(NULL, ","));
        strcpy(newNode->phoneNum, strtok(NULL, "\n"));
        // Insert node at the top.
        if (ndx == 0) {
            newNode->next = *top;
            *top = newNode;
        }
        //Insert node at the index.
        else {
            int i = 0;
            cur = *top;
            while (i < ndx - 1) {
                cur = cur->next;
                i++;
            }
            newNode->next = cur->next;
            cur->next = newNode;
        }
        
    }
}

void delete(int ndx, int num, pNode* top){
    pNode cur1;
    pNode cur2;
    pNode cur3;
    int i = 0;
    int j = 0;
    // Executes when index is less than the total number of nodes in the list.
    if (ndx <= num - 1) {
        // Delete a node at the end.
        if (ndx == num - 1) {
            // cur1 points to top.
            cur1 = *top;
            //Traverse cur1 to before the node I'm trying to delete
            while (i < ndx - 1) {
                cur1 = cur1->next;
                i++;
            }
            // cur2 points to cur1->next (the node I'm trying to delete).
            cur2 = cur1->next;
            cur1->next = NULL;
            // Clear memory (delete a node)
            free(cur2);
            cur2 = NULL;
            
        }
        // Delete a node in the middle.
        if ((ndx < num - 1) && (ndx > 0)) {
            cur1 = *top;
            cur3 = *top;
            // Traverse cur3 to before the node I'm trying to delete
            while (j < ndx - 1) {
                cur3 = cur3->next;
                j++;
            }
            // cur1 points to cur3->next.
            cur1 = cur3->next;
            // cur3->next points to cur1->next.
            cur3->next = cur1->next;
            free(cur1);
            cur1 = NULL;
        }
        // Delete a node at the top.
        if (ndx == 0) {
            // cur2 points to top.
            cur2 = *top;
            // cur1 points to the next node of top.
            cur1 = (*top)->next;
            // top points to cur1.
            *top = cur1;
            free(cur2);
            cur2 = NULL;
        }
    }

}

void getContact(int ndx, pNode* top){
    pNode cur = *top;
    int i = 0;
    
    while (i < ndx) {
        cur = cur->next;
        i++;
    }
    printf("%s,%s,%s,%s\n", cur->lastname, cur->firstname, cur->email, cur->phoneNum);
}

void getField(int ndx, char str[], pNode* top){
    pNode cur = *top;
    int i = 0;
    
    while (i < ndx) {
        cur = cur->next;
        i++;
    }
    
    switch (str[0]) {
        case 'l':
            printf("%s\n", cur->lastname);
            break;
        case 'f':
            printf("%s\n", cur->firstname);
            break;
        case 'e':
            printf("%s\n", cur->email);
            break;
        case 'p':
            printf("%s\n", cur->phoneNum);
            break;
            
    }

}

int getNum(pNode* top){
    pNode cur = *top;
    int count = 0;
    // Traverse the cursor while there is a node.
    while (cur != NULL) {
        cur = cur->next;
        count++;
    }
    
    return count;
}

void load(char str[], pNode* top){
    char data[BUFSIZ];
    // Open CSV file to read the contracts.
    FILE* pFile = fopen(str, "r");
    // Get the first line in the file.
    fgets(data, BUFSIZ, pFile);
    // Total number of nodes being passed for adding the contracts in the file after the already existed nodes in the list
    int position = getNum(top);
    // Read every line in the file
    while (fgets(data, BUFSIZ, pFile) != NULL) {
        // call add() to create a node and to initialize members.
        add(position, data, top);
        // position to add changed for every contracts that got added to the list.
        position++;
    }
    
    pclose(pFile);
}

void save(char str[], pNode* top){
    FILE* pFile = fopen(str, "w");
    pNode cur = *top;
    fprintf(pFile, "lastName,firstName,email,phoneNumber\n");
    
    while (cur != NULL) {
        fprintf(pFile, "%s,%s,%s,%s\n", cur->lastname, cur->firstname,cur->email, cur->phoneNum);
        cur = cur->next;
    }
    
    fclose(pFile);
}

void edit(int ndx, char str1[], char str2[], pNode* top){
    pNode cur = *top;
    int i = 0;
    
    while (i < ndx) {
        cur = cur->next;
        i++;
    }
    
    switch (str1[0]) {
        case 'l':
            strcpy(cur->lastname, str2);
            break;
        case 'f':
            strcpy(cur->firstname, str2);
            break;
        case 'e':
            strcpy(cur->email, str2);
            break;
        case 'p':
            strcpy(cur->phoneNum, str2);
            break;
    }

}

void sort(pNode* top){
    pNode cur1 = *top;
    pNode cur2 = *top;
    int i,j;
    int k;
    int n = getNum(top);
    int minNdx;
    
    for(i = 0; i < n-1; i++){
        minNdx = i + 1;
        for(k = 0; k <= minNdx; k++){
            cur1 = cur1->next;
        }
        for(j = i; j < n; j++){
            for(k = 0; k <= j; k++){
                cur2 = cur2->next;
            }
            if(strcmp(cur1->lastname, cur2->lastname) > 0){
                minNdx = j;
            }
        }
        if (i != minNdx){
            swap(&cur1,&cur2);
        }
    }
    
    for(i = 0; i < n-1; i++){
        minNdx = i + 1;
        for(k = 0; k <= minNdx; k++){
            cur1 = cur1->next;
        }
        for(j = i; j < n; j++){
            for(k = 0; k <= j; k++){
                cur2 = cur2->next;
            }
            if(strcmp(cur1->lastname, cur2->lastname) == 0 && strcmp(cur1->firstname, cur2->firstname) > 0){
                minNdx = j;
            }
        }
        if (i != minNdx){
            swap(&cur1,&cur2);
        }
    }
    
    for(i = 0; i < n-1; i++){
        minNdx = i + 1;
        for(k = 0; k <= minNdx; k++){
            cur1 = cur1->next;
        }
        for(j = i; j < n; j++){
            for(k = 0; k <= j; k++){
                cur2 = cur2->next;
            }
            if(strcmp(cur1->lastname, cur2->lastname) == 0 && strcmp(cur1->firstname, cur2->firstname) == 0 && strcmp(cur1->email, cur2->email) > 0){
                minNdx = j;
            }
        }
        if (i != minNdx){
            swap(&cur1,&cur2);
        }
    }
    
    for(i = 0; i < n-1; i++){
        minNdx = i + 1;
        for(k = 0; k <= minNdx; k++){
            cur1 = cur1->next;
        }
        for(j = i; j < n; j++){
            for(k = 0; k <= j; k++){
                cur2 = cur2->next;
            }
            if(strcmp(cur1->lastname, cur2->lastname) == 0 && strcmp(cur1->firstname, cur2->firstname) == 0 && strcmp(cur1->email, cur2->email) == 0 && strcmp(cur1->phoneNum, cur2->phoneNum) > 0){
                minNdx = j;
            }
        }
        if (i != minNdx){
            swap(&cur1,&cur2);
        }
    }
}

void swap(pNode* first, pNode* second){
    pNode temp = *first;
    *first = *second;
    *second = temp;
}
