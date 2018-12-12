#include <stdio.h>

#define INPUT 8772
#define SIZE 300

int grid[SIZE][SIZE];

int power_level(int x, int y) {
  int rid = x + 10;
  int pw = rid * y;
  pw += INPUT;
  pw *= rid;
  pw = ((pw / 100) % 10);
  pw -= 5;
  return pw;
}

int scan(int start_x, int start_y, int size) {
  int value = 0;
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      value += grid[start_y + y][start_x + x];
    }
  }
  return value;
}

int main(int argc, char** argv) {
  for (int y = 0; y < SIZE; y++) {
    for (int x = 0; x < SIZE; x++) {
      grid[y][x] = power_level(x, y);
    }
  }
  int is_set = 0;
  int max_x = 0;
  int max_y = 0;
  int max_size = 0;
  int max_value = 0;
  for (int s = 1; s <= 300; s++) {
    printf("running size: %d\n", s);
    for (int y = 0; y < SIZE - s; y++) {
      for (int x = 0; x < SIZE - s; x++) {
        int value = scan(x, y, s);
        if (is_set == 0 || value > max_value) {
          is_set = 1;
          max_x = x;
          max_y = y;
          max_size = s;
          max_value = value;
        }
      }
    }
  }
  printf("answer: x: %d, y: %d, size: %d, value: %d\n", max_x, max_y, max_size, max_value);
  return 0;
}
