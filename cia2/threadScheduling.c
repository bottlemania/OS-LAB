#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

pthread_t pri;
pthread_t palin;
pthread_t arm;
pthread_t perfect;

void *prime_or_composite(void *n1)
{
    int n = *(int *)n1;
    printf("**********Operation Prime or Composite********\n");
    printf(" Thread id is : %ld\n", (long)pri);
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            printf(" %d Number is Composite\n", n);
            return 0;
        }
    }
    printf(" %d Number is Prime number\n", n);
}


void *palindrome(void *n1)
{
    int n = *(int *)n1;
    printf("**********Operation Palindrome********\n");
    printf(" Thread id is : %ld\n", (long)palin);
    int original, reversed = 0, remainder;
    original = n;
    while (n != 0)
    {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    if (original == reversed)
    {
        printf(" %d is Palindrome\n", original);
    }
    else
    {
        printf(" %d is Not Palindrome\n", original);
    }
}


void *armstrong(void *n1)
{
    int n = *(int *)n1;
    printf("**********Operation Armstong ********\n");
    printf(" Thread id is : %ld\n", (long)arm);
    int r, sum = 0;
    int original = n;
    while (n > 0)
    {
        r = n % 10;
        sum += r * r * r;
        n /= 10;
    }
    if (original == sum)
    {
        printf(" %d is Armstong\n", original);
    }
    else
    {
        printf(" %d is Not Armstrong\n", original);
    }
}


void *perfectno(void *n1)
{
    int n = *(int *)n1;
    int sum = 0;
    printf("**********Operation Perfect Number ********\n");
    printf(" Thread id is : %ld\n", (long)perfect);
    for (int i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    if (n == sum)
        printf(" %d is Perfect number\n", n);
    else
        printf(" %d is Not a Perfect Number\n", n);
}


int main()
{
    int n;
    printf("Enter the number to check all operations\n");
    scanf("%d", &n);
    pthread_create(&pri, NULL, prime_or_composite, &n);
    pthread_join(pri, NULL);

    pthread_create(&palin, NULL, palindrome, &n);
    pthread_join(palin, NULL);

    pthread_create(&arm, NULL, armstrong, &n);
    pthread_join(arm, NULL);

    pthread_create(&perfect, NULL, perfectno, &n);
    pthread_join(perfect, NULL);

    exit(0);
}