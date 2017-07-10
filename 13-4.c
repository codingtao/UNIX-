#include "apue.h"
#include <syslog.h>
#include <errno.h>

extern int lockfile(int);
extern int already_running(void);

void reread(void)
{

}

void sigterm(int signo)
{
    syslog(LOG_INFO,"got SIGTERM; exiting");
    exit(0);
}

void 