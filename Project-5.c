// CST-315-WF900
// Author: Isaac Lund
// Group: A5
// Date: 03/05-10/2024

#include<stdio.h>
#include<stdlib.h>

void pageTable(char pages[]) {

}

int main() {
  char *pages[4];
  FILE *file_1;
  char *str;
  
  file_1 = fopen("Input","w");
  if (file_1 == NULL) {
      perror("Cannot create file.\n");
      return 1;
  }
  
  for (int i = 0; i < 4; i++) {
      str = "page"+i;
      fprintf(file_1,"%s",str);
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
  pages[read] = "\0";
  fclose(file_1);
  
  printf("Here is the input file:\n");
  for (int i = 0; i < 5; i++) {
      printf("%s", pages[i]);
  }
  
  return 0;
}
