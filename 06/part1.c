#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 20
#define COUNT 50
#define NODE_COUNT 400000

typedef struct {
  int id;
  int x;
  int y;
  int area;
} point_t;

typedef struct {
  point_t* point;
  int distance;
  int is_org;
  int is_eq;
  int visited;
} cell_t;

typedef struct {
  int points_i;
  point_t points[COUNT];
  int height;
  int width;
  cell_t* cells;
} grid_t;

typedef struct search_node_t {
  int x;
  int y;
  int d;
} search_node_t;

void clear_visited(grid_t* grid) {
  for (int y = 0; y < grid->height; y++) {
    for (int x = 0; x < grid->width; x++) {
      (grid->cells + (y * grid->width) + x)->visited = 0;
    }
  }
}

void fill(grid_t* grid, point_t* point, int start_x, int start_y) {
  // Use a sliding window approach as a queue
  search_node_t nodes[NODE_COUNT];
  int node_i = 0;
  int node_length = 0;

  search_node_t* node = nodes + node_length++;
  node->x = start_x;
  node->y = start_y;
  node->d = 0;

  while (node_i < node_length) {
    node = nodes + node_i++;
    if (node->x < 0 || node->x >= grid->width || node->y < 0 || node->y >= grid->height) {
      continue;
    }

    cell_t* cell = grid->cells + (node->y * grid->width) + node->x;

    if (cell->visited) {
      continue;
    }

    cell->visited = 1;

    // Equal distance don't count. If it gets claimed again, that's fine.
    // Having language constraints makes it easier to come up with creative solutions.
    if (node->d == cell->distance) {
      cell->is_eq = 1;
      cell->point = NULL;
    }
    if (cell->distance == -1 || node->d < cell->distance) {
      cell->point = point;
      cell->distance = node->d;
    }

    search_node_t* next = nodes + node_length++;
    next->x = node->x + 1;
    next->y = node->y;
    next->d = node->d + 1;

    next = nodes + node_length++;
    next->x = node->x - 1;
    next->y = node->y;
    next->d = node->d + 1;

    next = nodes + node_length++;
    next->x = node->x;
    next->y = node->y + 1;
    next->d = node->d + 1;

    next = nodes + node_length++;
    next->x = node->x;
    next->y = node->y - 1;
    next->d = node->d + 1;
  }

  clear_visited(grid);
}

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  grid_t grid = { 0, { { 0 } }, 0, 0, NULL };
  char line_buffer[LINE_BUFFER];
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    point_t* point = grid.points + grid.points_i;
    sscanf(line_buffer, "%d, %d", &point->x, &point->y);
    point->id = grid.points_i;
    grid.points_i += 1;
  }

  int maxX = -1, minX = -1, maxY = -1, minY = -1;
  for (int i = 0; i < grid.points_i; i++) {
    point_t* point = grid.points + i;
    if (maxX == -1 || point->x > maxX) maxX = point->x;
    if (minX == -1 || point->x < minX) minX = point->x;
    if (maxY == -1 || point->y > maxY) maxY = point->y;
    if (minY == -1 || point->y < minY) minY = point->y;
  }
  grid.width = maxX - minX + 1;
  grid.height = maxY - minY + 1;
  for (int i = 0; i < grid.points_i; i++) {
    point_t* point = grid.points + i;
    point->x -= minX;
    point->y -= minY;
  }

  grid.cells = (cell_t*) malloc(sizeof(cell_t) * grid.width * grid.height);
  for (int y = 0; y < grid.height; y++) {
    for (int x = 0; x < grid.width; x++) {
      *(grid.cells + (y * grid.width) + x) = (cell_t) { NULL, -1, 0, 0, 0 };
    }
  }

  for (int i = 0; i < grid.points_i; i++) {
    point_t* point = grid.points + i;
    cell_t* cell = grid.cells + (point->y * grid.width) + point->x;
    cell->point = point;
    cell->distance = -1;
    cell->is_org = 1;
  }

  for (int i = 0; i < grid.points_i; i++) {
    point_t* point = grid.points + i;
    fill(&grid, point, point->x, point->y);
  }

  for (int i = 0; i < grid.width * grid.height; i++) {
    cell_t* cell = grid.cells + i;
    if (cell->point != NULL) {
      cell->point->area += 1;
    }
  }

  int max_area = -1;
  for (int i = 0; i < grid.points_i; i++) {
    point_t* point = grid.points + i;
    if (max_area == -1 || point->area > max_area) {
      max_area = point->area;
    }
  }

  printf("answer: %d\n", max_area);

  free(grid.cells);
  return 0;
}
