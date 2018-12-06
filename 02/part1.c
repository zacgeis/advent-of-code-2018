#include <stdio.h>
#include <string.h>

#define CHARS 26
#define LINE_BUFFER 30

int main(int argc, char** argv) {
  int twos = 0;
  int threes = 0;
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    int unique_count[CHARS] = { 0 };
    int i = 0;
    while (i < LINE_BUFFER && line_buffer[i] != '\0') {
      unique_count[line_buffer[i] - 'a']++;
      i++;
    }
    int two_counted = 0;
    int three_counted = 0;
    for (i = 0; i < CHARS; i++) {
      if (!two_counted && unique_count[i] == 2) {
        two_counted = 1;
        twos++;
      }
      if (!three_counted && unique_count[i] == 3) {
        three_counted = 1;
        threes++;
      }
    }
  }
  printf("answer: %d\n", twos * threes);
  return 0;
}
