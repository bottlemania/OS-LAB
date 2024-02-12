#include <stdio.h>
#include <stdbool.h>

int allocation[10][10];
int max[10][10];
int available[10];
bool finish[10];
int need[10][10];
int p, r;

void init()
{
    int i;
    for (i = 0; i < p; i++)
        finish[i] = false;
}
int exists()
{
    int index = -1;
    int i;
    for (i = 0; i < p; i++)
    {
        if (!finish[i])
        {
            index = i;
            int j;
            for (j = 0; j < r; j++)
            {
                if (need[i][j] > available[j])
                {
                    index = -1;
                    break;
                }
            }
            if (index != -1)
                return index;
        }
    }

    return index;
}

int main()
{

    printf("Enter no.of processes and resources... \n");
    scanf("%d %d", &p, &r);

    int i;
    init();

    printf("Enter allocation..\n");
    for (i = 0; i < p; i++)
    {
        int j;
        for (j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Maximum..\n");
    for (i = 0; i < p; i++)
    {
        int j;
        for (j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter Available..\n");

    int j;
    for (j = 0; j < r; j++)
    {
        scanf("%d", &available[j]);
    }

    for (i = 0; i < p; i++)
    {
        int j;
        for (j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int round = 1;
    while (round <= p)
    {
        int k = exists();
        if (k != -1)
        {
            for (i = 0; i < r; i++)
            {
                available[i] += allocation[k][i];
                // printf("%d",available[i]);
            }
            // printf("\n");
            finish[k] = true;
            printf(" P%d \t", k);
        }
        int completed = 0;
        for (i = 0; i < p; i++)
            if (finish[i])
                completed++;
        if (completed == p)
        {
            printf("Safety condition acheived\n");
            return;
        }
        round++;
    }
    printf("Dead lock\n");
}
