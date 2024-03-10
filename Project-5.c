// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 03/05-10/2024

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// This creates an array of the same size of local memory input, giving random physical memory address number location as array elements to link to the local memory
int pageTable(char **pagesTable) {
    srand(time(0));
    printf("\n\nPage Table: \n");
    for (int i = 0; i < 4; i++) {
        while (1) {
            int num = (rand() % 8);
            if (i == 0 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("page0 | %d\n", num);
                break;
            } else if (i == 1 && (atoi(pagesTable[0]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("page1 | %d\n", num);
                break;
            } else if (i == 2 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[0]) != num) && (atoi(pagesTable[3]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("page2 | %d\n", num);
                break;
            } else if (i == 3 && (atoi(pagesTable[1]) != num) && (atoi(pagesTable[2]) != num) && (atoi(pagesTable[0]) != num)) {
                sprintf(pagesTable[i],"%d", num);
                printf("page3 | %d\n", num);
                break;
            }
        }
    }
    return 0;
}

// This setup creates and reads an input file with a given local memory.
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
    
    for (int i = 0; i < 4; i++) {
        if (fscanf(file_1, "%s", pages[i]) != 1) {
            perror("Cannot read file.\n");
            fclose(file_1);
            return 1;
        }
    }
    
    fclose(file_1);
    return 0;
}


// takes the array of the page table and pages to assign the local memory data into the correct physical memory locations given by pagetable and displays it.
int setUpOutput(char **pages, char **table) {
    FILE *file_2;
    printf("\n\nPhyscial memory:\n");
    
    file_2 = fopen("Output","w");
    if (file_2 == NULL) {
        perror("Cannot create file.\n");
        return 1;
    }
    
    for (int i = 0; i < 8; i++) {
        fprintf(file_2,"%d | ", i);
        printf("%d | ", i);
        for (int j = 0; j < 4; j++) {
            if (atoi(table[j]) == i) {
                fprintf(file_2,"%s",pages[j]);
                printf("%s",pages[j]);
                break;
            }
        }
        fprintf(file_2,"\n");
        printf("\n\n\n");
    }
    fclose(file_2);
    
    return 0;
}


// creates the arrays for pages input and table for pagetable with memory allocation and then runs two methods and frees the memory.
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
    
    printf("\n\nLocal memory:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", pages[i]);
    }
    
    
    int process = pageTable(table);
    
    int output = setUpOutput(pages, table);
    
    for (int i = 0 ; i < 4; i++) {
        free(pages[i]);
        free(table[i]);
    }
    
    return 0;
}
