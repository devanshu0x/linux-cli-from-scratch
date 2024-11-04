#include<stdio.h>

void print_file(const char * filename){
    FILE * f= fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"Cannot read file or file doesn't exist\n");
    }
    else{
        char ch;
        ch=getc(f);
        while(ch!=EOF){
            putchar(ch);
            ch=getc(f);
        }
        fclose(f);
    }
    
}

int main(int argc, char const *argv[])
{
    if(argc<2){
        // Reading from stdin
        char ch;
        ch=getc(stdin);
        while(ch!=EOF){
            putchar(ch);
            ch=getc(stdin);
        }
    }
    else{
        // Reading from file(s)
        for(int i=1;i<argc;i++){
            print_file(argv[i]);
        }
    }
    return 0;
}
