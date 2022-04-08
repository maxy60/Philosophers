#include <sys/time.h>
#include <stdio.h>

int main()
{
    int i = 0;;
    long int time_ms;
    struct timeval time;
    
    gettimeofday(&time, NULL);
    time_ms = ((time.tv_sec *1000) + (time.tv_usec / 1000));
    while (i < 3)
    {
        sleep(2);
        printf("time u_sec: %ld\n", ((time.tv_sec *1000) + (time.tv_usec / 1000)) - time_ms);
        i++;
    }
}