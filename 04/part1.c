#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER 100
#define EVENT_COUNT 2000
#define GUARD_COUNT 30
#define DURATION_COUNT 50
#define MINUTES 60

typedef enum {
  begin_shift,
  wake_up,
  fall_asleep,
} event_type;

typedef struct {
  int month;
  int day;
  int hour;
  int minute;
} etime_t;

typedef struct {
  event_type type;
  etime_t time;
  int guard_id;
} event_t;

typedef struct {
  int length;
  etime_t start;
  etime_t end;
} duration_t;

typedef struct {
  int id;
  int total_time_asleep;
  int minute_grouping[MINUTES];
  int durations_i;
  duration_t durations[DURATION_COUNT];
} guard_t;

// Smaller inputs are always easier to debug. Start simple.
void events_swap(event_t* events, int i, int j) {
  event_t temp = events[i];
  events[i] = events[j];
  events[j] = temp;
}

int events_compare(event_t* event1, event_t* event2) {
  if (event1->time.month > event2->time.month) return 1;
  if (event1->time.month < event2->time.month) return -1;
  if (event1->time.day > event2->time.day) return 1;
  if (event1->time.day < event2->time.day) return -1;
  if (event1->time.hour > event2->time.hour) return 1;
  if (event1->time.hour < event2->time.hour) return -1;
  if (event1->time.minute > event2->time.minute) return 1;
  if (event1->time.minute < event2->time.minute) return -1;
  return 0;
}

int events_partition(event_t* events, int l, int r) {
  event_t pivot = events[l];
  int tl = l, tr = r;
  tl += 1;
  while (tl <= tr) {
    if (events_compare(&events[tl], &pivot) == 1) {
      events_swap(events, tl, tr);
      tr -= 1;
    } else {
      tl += 1;
    }
  }
  events_swap(events, l, tl - 1);
  return tl - 1;
}

void events_sort(event_t* events, int l, int r) {
  if (l < r) {
    int p = events_partition(events, l, r);
    events_sort(events, l, p - 1);
    events_sort(events, p + 1, r);
  }
}

guard_t* guards_find(guard_t* guards, int guards_i, int id) {
  for (int i = 0; i < guards_i; i++) {
    if (guards[i].id == id) {
      return &guards[i];
    }
  }
  return NULL;
}

int main(int argc, char** argv) {
  FILE* file = fopen(argv[1], "r");
  char line_buffer[LINE_BUFFER];
  event_t events[EVENT_COUNT] = { { 0 } };
  int events_i = 0;
  guard_t guards[GUARD_COUNT] = { { 0 } };
  int guards_i = 0;
  while (fgets(line_buffer, LINE_BUFFER, file) != NULL) {
    event_t* event = &events[events_i++];
    char event_type_string[10];
    char guard_id_string[10];
    sscanf(
      line_buffer,
      "[%*d-%d-%d %d:%d] %10s %10s",
      &event->time.month,
      &event->time.day,
      &event->time.hour,
      &event->time.minute,
      event_type_string,
      guard_id_string
    );
    if (strcmp(event_type_string, "Guard") == 0) {
      event->type = begin_shift;
      sscanf(guard_id_string, "#%d", &event->guard_id);
    } else if (strcmp(event_type_string, "wakes") == 0) {
      event->type = wake_up;
    } else {
      event->type = fall_asleep;
    }
  }
  events_sort(events, 0, events_i - 1);
  guard_t* current_guard = NULL;
  for (int i = 0; i < events_i; i++) {
    event_t event = events[i];
    // printf("%d,%d,%d\n", event.time.month, event.time.day, event.time.minute);
    if (event.type == begin_shift) {
      current_guard = guards_find(guards, guards_i, event.guard_id);
      if (current_guard == NULL) {
        current_guard = guards + guards_i;
        current_guard->id = event.guard_id;
        guards_i += 1;
      }
    } else if (event.type == fall_asleep) {
      duration_t* duration = current_guard->durations + current_guard->durations_i;
      duration->start = event.time;
    } else if (event.type == wake_up) {
      duration_t* duration = current_guard->durations + current_guard->durations_i;
      duration->end = event.time;
      duration->length = duration->end.minute - duration->start.minute;
      current_guard->total_time_asleep += duration->length;
      for (int i = duration->start.minute; i < duration->end.minute; i++) {
        current_guard->minute_grouping[i] += 1;
      }
      current_guard->durations_i += 1;
    }
  }

  // Solve part 1
  guard_t* max_guard1 = NULL;
  for (int i = 0; i < guards_i; i++) {
    guard_t* guard = guards + i;
    if (max_guard1 == NULL \
        || guard->total_time_asleep > max_guard1->total_time_asleep) {
      max_guard1 = guard;
    }
  }
  int max_minute1 = 0;
  for (int i = 0; i < MINUTES; i++) {
    if (max_guard1->minute_grouping[i] > max_guard1->minute_grouping[max_minute1]) {
      max_minute1 = i;
    }
  }

  // Solve part 2
  guard_t* max_guard2 = NULL;
  int max_guard2_freq = 0;
  int max_guard2_min = 0;
  for (int i = 0; i < MINUTES; i++) {
    int max_freq = 0;
    int max_min = 0;
    guard_t* max_guard2_temp = NULL;
    for (int j = 0; j < guards_i; j++) {
      guard_t* guard = guards + j;
      if (guard->minute_grouping[i] > max_freq) {
        max_freq = guard->minute_grouping[i];
        max_guard2_temp = guard;
        max_min = i;
      }
    }
    if (max_freq > max_guard2_freq) {
      max_guard2_freq = max_freq;
      max_guard2 = max_guard2_temp;
      max_guard2_min = max_min;
    }
  }

  printf("part1 answer: %d\n", max_minute1 * max_guard1->id);
  printf("part2 answer: %d\n", max_guard2_min * max_guard2->id);
  return 0;
}
