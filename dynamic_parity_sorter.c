#pragma warning(disable:4996) // Disables scanf warnings in Visual Studio
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;
    int* input_array;

    printf("How many numbers do you want to enter?\n");
    if (scanf("%d", &size) != 1) return 1; 

    input_array = (int*)malloc(size * sizeof(int));

    if (input_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the numbers:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &input_array[i]);
    }

    int even_count = 0;
    int odd_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (input_array[i] % 2 == 0) even_count++;
        else odd_count++;
    }

    int* even_numbers;
    int* odd_numbers;

    even_numbers = (int*)malloc(even_count * sizeof(int));
    odd_numbers = (int*)malloc(odd_count * sizeof(int));

    if (even_numbers == NULL || odd_numbers == NULL) {
        printf("Memory allocation failed!\n");
        free(input_array); 
        if (even_numbers != NULL) free(even_numbers);
        if (odd_numbers != NULL) free(odd_numbers);
        return 1;
    }

    int even_pos = 0;
    int odd_pos = 0;

    for (int i = 0; i < size; i++)
    {
        if (input_array[i] % 2 == 0)
        {
            *(even_numbers + even_pos) = *(input_array + i);
            even_pos++;
        }
        else
        {
            *(odd_numbers + odd_pos) = *(input_array + i);
            odd_pos++;
        }
    }

    printf("\nEven numbers:\n");
    for (int i = 0; i < even_count; i++)
    {
        printf("%d ", *(even_numbers + i));
    }
    printf("\n");

    printf("Odd numbers:\n");
    for (int i = 0; i < odd_count; i++)
    {
        printf("%d ", *(odd_numbers + i));
    }
    printf("\n");

    free(input_array);
    free(even_numbers);
    free(odd_numbers);

    return 0;
}