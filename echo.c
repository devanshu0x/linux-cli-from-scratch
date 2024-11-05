#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(argc<2){
        fprintf(stderr,"Usage ./echo arg1 arg2(optional) arg3(optional) ...\n");
        return 1;
    }
    else{
        for(int i=1;i<argc;i++){
            printf("%s",argv[i]);
            if(i<argc-1){
                putchar(' ');
            }
        }
        putchar('\n');
    }
    return 0;
}
