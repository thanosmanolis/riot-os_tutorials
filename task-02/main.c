#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "led.h"

//! Define delay values
#ifdef CLOCK_CORECLOCK
#define DELAY_SHORT         (CLOCK_CORECLOCK / 50)
#else
#define DELAY_SHORT         (500000UL)
#endif
#define DELAY_LONG          (DELAY_SHORT * 4)

//! Apply a delay of given time
void custom_delay(uint32_t delay)
{
    for (uint32_t i = 0; i < delay; i++) {
        __asm__("nop");
    }
}

//! Task 2.2 - toggle the primary LED
int toggle(int argc, char **argv)
{
    for(int i=0; i<10; i++)
    {
        LED0_TOGGLE;
        custom_delay(DELAY_LONG);
    }

    for(int i=0; i<100; i++)
    {
        LED0_TOGGLE;
        custom_delay(DELAY_SHORT);
    }

    for(int i=0; i<10; i++)
    {
        LED0_TOGGLE;
        custom_delay(DELAY_LONG);
    }

    return 0;
}

//! Turn on primary led
int ledon(int argc, char **argv)
{
    LED0_ON;
    custom_delay(DELAY_LONG);

    return 0;
}

//! Turn off primary led
int ledoff(int argc, char **argv)
{
    LED0_OFF;
    custom_delay(DELAY_LONG);

    return 0;
}

int echo(int argc, char **argv)
{
    //! Task 2.1 - Print all the arguments
    for(int i=1; i<argc; i++)
    	printf("%s ", argv[i]);
    printf("\n");

    return 0;
}

static const shell_command_t commands[] = {
    { "echo", "Prints arguments given", echo },
    { "toggle", "Toggles the primary LED", toggle },
    { "ledon", "Turns on the primary LED", ledon },
    { "ledoff", "Turns off the primary LED", ledoff },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("This is Task-02");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
