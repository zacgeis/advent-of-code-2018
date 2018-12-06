#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 20

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  int answer = 0;
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    char sign;
    int num;
    sscanf(line_buffer, "%c%d%*c", &sign, &num);
    if (sign == '-') num *= -1;
    answer += num;
  }
  printf("answer: %d\n", answer);
  return 0;
}
