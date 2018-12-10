#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 100
#define CHARS 26
#define MAX_DEPTH 10

int solution_i = 0;
int solution[CHARS] = { 0 };
int graph[CHARS][CHARS] = { 0 };
int resolved[CHARS] = { 0 };
int depth[CHARS] = { 0 };

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    char c1, c2;
    sscanf(line_buffer, "%*s %c %*s %*s %*s %*s %*s %c", &c1, &c2);
    graph[c2 - 'A'][c1 - 'A'] = 1;
  }
  int complete = 0;
  while (complete < CHARS) {
    for (int i = 0; i < CHARS; i++) {
      if (resolved[i]) continue;
      int ready = 1;
      for (int j = 0; j < CHARS; j++) {
        if (graph[i][j] == 1) {
          if (resolved[j] == 0) {
            ready = 0;
            break;
          }
        }
      }
      if (ready) {
        complete++;
        resolved[i] = 1;
        solution[solution_i++] = i;
        break;
      }
    }
  }
  printf("answer: ");
  for (int i = 0; i < CHARS; i++) {
    printf("%c", solution[i] + 'A');
  }
  printf("\n");
  return 0;
}
