/*
 *  Program z Lab07_cw07
 *
 *  Tworzy dwa potomne procesy, podmienia ich kod,
 *  nastepnie czeka na ich zakonczenia i wypisuje podstawowe
 *  informacje na temat tych procesow
 *
 *  W celu uruchomienia nalezy wczesniej w tym samym katalogu
 *  posiadac skompilowane programy nowy1.c, nowy2.c
 *  pod nazwami nowy1 i nowy2
 *  LUB
 *  w argumentach podac nazwy plikow
 *
 *  PRZYKLAD
 *  $ ./fkexe ./plik1 ./plik2
 *  Aby fkexe podmienil kod na podane podczas wykonywania
 *
 *
 * */

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int kod_rodzica(){
    /* Kod wykonywany tylko przez rodzica
    * kod wykonywany jest dwa razy, poniewaz sa dwa procesy potomne */

    int stat;

    for (int i = 0; i < 2; i++) {
        int pid = wait(&stat);        // pod stat zwracam status zakonczenia programu, i zwracam PID
        /* liczba stat na starszym bajcie zawiera kod zakonczenia, a na mlodszym sygnal ktory zakonczyl proces */
        int sig_num = stat % 256;        // obliczam numer sygnalu ktory zakonczyl proces
        int kod = (stat - sig_num) / 256;    // obliczam kod zakonczenia programu

        /* drukuje informacje na temat zakonczonego procesu-dziecka */
        printf("Zakonczony proces potomny: PID %d, Kod zakonczenia %d, Numer sygnalu %d\n", pid, kod, sig_num);
    }

    return 0;
}

int main(int argc, char *argv[]) {

    char *program1 = "./nowy1";
    char *program2 = "./nowy2";

    if(argc == 3){
        program1 = argv[1];
        program2 = argv[2];
    }

    int nowy1_status, nowy2_status;

    nowy1_status = fork(); // rozgaleziam proces pierwszy raz

    if( nowy1_status != 0){ /* jesli proces nie jest dzieckiem nowy1 */

        nowy2_status = fork(); // rozgaleziam proces drugi raz

        if ( nowy2_status != 0 ) { /* jesli proces nie jest dzieckiem nowy2 */
            /* koncze caly program z takim kodem jak kod rodzica */
            return kod_rodzica();
        }

        char *args2[]={program2, NULL};	//po rozgalezieniu w programie nastapi zamiana swojego kodu na kod programu nowy2
        execvp(args2[0],args2);
    }
    char *args1[]={program1, NULL};    	//po rozgalezieniu w programie nastapi zamiana swojego kodu na kod programu nowy1
    execvp(args1[0],args1);
}
