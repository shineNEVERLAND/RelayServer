#include"global.h"

int EpollAdd( int epollFd, int sockfd, int position )
{
	struct epoll_event ev;
	ev.events = EPOLLOUT;
	ev.data.ptr = g_EpollPtr[position];
//	printf( "dealPkg[%d] address:%p\n", position, dealPkg[position] );
//	printf( "dealPkg[%d]->fd:%d\n", position,dealPkg[position]->nMySockFd );
	
	
	
	if( epoll_ctl( epollFd, EPOLL_CTL_ADD, g_EpollPtr[position]->OUTdealPackage->nMySockFd, &ev ) < 0 )
	{
		perror("epoll_ctl add error");
		return ERROR;
	}
	return SUCCESS;
}

int nEpollDelWrite( int epollFd, dealPackage * dealPtr, struct epoll_event * ev ){
	
	// (ev->data).ptr = dealPtr;
	ev->events = EPOLLIN;
	
	if( epoll_ctl( epollFd, EPOLL_CTL_MOD, dealPtr->nMySockFd, ev ) < 0 )
	{
		perror("epoll_ctl add error");
		return ERROR;
	}
	return SUCCESS;

}






int EpollModInToOut( int epollFd, dealPackage * dealPkg, struct epoll_event * ev )
{
    (ev->data).ptr = dealPkg;
    ev->events = EPOLLOUT;
    if( epoll_ctl( epollFd, EPOLL_CTL_MOD, dealPkg->nMySockFd, ev ) < 0 )//dealPkg->fd?? ( (dealPackage*)(ev.data.ptr) )->fd
	{
		perror("epoll_ctl add error");
		return ERROR;
	}
	return SUCCESS;
}


int EpollModOutToIn( int epollFd, dealPackage * dealPkg, struct epoll_event * ev )
{
    (ev->data).ptr = dealPkg;
    ev->events = EPOLLIN;
    if( epoll_ctl( epollFd, EPOLL_CTL_MOD, dealPkg->nMySockFd, ev ) < 0 )
	{
		perror("epoll_ctl add error");
		return ERROR;
	}
	return SUCCESS;
}

int EpollDel( int epollFd, int sockfd, struct epoll_event * ev )
{
	if( epoll_ctl( epollFd, EPOLL_CTL_DEL, sockfd, ev ) < 0 )
	{
		perror("epoll_ctl add error");
		return ERROR;
	}
	return SUCCESS;
}
