#pragma once

#include"global.h"

class CRelayAgent;
class CListenAgent;
class CEpoll{
	public:
		void vEpollRun();
		
		int nCtlAddAgent( CListenAgent * pListenAgent );
		int nCtlAddAgent( CRelayAgent * pRelayAgent, struct epoll_event * pEv );
		
		int nCtlAddWrite( CRelayAgent * cRelayAgent, struct epoll_event * pEv );
		int nCtlDelWrite( CRelayAgent * cRelayAgent, struct epoll_event * pEv );
		int nCtlDelAgent( CRelayAgent * cRelayAgent, struct epoll_event * pEv );
		
		CEpoll( int nMaxNum );
	   ~CEpoll();
	   
	private:
		int nEpollFd;
		int nMaxEventsNum;
		struct epoll_event * pEvents;
};