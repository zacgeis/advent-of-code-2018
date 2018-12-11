#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // sleep

#define COUNT 400
#define BUFFER 200
#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define SLEEP 2

typedef struct {
  int x;
  int y;
  int vx;
  int vy;
} point_t;

int step = 0;
void display(point_t* points, int points_count, int min_x, int min_y, int width, int height) {
  height += 1;
  printf("\033[2J");
  printf("\033[H");
  printf("Step: %d\n", step);
  char* display = (char*) malloc(sizeof(char) * width * height);
  for (int i = 0; i < width * height; i++) *(display + i) = '.';
  for (int i = 0; i < points_count; i++) {
    point_t* point = points + i;
    *(display + ((point->y - min_y) * width) + (point->x - min_x)) = '#';
  }
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      printf("%c", *(display + (y * width) + x));
    }
    printf("\n");
  }
}

void simulate(point_t* points, int points_count) {
  int width = -1;
  int height = -1;
  int in_zone = 0;
  while (1) {
    for (int i = 0; i < points_count; i++) {
      point_t* point = points + i;
      point->x += point->vx;
      point->y += point->vy;
    }
    int min_xs = 0, min_ys = 0, max_xs = 0, max_ys = 0;
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
    for (int i = 0; i < points_count; i++) {
      point_t* point = points + i;
      if (min_xs == 0 || point->x < min_x) {
        min_xs = 1;
        min_x = point->x;
      }
      if (min_ys == 0 || point->y < min_y) {
        min_ys = 1;
        min_y = point->y;
      }
      if (max_xs == 0 || point->x > max_x) {
        max_xs = 1;
        max_x = point->x;
      }
      if (max_ys == 0 || point->y > max_y) {
        max_ys = 1;
        max_y = point->y;
      }
    }
    width = max_x - min_x;
    height = max_y - min_y;
    step++;
    if (width < MAX_WIDTH && height < MAX_HEIGHT) {
      in_zone = 1;
      printf("in range %d, %d\n", width, height);
      display(points, points_count, min_x, min_y, width, height);
      sleep(SLEEP);
    } else {
      if (in_zone) break; // We've gone past the zone.
    }
  }
}

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[BUFFER];
  int points_count = 0;
  point_t points[COUNT];
  while (fgets(line_buffer, BUFFER, file) != NULL) {
    point_t* point = &points[points_count++];
    sscanf(
      line_buffer,
      "position=<%d,%d> velocity=<%d,%d>",
      &point->x,
      &point->y,
      &point->vx,
      &point->vy
    );
  }
  simulate(points, points_count);
  fclose(file);
  return 0;
}
