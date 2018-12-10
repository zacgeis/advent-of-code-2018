#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COUNT 50000

int answer = 0;
int values[MAX_COUNT] = { 0 };
int value_count = 0;
int points[MAX_COUNT] = { 0 };
int point_count = 0;

int navigate(int l, int p) {
  int child_count = values[l++];
  int meta_count = values[l++];
  int *child_points;
  int child_points_count = 0;
  if (child_count > 0) {
    child_points = (int*) malloc(sizeof(int) * child_count);
  }
  for (int i = 0; i < child_count; i++) {
    int ps = point_count++;
    child_points[child_points_count++] = ps;
    l = navigate(l, ps);
  }
  if (child_count == 0) {
    for (int i = 0; i < meta_count; i++) {
      points[p] += values[l++];
    }
  } else {
    for (int i = 0; i < meta_count; i++) {
      int ind = values[l++];
      if (ind >= 1 && ind < child_count + 1) {
        points[p] += points[child_points[ind - 1]];
      }
    }
  }
  free(child_points);
  return l;
}

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  int d;
  while (fscanf(file, "%d", &d) > 0) {
    values[value_count++] = d;
  }
  navigate(0, point_count++);
  printf("answer: %d\n", points[0]);

  return 0;
}
