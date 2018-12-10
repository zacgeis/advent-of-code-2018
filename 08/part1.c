#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COUNT 50000

int answer = 0;
int values[MAX_COUNT];
int value_count = 0;

int navigate(int l) {
  int child_count = values[l++];
  int meta_count = values[l++];
  for (int i = 0; i < child_count; i++) {
    l = navigate(l);
  }
  for (int i = 0; i < meta_count; i++) {
    answer += values[l++];
  }
  return l;
}

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  int d;
  while (fscanf(file, "%d", &d) > 0) {
    values[value_count++] = d;
  }
  navigate(0);
  printf("answer: %d\n", answer);
  return 0;
}
