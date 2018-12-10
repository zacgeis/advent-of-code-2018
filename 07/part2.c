#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 100
#define CHARS 26
#define WORKER_COUNT 5

int solution_i = 0;
int solution[CHARS] = { 0 };
int graph[CHARS][CHARS] = { 0 };
int resolved[CHARS] = { 0 };
int assigned[CHARS] = { 0 };
int workers[WORKER_COUNT] = { 0 };
int workers_item[WORKER_COUNT] = { 0 };

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    char c1, c2;
    sscanf(line_buffer, "%*s %c %*s %*s %*s %*s %*s %c", &c1, &c2);
    graph[c2 - 'A'][c1 - 'A'] = 1;
  }
  int time = 0;
  int complete = 0;
  for (int i = 0; i < WORKER_COUNT; i++) workers_item[i] = -1;
  while (complete < CHARS) {
    for (int i = 0; i < CHARS; i++) {
      if (resolved[i] == 1) continue;
      if (assigned[i] == 1) continue;
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
        for (int w = 0; w < WORKER_COUNT; w++) {
          if (workers_item[w] == -1) {
            assigned[i] = 1;
            workers[w] = 60 + i;
            workers_item[w] = i;
            break;
          }
        }
      }
    }
    for (int w = 0; w < WORKER_COUNT; w++) {
      if (workers[w] == 0 && workers_item[w] != -1) {
        resolved[workers_item[w]] = 1;
        solution[solution_i++] = workers_item[w];
        complete++;
        workers_item[w] = -1;
      } else {
        workers[w] -= 1;
      }
    }
    time++;
  }
  for (int i = 0; i < CHARS; i++) {
    printf("%c", solution[i] + 'A');
  }
  printf("\n");
  printf("answer: %d\n", time);
  return 0;
}
