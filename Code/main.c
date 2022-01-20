#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lab1_IO.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    double start, end;
    GET_TIME(start);
    printf("hello\n");
    GET_TIME(end);
    sleep(2);
    printf("%.2f\n", start - end);
}