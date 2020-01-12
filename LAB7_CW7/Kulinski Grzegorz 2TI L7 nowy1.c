#include <stdio.h>
#include <unistd.h>

int main()
{
    /* program czeka 20 sekund po czym zwraca 20 */
    printf("nowy1: sleep(20)\n");
    sleep(20);
    printf("nowy1: zakonczono sleep(20)\n");
    return 20;
}
