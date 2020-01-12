/*
 *  Program z Lab06_cw05
 *
 *  Wyswietla na podstawie podanych argumentow wejsciowych
 *  wartosci zadanych zmiennych srodowiskowych
 *
 *  przyklad uzycia:
 *  $ ./'Kulinski Grzegorz 2TI L6 zmienne.o' HOST
 *  wynik:
 *  PATH=/usr/share/Modules/bin:/usr/local/bin:/usr/bin
 *
 * */

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>


int main(int argc, char *argv[], char *envp[]){  /* funkcja main ze standardowymi argumentami wejsiowymi */

    /* nie podano argumentow funkcji
     * wypisze wszystkie zmienne srodowiskowe */
    if(argc == 1){
        while(*envp){
            printf("%s\n",*envp);
            envp++;
        }
        return 0; // program konczy dzialanie po wyswietleniu wszystkich zmiennych
    }
    else{
        printf("Argumenty wejsciowe: ");
        for(int i = 1; i < argc; i++){
            printf(" %s ", argv[i]);
        }
        printf("\n");
    }

    printf("---- Poszukiwane wartosci -----\n");

    /* podano argumenty na wejsciu
     * rozpoczyna sie ich wypisywanie */
    for(int i=1;i<argc;i++){
        /* Jesli zmienna x istnieje: wypisz ja;
         * else: nie znaleziono zmiennej x */
        if(getenv(argv[i])!=NULL){
            printf("%s=%s\n",argv[i],getenv(argv[i]));
        }
        else{
            printf("Nie znaleziono zmiennej: %s \n",argv[i]);
        }
    }

    // program konczy dzialanie bez bledow
    return 0;
}
