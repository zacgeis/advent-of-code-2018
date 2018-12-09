#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT 50001

typedef struct seq_t {
  struct seq_t* previous;
  struct seq_t* next;
  char value;
} seq_t;

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
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

  printf("answer: %d\n", length);
  return 0;
}
