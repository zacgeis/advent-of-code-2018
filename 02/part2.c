#include <stdio.h>
#include <string.h>

#define CHARS 26
#define LINE_BUFFER 30
#define LINE_COUNT 250

int main(int argc, char** argv) {
  char input[LINE_COUNT][LINE_BUFFER];
  FILE* file = fopen(argv[1], "r");
  int line = 0;
  while (fgets(input[line++], LINE_BUFFER, file) != NULL);
  for (int i = 0; i < LINE_COUNT; i++) {
    for (int j = i; j < LINE_COUNT; j++) {
      int diffs = 0;
      for (int z = 0; z < LINE_BUFFER; z++) {
        if (input[i][z] != input[j][z]) {
          diffs += 1;
          if (diffs > 1) break;
        }
      }
      if (diffs == 1) {
        printf("answer: ");
        for (int z = 0; z < LINE_BUFFER; z++) {
          if (input[i][z] == input[j][z]) {
            printf("%c", input[i][z]);
          }
        }
        printf("\n");
        return 0;
      }
    }
  }
  return 1;
}
