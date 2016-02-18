#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<time.h>
int main(int argc, char** argv){
    void sendData(char*, const char*);
    void vuln(char*);
    const char *ip = "127.0.0.1";

    if(argc < 2){
        printf("usage: ./vuln <input>\n");
        exit(1);
    }
    sendData(argv[1], ip);
    vuln(argv[1]);
    exit(0);
}

void sendData(char* s, const char* ip){
    int i, len;
    char buf[64];
    int sock;
    struct sockaddr_in addr;
    time_t t;
    time(&t);
    len = strlen(s);


    addr.sin_family = AF_INET;
    addr.sin_port = htons(8081);

    if(inet_pton(AF_INET, ip, &addr.sin_addr) <= 0){
        fprintf(stderr, "inet_pton error\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        fprintf(stderr, "socket error\n");
        exit(1);
    }
    if(connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        fprintf(stderr, "connect error\n");
        exit(1);
    }
    sprintf(buf, "%s", ctime(&t));
    write(sock, buf, strlen(buf));
    write(sock, "raw:\n\t", 6);
    for(i=0; i<len; i++)
        write(sock, &s[i], 1);
    write(sock, "\n", 1);
    write(sock, "bytes:\n\t", 8);
    for(i=0; i<len; i++){
        sprintf(buf, "%x ", s[i]);
        write(sock, buf, 3);
    }
    write(sock, "\n", 1);
    close(sock);
}

void vuln(char* c){
    char buf[2];
    strcpy(buf, c);
}
