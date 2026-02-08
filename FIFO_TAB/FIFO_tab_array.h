#ifndef FIFO_ARRAY_H
#define FIFO_ARRAY_H

#include <stdio.h>

typedef enum {
    OPTION_LOAD = 0,
    OPTION_ADD,
    OPTION_GET,
    OPTION_SEARCH,
    OPTION_DISPLAY,
    OPTION_COUNT,
    OPTION_CLEAR,
    OPTION_EXIT,
    NUM_OPTIONS
} MenuOption;

typedef struct {
    char* first_name;
    char* last_name;
    int birth_year;
} Student;

void load_from_file();
void add_manually();
void enqueue(Student s);
void dequeue();
void clear_queue();
void display_all();
void search_element();
void count_elements();
void display_menu();

#endif