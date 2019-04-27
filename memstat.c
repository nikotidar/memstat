/*
 * display memory statistic
 * copyright (c) 2019 - rndtx
 */

#include <unistd.h>
#include <stdio.h>

int memstat_print(int mod, char suffix) {
    int padding = 8;
    long pages = sysconf(_SC_PHYS_PAGES);
    long pagesiz = sysconf(_SC_PAGE_SIZE);
    long avpages = sysconf(_SC_AVPHYS_PAGES);

    if (!pages || !avpages || !pages)
        return 1;

    puts("\ttotal\tused\tfree");
    printf("mem:\t%ld%c\t%ld%c\t%ld%c\n",
            pages * pagesiz >> mod, suffix,
            (pages - avpages) * pagesiz >> mod, suffix,
            avpages * pagesiz >> mod, suffix);

    return 0;
}

int main(int argc, const char **argv) {
    int suffix = 'M', mod = 20;

    if (argc >= 2 && argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'm': mod = 20; suffix='M'; break;
            case 'k': mod = 10; suffix='k'; break;
            case 'g': mod = 30; suffix='G'; break;
        }
    }

    return memstat_print(mod, suffix);
}
