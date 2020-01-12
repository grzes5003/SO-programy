#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    int pipefd[2], pid;

    /* Argumenty z jakimi wywolam cat oraz sort */
    const char *cat_arg[] = {"cat", "/etc/passwd", NULL};
    const char *sort_arg[] = {"sort", NULL};

    /* Tworze nowego pipe'a, gdzie pipefd[0] bedzie do czytania
     * pipefd[1] bedzie zapisywania */
    if (pipe(pipefd) < 0) {
        perror("Blad podczas pipe()");
        return 1;
    }

    /* Rozdzielam proces */
    pid = fork();
    if (pid == -1) {
        perror("Blad podczas fork()");
        return 1;
    }

    if (pid == 0) {
        /* Potomek odpowiada za wykonanie cat z wynikiem dzialania rodzica */

        dup2(pipefd[1], 0);
        close(pipefd[0]); // zamykam niepotrzebna czesc pipe'a
        execvp("cat", (char *const *) cat_arg); // wywoluje cat z argumentami cat_arg
    } else {
        /* Rodzic odpowiada za wykonanie sort /args/ */

        dup2(pipefd[0], 0);
        close(pipefd[1]); // zamykam niepotrzebna czesc pipe'a
        wait(NULL); // czakam az potomek zakonczy dzialanie
        execvp("sort", (char *const *) sort_arg); // wywoluje sort z argumentami sort_arg
    }
    /* Koncze dzialanie zwracajac 0 */
    return 0;
}

