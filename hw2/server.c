#define BUFSIZE 256

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
int main(int argc, char** argv){
    int sock, client, clilen;
    struct sockaddr_in addr, cliaddr;
    char buf[BUFSIZE];
    ssize_t n;

    for(;;){
        //Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1){
            fprintf(stderr, "socket error\n");
            exit(1);
        }
        //Bind
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(8081);
        if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1){
            fprintf(stderr, "bind error\n");
            exit(1);
        }

        //Listen
        if(listen(sock, 10) == -1){
            fprintf(stderr, "listen error\n");
            exit(1);
        }
        //Accept
        if((client = accept(sock, (struct sockaddr*) &cliaddr, &clilen)) == -1){
            fprintf(stderr, "accept error\n");
            exit(1);
        } 
        //Read and dump data
        while((n = read(client, buf, BUFSIZE)) != -1){
            write(STDOUT_FILENO, buf, n);
            if(n < BUFSIZE)
                break;
        }
    }
}
