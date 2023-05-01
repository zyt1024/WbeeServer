#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
#include "locker.h"
#include "webserver.h"

#define MAX_FD 65536 // 最大的文件描述符个数
#define MAX_EVENT_NUMBER 10000 // 监听的最大的事件数量
/*
    要处理的数据准备好，在主线程中检测到可以写的时候，再写进去
*/
extern void addfd( int epollfd, int fd, bool one_shot, int tri_modle);
extern void removefd( int epollfd, int fd);
extern void modfd(int epollfd, int fd, int ev, int tri_mode);// ev为event的值


// 添加信号捕捉
void addsig(int sig, void(handler)(int)){
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) ); // 将这一空间置为0;
    sa.sa_handler = handler;
    sigfillset( &sa.sa_mask );
    // assert( sigaction( sig, &sa, NULL ) != -1 );
}

int main(int argc, char* argv[]){

    if(argc <= 1 ) {
        printf("usage: %s port_number\n",basename(argv[0]));
        return 1;
    }

    //从参数中获取端口
    int port = atoi( argv[1] );
    int close_log = 0; // 打开日志
    int log_write = 1; // 写入日志

    WebServer server;

    //初始化
    server.init(port, close_log, log_write);

    //日志 写入日志
    server.log_write();

    server.trig_mode();
    
    //线程池
    server.thread_pool();

    //监听
    server.eventListen();

    // 运行
    server.eventLoop();

    return 0;
}