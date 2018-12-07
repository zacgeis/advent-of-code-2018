#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 30
#define FABRIC_LENGTH 1000

typedef struct section_t {
  int id;
  int x;
  int y;
  int w;
  int h;
} section_t;

void add_section(short* fabric, section_t* section) {
  for (int i = 0; i < section->h; i++) {
    for (int j = 0; j < section->w; j++) {
      *(fabric + ((section->y + i) * FABRIC_LENGTH) + (section->x + j)) += 1;
    }
  }
}

int main(int argc, char** argv) {
  short* fabric = (short*) malloc(sizeof(short) * FABRIC_LENGTH * FABRIC_LENGTH);
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    section_t section;
    sscanf(line_buffer, "#%d @ %d,%d: %dx%d", &section.id, &section.x, &section.y, &section.w, &section.h);
    add_section(fabric, &section);
  }
  int answer = 0;
  for (int i = 0; i < FABRIC_LENGTH * FABRIC_LENGTH; i++) {
    if (*(fabric + i) >= 2) {
      answer++;
    }
  }
  free(fabric);
  printf("answer: %d\n", answer);
  return 0;
}
