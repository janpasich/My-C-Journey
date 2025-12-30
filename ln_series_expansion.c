#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double calculate_series(double x, double eps, int max_iter, int* term_count, int* stop_reason);

int main(void)
{
    double x = 0.0, eps = 0.0, a = 0.0, b = 0.0;
    int max_iter = 0, term_count = 0, stop_reason = 0, n_intervals = 0;


    FILE* output_file = fopen("results.txt", "wt");
    if (output_file == NULL)
    {
        printf("Error: Cannot open file for writing!\n");
        return 1;
    }

    while (1) {
        printf("Enter precision (eps): ");
        if (scanf("%lf", &eps) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (eps <= 0) {
            printf("Error: eps must be positive!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter max iterations (M): ");
        if (scanf("%d", &max_iter) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (max_iter <= 0) {
            printf("Error: M must be greater than zero!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter start of interval (a): ");
        if (scanf("%lf", &a) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (a <= 0.5) {
            printf("Error: a must be > 0.5 because of ln(x) convergence domain!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter end of interval (b): ");
        if (scanf("%lf", &b) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (b <= a) {
            printf("Error: b must be greater than a!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter number of intervals (n): ");
        if (scanf("%d", &n_intervals) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (n_intervals <= 0) {
            printf("Error: n must be greater than zero!\n");
            continue;
        }
        break;
    }

    fprintf(output_file, "x\tln(x)_exact\tln(x)_series\tterms\treason\n");
    fprintf(output_file, "-------------------------------------------------------\n");

    printf("\nComputing...\n");

    double step_size = (b - a) / n_intervals;


    for (int i = 0; i <= n_intervals; i++)
    {
        double current_x = a + i * step_size;

        term_count = 0;
        stop_reason = 0;

        double y_exact = log(current_x);
        double y_series = calculate_series(current_x, eps, max_iter, &term_count, &stop_reason);


        printf("x = %.4lf | Series = %.6lf | Exact = %.6lf | Terms = %d | Stop Code = %d\n",
            current_x, y_series, y_exact, term_count, stop_reason);


        fprintf(output_file, "%.4lf\t%.6lf\t%.6lf\t%d\t%d\n",
            current_x, y_exact, y_series, term_count, stop_reason);
    }

    fclose(output_file);
    printf("\nResults saved to 'results.txt'.\n");

    return 0;
}


double calculate_series(double x, double eps, int max_iter, int* term_count, int* stop_reason)
{
    double sum = 0.0;
    double current_term = 0.0;
    int k = 0;

    *term_count = 0;
    *stop_reason = 0;

    if (x <= 0.5)
    {
        *stop_reason = 4;
        return 0.0;
    }

    double r = (x - 1.0) / x;
    double numerator = r;

    for (k = 1; k <= max_iter; k++)
    {
        current_term = numerator / k;
        sum += current_term;
        (*term_count)++;

        if (fabs(current_term) < eps)
            break;

        numerator *= r;
    }

    int is_precision_reached = (fabs(current_term) < eps);
    int is_limit_reached = (k > max_iter);

    if (is_precision_reached)
    {
        *stop_reason = 1;
    }
    else if (is_limit_reached)
    {
        *stop_reason = 2;
    }
    else
    {
        *stop_reason = 0;
    }

    return sum;
}