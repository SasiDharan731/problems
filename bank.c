#include <stdio.h>
#include <stdlib.h>

int available[10], maximum[10][10], allocation[10][10], need[10][10], safe[10];
int n, m;

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources needed by each process: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocated resources for each process: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // implementation of banker's algorithm
    int work[10];
    int finish[10] = {0};
    int index = 0;

    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }
                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safe[index++] = i;
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0)
        {
            printf("System is in unsafe state. No safe sequence exists.\n");
            return 0;
        }
    }

    printf("System is in safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", safe[i]);
    }
    printf("\n");

    return 0;
}
