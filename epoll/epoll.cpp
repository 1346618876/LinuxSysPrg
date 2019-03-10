#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define MAX_EVEN_SIZE 5

int main()
{
    // int epfd;
    // epfd = epoll_create(1);

    // if (epfd == -1)
    // {
    //     perror("epoll_create");
    // }
    // int ret;

    struct epoll_event *events;
    struct epoll_event event;
    int ret;
//  int listenfd;

    int nr_events, i, epfd;
    events = (epoll_event *)malloc(sizeof(epoll_event) * MAX_EVEN_SIZE);
    if(events = 0)
    {
        perror("aaa");
        return 1;
    }
    printf("success3\n");
    epfd = epoll_create(MAX_EVEN_SIZE); ////创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大 
    if (epfd < 0)
    perror ("epoll_create");
        printf("success2\n");

    //listenfd = socket(AF_INET,SOCK_DGRAM,0);    //创建套接字
    // 	if(sockfd < 0)
	// {
	// 	perror("socket");
	// 	exit(-1);
	// }

    event.data.fd = 0; /* return the fd to us later*/
    event.events = EPOLLIN;
    ret = epoll_ctl (epfd, EPOLL_CTL_ADD, event.data.fd, &event);  //把fd指定的文件添加到epfd指定的epoll实例监听集中，监听event中定义的事件
    if (ret)
        perror ("epoll_ctl");
    while(1){
        nr_events = epoll_wait (epfd, events, MAX_EVEN_SIZE,-1);   //等待epoll实例epfd中的文件fd上的事件，时限为最后一个参数的毫秒数,且最多可以有第三参数个事件
        if (nr_events < 0) {
            perror ("epoll_wait");
            free (events);
            return 1;
        }
    }

    printf("epoll_wait success\n");
    for (i = 0; i < nr_events; i++) {
        printf ("event=%d on fd=%d\n",events[i].events, events[i].data.fd);
    }
    free (events);
    return 0;

}