#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 30
#define FABRIC_LENGTH 1000
#define SECTIONS 2000

typedef struct section_t {
  int id;
  int x;
  int y;
  int w;
  int h;
  // different way of thinking when you don't have easy access to containers, etc.
  int overlapped;
} section_t;

void apply_section(section_t** fabric, section_t* section) {
  for (int i = 0; i < section->h; i++) {
    for (int j = 0; j < section->w; j++) {
      section_t* cell = *(fabric + ((section->y + i) * FABRIC_LENGTH) + (section->x + j));
      if (cell != NULL) {
        cell->overlapped = 1;
        section->overlapped = 1;
      } else {
        *(fabric + ((section->y + i) * FABRIC_LENGTH) + (section->x + j)) = section;
      }
    }
  }
}

int main(int argc, char** argv) {
  section_t* sections = (section_t*) malloc(sizeof(section_t) * SECTIONS);
  int sections_i = 0;
  section_t** fabric = (section_t**) malloc(sizeof(section_t*) * FABRIC_LENGTH * FABRIC_LENGTH);
  for (int i = 0; i < FABRIC_LENGTH * FABRIC_LENGTH; i++) *(fabric + i) = NULL;
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    section_t* section = sections + sections_i++;
    sscanf(line_buffer, "#%d @ %d,%d: %dx%d", &section->id, &section->x, &section->y, &section->w, &section->h);
    apply_section(fabric, section);
  }
  for (int i = 0; i < FABRIC_LENGTH * FABRIC_LENGTH; i++) {
    section_t* section = *(fabric + i);
    if (section != NULL && section->overlapped != 1) {
      printf("answer: %d\n", (*(fabric + i))->id);
      break;
    }
  }
  free(sections);
  free(fabric);
  return 0;
}
