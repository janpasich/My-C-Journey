#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include "fifo_array.h" 

int main() {
    setlocale(LC_ALL, "C");

    load_from_file();

    int choice = -1;
    while (choice != OPTION_EXIT) {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case OPTION_LOAD:    load_from_file(); break;
        case OPTION_ADD:     add_manually(); break;
        case OPTION_GET:     get_element(); break; 
        case OPTION_SEARCH:  search_element(); break;
        case OPTION_DISPLAY: display_all(); break;
        case OPTION_COUNT:   count_elements(); break;
        case OPTION_CLEAR:   clear_all(); break;
        case OPTION_EXIT:
            clear_all();
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}