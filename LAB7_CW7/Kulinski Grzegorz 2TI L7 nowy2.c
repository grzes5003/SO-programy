#include <stdio.h>
#include <unistd.h>

int main()
{
    /* program czeka 30 sekund po czym zwraca 30 */
    printf("nowy2: sleep(30)\n");
    sleep(30);
    printf("nowy2: zakonczono sleep(30)\n");
    return 30;
}
