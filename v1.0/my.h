//
// Created by benz on 7/18/17.
//

#ifndef UNTITLED1_MY_H_H
#define UNTITLED1_MY_H_H

#endif //UNTITLED1_MY_H_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>//close() function
#define LISTENQ  1024
#define MAXLINE 1024
#define MAXBUF 1024
int open_listenfd(char *port){
    struct addrinfo hints,*listp,*p;
    int listenfd,rc,optval = 1;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;

    getaddrinfo(NULL,port,&hints,&listp);

    for (p = listp; p ; p = p->ai_next){
        if((listenfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
            continue;
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeof(int));

        if(bind(listenfd,p->ai_addr,p->ai_addrlen)==0)
            break;//success

        if(close(listenfd)<0) {
            fprintf(stderr, "open_listenfd close failed: %s\n", strerror(errno));
            return -1;
        }
    }

    freeaddrinfo(listp);

    if(listen(listenfd,LISTENQ)<0){
        close(listenfd);
        return -1;
    }
    return listenfd;
}

int Open_listenfd(char *port){
    int rc;
    if((rc = open_listenfd(port))<0)
        printf("Open_listenfd error");
    return rc;
}

