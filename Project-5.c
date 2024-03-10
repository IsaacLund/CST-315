// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 03/05-10/2024

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int pageTable(char **pagesTable) {
    for (int i = 0; i < 4; i++) {
        printf("\n2-Here-%d!\n",i);
        while (1) {
            int num = (rand() % (7-0+1))+ 0;
            if (i = 0 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("\n2-Here-a!\n");
                break;
            } else if (i = 1 && (atoi(pagesTable[0]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("\n2-Here-b!\n");
                break;
            } else if (i = 2 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[0]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("\n2-Here-c!\n");
                break;
            } else if (i = 3 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[0]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("\n2-Here-d!\n");
                break;
            } else {
                printf("\n2-Here-e!\n");
                break;
            }
        }
    }
    return 0;
}

int setUpInput(char **pages) {
    FILE *file_1;
    
    file_1 = fopen("Input","w");
    if (file_1 == NULL) {
        perror("Cannot create file.\n");
        return 1;
    }
    
    for (int i = 0; i < 4; i++) {
        sprintf(pages[i], "pge%d",i);
        fprintf(file_1,"%s\n",pages[i]);
    }
    fclose(file_1);
    
    file_1 =fopen("Input","r");
    if (file_1 == NULL) {
        perror("Cannot open file.\n");
        return 1;
     }
    
    size_t read = fread(*pages, 4, 1, file_1);
    
    if (read = 0) {
        perror("Cannot read file.\n");
        fclose(file_1);
        return 1;
    }
    fclose(file_1);
    printf("\n1-Here!\n");
    return 0;
}

int setUpOutput(char **pages, char **table) {
    FILE *file_2;
    
    file_2 = fopen("Output","w");
    if (file_2 == NULL) {
        perror("Cannot create file.\n");
        return 1;
    }
    
    for (int i = 0; i < 7; i++) {
        fprintf(file_2,"%d | ", i);
        for (int j = 0; i < 4; j++) {
            if (atoi(table[j]) == i) {
                fprintf(file_2,"%s",pages[j]);
                break;
            }
        }
        fprintf(file_2,"\n");
    }
    fclose(file_2);
    
    return 0;
}

int main() {
    char *pages[4];
    for (int i = 0; i < 4; i++) {
        pages[i] = malloc(256);
        if (pages[i] == NULL) {
            perror("1-Cannot allocation memory.\n");
            return 1;
        }
    }
    
    char *table[4];
    for (int i = 0; i < 4; i++) {
        table[i] = malloc(256);
        if (table[i] == NULL) {
            perror("2-Cannot allocation memory.\n");
            return 1;
        }
    }
    
    
    int input = setUpInput(pages);
    
    printf("Here is the input file:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", pages[i]);
    }
    
    printf("\n2-Here!\n");
    int process = pageTable(table);
    printf("\n3-Here!\n");
    int output = setUpOutput(pages, table);
    printf("\n4-Here!\n");
    return 0;
}
