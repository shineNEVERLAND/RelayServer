#include"global.h"


int nAddAllAgentToEpoll( int epollFd ){
	int i;
	for( i = 0; i < CLI_NUM; i++ ){
		struct epoll_event ev;
		ev.data.ptr = g_EpollPtr[i];
		ev.events = EPOLLIN|EPOLLOUT;
		
		int nStatus;
		printf("%d: change %d to IN|OUT\n", i, g_EpollPtr[i]->OUTdealPackage->nMySockFd);
		nStatus = epoll_ctl( epollFd, EPOLL_CTL_MOD, g_EpollPtr[i]->OUTdealPackage->nMySockFd, &ev );
		if( nStatus < 0 ){
			printf("epoll ctl mod epoll fail!\n");
			return ERROR;
		}
	}
	return SUCCESS;
}