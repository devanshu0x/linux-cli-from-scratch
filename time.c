#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    if(argc<2){
        fprintf(stderr,"Usage ./time command\n");
        return 1;
    }
    struct timeval start,end;
    struct rusage usage;

    //storing start time
    gettimeofday(&start,NULL);

    // Fork a child process to execute the command
    pid_t pid=fork();
    if(pid<0){
        fprintf(stderr,"fork() error\n");
        return 1;
    }
    // pid==0 in child process  else in parent process
    if(pid==0){
        // executing the command in child process
        execvp(argv[1],&argv[1]);

        // if no error occour in execvp control will never reach here and child process will end
        fprintf(stderr,"execvp() error\n");
        return 1;
    }
    else{
        //in parent process waiting for child process to finish
        int status;
        waitpid(pid,&status,0);

        //get end time 
        gettimeofday(&end,NULL);

        // get resources usage
        getrusage(RUSAGE_CHILDREN,&usage);

        // calculate real time
        double real_time= (end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec)/1e6;

        // user time
        double user_time= usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1e6;

        // system time
        double system_time =usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1e6;

        // Printing the result
        printf("Real time: %0.7f sec\n",real_time);
        printf("User time: %0.7f sec\n",user_time);
        printf("System time: %0.7f sec\n",system_time);

    }

    return 0;
}
