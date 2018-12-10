#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PLAYERS 465
#define LAST_MARBLE_WORTH 7194000

typedef struct node_t {
  struct node_t* previous;
  struct node_t* next;
  int value;
} node_t;

int main(int argc, char** argv) {
  unsigned long scores[PLAYERS];
  for (int i = 0; i < PLAYERS; i++) scores[i] = 0;

  int current_marble = 0;
  int player = -1;
  node_t* node = (node_t*) malloc(sizeof(node_t));
  node->previous = node;
  node->next = node;
  node->value = current_marble;

  while (current_marble <= LAST_MARBLE_WORTH) {
    current_marble += 1;
    player = (player + 1) % PLAYERS;
    if (current_marble % 23 == 0) {
      long points = 0;
      points += current_marble;
      for (int i = 0; i < 7; i++) node = node->previous;
      points += node->value;
      scores[player] += points;
      node->previous->next = node->next;
      node->next->previous = node->previous;
      node_t* temp = node;
      node = node->next;
      free(temp);
    } else {
      node_t* temp = (node_t*) malloc(sizeof(node_t));
      temp->value = current_marble;
      temp->previous = node->next;
      temp->next = node->next->next;
      node->next->next->previous = temp;
      node->next->next = temp;
      node = temp;
    }
  }

  unsigned long max_score = 0;
  for (int i = 0; i < PLAYERS; i++) {
    if (scores[i] > max_score) max_score = scores[i];
  }
  printf("answer: %lu\n", max_score);

  return 0;
}
