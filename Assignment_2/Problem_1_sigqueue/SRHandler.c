#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <bits/types.h>
#define INTERVAL 2000
pid_t pidS1 =-1;
void alarmHandler();
int randomNum;
int main(int argc, char const *argv[])
{
    struct itimerval SRTimer;
    pidS1= atoi(argv[1]);
    signal(SIGALRM,alarmHandler);
    SRTimer.it_value.tv_sec= INTERVAL/1000;
    SRTimer.it_value.tv_usec=(INTERVAL*1000) % 1000000;
    SRTimer.it_interval = SRTimer.it_value;
    int a = setitimer(ITIMER_REAL,&SRTimer,NULL);
    while (1)
    {
        pause();
    }
    
    return 0;
}
void alarmHandler(){
    union sigval data;
    asm("RDRAND %rax");
    asm("mov %rax, randomNum");
    data.sival_int = randomNum;
    sigqueue(pidS1,SIGTERM,data);
}