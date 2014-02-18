#include <sys/types.h>
#include <stdio.h>

main()
{

    pid_t pid  = getpid();
    pid_t ppid = getppid();
    pid_t pgrp = getpgrp();
    pid_t pgid = getpgid( pid );


    uid_t uid  = getuid();
    uid_t euid = geteuid();
    gid_t gid  = getgid();
    gid_t egid = getegid();


    printf("PID = %d\t PPID = %d\t PGRP = %d\t PGID = %d\n", pid, ppid, pgrp, pgid);
    printf("UID = %d\t EUID = %d\t GID = %d\t EGID = %d\n", uid, euid, gid, egid);
    


}
