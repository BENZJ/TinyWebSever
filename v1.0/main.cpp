#include "my.h"

int main (void){
    int listenfd,confd;
    struct stat sbuf;
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;
    char port[]="8880";
    //创建监听端口
    listenfd = Open_listenfd(port);
    while(1){
        clientlen = sizeof(clientaddr);
        //等待链接默认情况下无链接时会一直等待
        confd = accept(listenfd,(sockaddr*)&clientaddr,&clientlen);

        //运行到这里已经成功建立链接
        char buf[MAXLINE];
        //读取客户端的输入
        read(confd,buf,MAXLINE);
        //输出收到的http请求
        printf("%s",buf);
        char writebuf[MAXLINE];

        //写一个http报头
        char html[]="<html><head></head><body><h1>Hello World!</h1></body></html>";
        sprintf(writebuf, "HTTP/1.0 200 OK\r\n");    //line:netp:servestatic:beginserve
        sprintf(writebuf, "%sServer: Tiny Web Server\r\n", writebuf);
        sprintf(writebuf, "%sConnection: close\r\n", writebuf);
        sprintf(writebuf, "%sContent-length: %d\r\n", writebuf, (int)strlen(html));
        sprintf(writebuf, "%sContent-type: %s\r\n\r\n", writebuf, "text/html");

        //写入html文件
        sprintf(writebuf,"%s%s",writebuf,html);
        write(confd,writebuf,strlen(writebuf));


        //输出http响应
        printf("%s",writebuf);

        close(confd);


    }
    return 0;
}
