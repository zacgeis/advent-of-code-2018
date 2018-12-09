#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 50001

typedef struct seq_t {
  struct seq_t* previous;
  struct seq_t* next;
  char value;
} seq_t;

int solve_skipping(char* filename, char skip) {
  FILE* file = fopen(filename, "r");
  seq_t seqs[COUNT] = { { NULL, NULL, '?' } };
  int seqs_i = 0;
  seq_t* previous = NULL;
  char c;
  while ((c = fgetc(file)) != EOF) {
    seq_t* current = seqs + seqs_i;
    current->value = c;
    current->previous = previous;
    if (previous != NULL) previous->next = current;
    previous = current;
    seqs_i += 1;
  }

  seq_t* current = seqs;
  while (1) {
    if (current->value == skip || current->value == (skip - 32)) {
      if (current->next != NULL) {
        current->next->previous = current->previous;
        if (current->previous != NULL) current->previous->next = current->next;
        current = current->next;
      } else {
        current = current->previous;
        break;
      }
    } else {
      if (current->next == NULL) break;
      current = current->next;
    }
  }

  // Rewind
  while (current->previous != NULL) current = current->previous;

  while (current != NULL && current->next != NULL) {
    // 32 is the difference between lowercase and uppercase
    if (abs(current->value - current->next->value) == 32) {
      if (current->next->next != NULL) {
        current->next->next->previous = current->previous;
        if (current->previous != NULL) {
          current->previous->next = current->next->next;
        }
        current = current->next->next;
        if (current->previous != NULL) {
          current = current->previous;
        }
      }
    } else {
      current = current->next;
    }
  }

  int length = 0;
  while ((current = current->previous) != NULL) length++;

  return length;
}

int main(int argc, char** argv) {
  int shortest = -1;
  for (char i = 'a'; i <= 'z'; i++) {
    int length = solve_skipping(argv[1], i);
    if (shortest == -1 || length < shortest) {
      shortest = length;
    }
  }

  printf("answer: %d\n", shortest);
  return 0;
}
