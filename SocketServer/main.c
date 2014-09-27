//
//  main.c
//  SocketServer
//
//  Created by happytree2 on 14-9-27.
//  Copyright (c) 2014年 yellowpomelo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4096

int main(int argc, const char * argv[])
{

    int listenfd, connfd;
    struct sockaddr_in serveraddr;
    char buff[4096];
    int n;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(6666);
    
    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    
    if (listen(listenfd, 10) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    
    printf("====== waiting for client's request ======\n");
    while(1){
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if (connfd == -1) {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        n = (int)recv(connfd, buff, (int)MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
//        close(connfd);
        shutdown(connfd, SHUT_RDWR);
    }
    
//    close(listenfd);
    shutdown(listenfd, SHUT_RDWR);
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

