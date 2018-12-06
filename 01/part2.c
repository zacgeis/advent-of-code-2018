#include <stdio.h>
#include <string.h>

#define LINE_BUFFER 20
#define BUCKETS 10000
#define NODES 200000

struct node_t {
  struct node_t* next;
  int value;
};
typedef struct node_t node_t;

int main(int argc, char** argv) {
  node_t nodes[NODES] = { { .next = NULL, .value = 0 } };
  int node_i = 0;
  node_t* buckets[BUCKETS] = { NULL }; // array of pointers to nodes
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  int current = 0;
  while (1) {
    if (fgets(line_buffer, sizeof(line_buffer), file) == NULL) {
      rewind(file);
      continue;
    }
    char sign;
    int num;
    sscanf(line_buffer, "%c%d%*c", &sign, &num);
    if (sign == '-') num *= -1;
    current += num;
    node_t* new_node = &nodes[node_i++];
    new_node->value = current;
    unsigned int bucket = ((unsigned int) current) % BUCKETS;
    if (buckets[bucket] != NULL) {
      node_t* search_node = buckets[bucket];
      while (1) {
        if (search_node->value == current) {
          printf("answer: %d\n", current);
          return 0;
        }
        if (search_node->next == NULL) break;
        search_node = search_node->next;
      }
      search_node->next = new_node;
    } else {
      buckets[bucket] = new_node;
    }
  }
  return 1;
}
