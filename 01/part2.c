#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 20
#define QUICKVIEW 1000000
#define PREVIOUS 1000000

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  int current = 0;
  int previous_quickview[QUICKVIEW] = { 0 };
  int previous[PREVIOUS];
  int previous_length = 0;
  while (1) {
    if (fgets(line_buffer, sizeof(line_buffer), file) == NULL) {
      rewind(file);
      continue;
    }
    char sign;
    int num;
    sscanf(line_buffer, "%c%d%*c", &sign, &num);
    if (sign == '-') num *= -1;
    current += num;
    unsigned int bucket = ((unsigned int) current) % QUICKVIEW;
    if (previous_quickview[bucket]) {
      for (int i = 0; i < previous_length; i++) {
        if (previous[i] == current) {
          printf("answer: %d\n", current);
          return 0;
        }
      }
    }
    previous[previous_length++] = current;
    previous_quickview[bucket] = 1;
  }
  return 1;
}
