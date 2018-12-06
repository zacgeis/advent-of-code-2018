#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 30
#define FABRIC_LENGTH 1000

int main(int argc, char** argv) {
  short fabric[FABRIC_LENGTH][FABRIC_LENGTH];
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    int id = 0, x = 0, y = 0, w = 0, h = 0;
    sscanf(line_buffer, "#%d @ %d,%d: %dx%d", &id, &x, &y, &w, &h);
    // printf("id: %d, x: %d, y: %d, w: %d, h: %d\n", id, x, y, w, h);
  }
  // printf("answer: %d\n", 1);
  return 0;
}
