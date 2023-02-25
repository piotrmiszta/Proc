#include <stdio.h>
#include <unistd.h>     /* for usleep */
#include <ctype.h>
#include <limits.h>
#include "Logger.h"
#include "dirent.h"
#include "TermDefines.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "ProcStat.h"
void this_function_read_processes_and_owners() { //TODO cos z tym zrobic
    char* fullpath;
    struct dirent* dp;
    const char* path = "/proc";
    DIR *dir = opendir(path);
    char temp[255];
    int i = 0;

    struct stat sb;
    char outstr[200];


    while(dp= readdir(dir)) {
        if(isdigit(dp->d_name[0])) {
            P_DARK_CYAN;
            printf("%s\t", dp->d_name);
            P_RESET;
            P_BLUE;
            char proc []= "/proc/";
            strcat(proc, dp->d_name);
            stat(proc, &sb);
            struct passwd *pw = getpwuid(sb.st_uid);
            struct group  *gr = getgrgid(sb.st_gid);
            if(pw != NULL && gr != NULL)
                printf("%s\t\t\t\t %s\n", pw->pw_name, gr->gr_name);
            P_RESET;
        }
    }
}


int main() {
    logger_init("test.txt");
    ProcStat* proc = procStat_create(1695);
    procStat_write(proc, stdout);
    printf("\n");
    printf("%f", procStat_percent(proc));
    logger_close();
}

