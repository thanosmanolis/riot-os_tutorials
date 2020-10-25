#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "thread.h"
#include "xtimer.h"

char stack[THREAD_STACKSIZE_MAIN];

void *thread_handler(void *arg)
{
    printf("Format: Hours:Minutes:Seconds:Milliseconds\n");
    
    while(1)
    {
        unsigned long long int timestamp;
        timestamp = xtimer_now_usec();
        
        long milliseconds   = (long) (timestamp / 1000) % 1000;
        long seconds    = (((long) (timestamp / 1000) - milliseconds)/1000)%60 ;
        long minutes    = (((((long) (timestamp / 1000) - milliseconds)/1000) - seconds)/60) %60;
        long hours      = ((((((long) (timestamp / 1000) - milliseconds)/1000) - seconds)/60) - minutes)/60;

        printf("Time: %ld:%ld:%ld:%ld\n", hours, minutes, seconds, milliseconds);
        xtimer_sleep(2);
    }

    (void)arg;
    return NULL;
}

int main(void)
{
    puts("This is Task-04");

    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST,
                  thread_handler, NULL,
                  "thread");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
