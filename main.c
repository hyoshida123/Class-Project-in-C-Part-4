//
//  main.c
//  HYoshidaAddressBook
//
//  Created by Hideaki Yoshida on 4/12/17.
//  Copyright © 2017 Hideaki Yoshida. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

int main(int argc, const char * argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    char input[10];
    int flag = 1;
    int ndx;
    char num[BUFSIZ+1], str1[BUFSIZ+1], str2[BUFSIZ+1];
    int number;
    pNode top = NULL;
    
    printf("Ready\n");
    while (flag != 0) {
        fgets(input, 9, stdin);
        switch (input[0]) {
            case 'a':
                ndx = atoi(fgets(num,BUFSIZ,stdin));
                fgets(str1,BUFSIZ,stdin);
                add(ndx,str1,&top);
                break;
            case 'd':
                ndx = atoi(fgets(num,BUFSIZ,stdin));
                number = getNum(&top);
                delete(ndx, number, &top);
                break;
            case 'g':
                ndx = atoi(fgets(num,BUFSIZ,stdin));
                getContact(ndx,&top);
                break;
            case 'f':
                ndx = atoi(fgets(num,BUFSIZ,stdin));
                fgets(str1,BUFSIZ,stdin);
                str1[strlen(str1)-1] = '\0';
                getField(ndx, str1,&top);
                break;
            case 'n':
                printf("%d\n", getNum(&top));
                break;
            case 'l':
                fgets(str1,BUFSIZ,stdin);
                str1[strlen(str1)-1] = '\0';
                load(str1,&top);
                break;
            case 's':
                fgets(str1,BUFSIZ,stdin);
                str1[strlen(str1)-1] = '\0';
                save(str1,&top);
                break;
            case 'e':
                ndx = atoi(fgets(num,BUFSIZ,stdin));
                fgets(str1,BUFSIZ,stdin);
                str1[strlen(str1)-1] = '\0';
                fgets(str2,BUFSIZ,stdin);
                str2[strlen(str2)-1] = '\0';
                edit(ndx,str1,str2,&top);
                break;
            case 'o':
                sort(&top);
                break;
            case 'q':
                printf("Complete\n");
                flag = 0;
                break;
        }
    }
    return 0;
}
