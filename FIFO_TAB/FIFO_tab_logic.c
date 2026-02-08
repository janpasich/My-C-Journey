#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifo_array.h"

static Student* queue_array = NULL;
static int queue_size = 0;

char* read_word_from_file(FILE* fp) {
    int size = 0; char* text = NULL; int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c != ' ' && c != '\n' && c != '\r' && c != '\t') break;
    }
    if (c == EOF) return NULL;

    text = (char*)malloc(1);
    if (!text) return NULL;

    text[0] = (char)c; size = 1;

    while ((c = fgetc(fp)) != EOF && c != ' ' && c != '\n' && c != '\r' && c != '\t') {
        size++;
        char* new_memory = (char*)realloc(text, size);
        if (!new_memory) { free(text); return NULL; }
        text = new_memory;
        text[size - 1] = (char)c;
    }

    char* final_memory = (char*)realloc(text, size + 1);
    if (final_memory) text = final_memory;
    text[size] = '\0';

    return text;
}

char* read_input(const char* message) {
    printf("%s", message);
    int size = 0; char* text = NULL; int c;
    while ((c = getchar()) != EOF) {
        if (c != '\n' && c != ' ' && c != '\r' && c != '\t') break;
    }
    if (c == EOF) return NULL;

    text = (char*)malloc(1);
    if (!text) return NULL;

    text[0] = (char)c; size = 1;

    while ((c = getchar()) != '\n' && c != EOF && c != '\r') {
        size++;
        char* new_memory = (char*)realloc(text, size);
        if (!new_memory) { free(text); return NULL; }
        text = new_memory;
        text[size - 1] = (char)c;
    }

    char* final_memory = (char*)realloc(text, size + 1);
    if (final_memory) text = final_memory;
    text[size] = '\0';

    return text;
}

void enqueue(Student s) {
    Student* temp = (Student*)realloc(queue_array, (queue_size + 1) * sizeof(Student));
    if (!temp) {
        printf("Memory allocation error!\n");
        return;
    }

    queue_array = temp;
    queue_array[queue_size] = s;
    queue_size++;
}

void load_from_file() {
    FILE* f = fopen("data.txt", "r");
    if (!f) {
        printf(">>> Info: 'data.txt' not found. Starting with empty queue.\n");
        return;
    }

    clear_queue();
    printf(">>> Loading data from file...\n");

    while (!feof(f)) {
        char* f_name = read_word_from_file(f);
        if (f_name == NULL) break;

        char* l_name = read_word_from_file(f);
        int b_year;

        if (fscanf(f, "%d", &b_year) != 1) {
            free(f_name);
            if (l_name) free(l_name);
            break;
        }

        Student s;
        s.first_name = f_name;
        s.last_name = l_name;
        s.birth_year = b_year;
        enqueue(s);
    }
    fclose(f);
    printf(">>> Data loaded (%d students).\n", queue_size);
}

void add_manually() {
    Student s;
    printf("Adding student:\n");
    s.first_name = read_input("First name: ");
    s.last_name = read_input("Last name: ");
    printf("Birth year: ");
    if (scanf("%d", &s.birth_year) != 1) {
        printf("Error reading year!\n");
        free(s.first_name); free(s.last_name);
        return;
    }

    enqueue(s);
    printf(">>> Added successfully.\n");
}

void dequeue() {
    if (queue_size == 0) { printf(">>> Queue is empty.\n"); return; }

    printf(">>> Retrieved: %s %s (%d)\n", queue_array[0].first_name, queue_array[0].last_name, queue_array[0].birth_year);

    free(queue_array[0].first_name);
    free(queue_array[0].last_name);

    for (int i = 0; i < queue_size - 1; i++) {
        queue_array[i] = queue_array[i + 1];
    }

    queue_size--;
    if (queue_size > 0) {
        Student* temp = (Student*)realloc(queue_array, queue_size * sizeof(Student));
        if (temp) queue_array = temp;
    }
    else {
        free(queue_array);
        queue_array = NULL;
    }
}

void clear_queue() {
    for (int i = 0; i < queue_size; i++) {
        free(queue_array[i].first_name);
        free(queue_array[i].last_name);
    }
    free(queue_array);
    queue_array = NULL;
    queue_size = 0;
    printf(">>> Memory cleared.\n");
}

void display_all() {
    if (queue_size == 0) { printf(">>> Empty.\n"); return; }
    printf("\n--- QUEUE (ARRAY) ---\n");
    for (int i = 0; i < queue_size; i++) {
        printf("[%d] %s %s (Born: %d)\n", i, queue_array[i].first_name, queue_array[i].last_name, queue_array[i].birth_year);
    }
}

void search_element() {
    int criteria;
    printf("\nSearch by: [1] First Name, [2] Last Name, [3] Birth Year: ");
    if (scanf("%d", &criteria) != 1) return;

    char* search_text = NULL;
    int search_year = 0;
    int found = 0;

    if (criteria == 1) search_text = read_input("Enter first name: ");
    else if (criteria == 2) search_text = read_input("Enter last name: ");
    else if (criteria == 3) { printf("Enter year: "); scanf("%d", &search_year); }
    else { printf("Invalid option.\n"); return; }

    printf("\n--- SEARCH RESULTS ---\n");
    for (int i = 0; i < queue_size; i++) {
        int match = 0;
        if (criteria == 1 && strcmp(queue_array[i].first_name, search_text) == 0) match = 1;
        else if (criteria == 2 && strcmp(queue_array[i].last_name, search_text) == 0) match = 1;
        else if (criteria == 3 && queue_array[i].birth_year == search_year) match = 1;

        if (match) {
            printf("[%d] %s %s, year: %d\n", i, queue_array[i].first_name, queue_array[i].last_name, queue_array[i].birth_year);
            found = 1;
        }
    }
    if (!found) printf(">>> No results found.\n");
    if (search_text) free(search_text);
}

void count_elements() {
    printf(">>> Number of elements: %d\n", queue_size);
}

void display_menu() {
    printf("\n--- QUEUE MENU (ARRAY) ---\n");
    printf("0. Load\n1. Add\n2. Get\n3. Search\n4. Display\n5. Count\n6. Clear\n7. Exit\nChoice: ");
}