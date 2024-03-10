// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 03/05-10/2024

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char **pageTable() {
    char *pagesTable[4];
    for (int i = 0; i < 4; i++) {
        pagesTable[i] = malloc(256);
        if (pagesTable[i] == NULL) {
            perror("Cannot allocation memory.\n");
            break;
        }
        while (1) {
            int num = (rand() % (7-0+1))+ 0;
            if (i = 0 && (pageTable[1] != "%d",num) && (pageTable[2] != "%d",num) && (pageTable[3] != "%d",num)) {
                pageTable[i] = "%d", num;
                break;
            }
        }
        
    }
    
}

int setUpInput(char **pages) {
    FILE *file_1;
    
    for (int i = 0; i < 4; i++) {
        pages[i] = malloc(256);
        if (pages[i] == NULL) {
            perror("Cannot allocation memory.\n");
            return 1;
        }
    }
    
    file_1 = fopen("Input","w");
    if (file_1 == NULL) {
        perror("Cannot create file.\n");
        return 1;
    }
    
    for (int i = 0; i < 4; i++) {
        sprintf(pages[i], "page%d",i);
        fprintf(file_1,"%s",pages[i]);
    }
    fclose(file_1);
    
    
    file_1 =fopen("Input","r");
    if (file_1 == NULL) {
        perror("Cannot open file.\n");
        return 1;
     }
    
    size_t read = fread(*pages, 1, sizeof(*pages), file_1);
    if (read = 0) {
        perror("Cannot read file.\n");
        fclose(file_1);
        return 1;
    }
    fclose(file_1);
    
    return 0;
}

int main() {
    char *pages[4];
    FILE *file_2;
    
    int t = setUpInput(pages);
    
    printf("Here is the input file:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", pages[i]);
    }
    
    return 0;
}
