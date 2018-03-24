#include"CEpoll.h"
#include"CAgent.h"
#include"CRelayAgent.h"
#include"CListenAgent.h"
#include"CAgentManager.h"



CEpoll :: CEpoll( int nMaxNum ){

	nMaxEventsNum = nMaxNum;
	
	nEpollFd = epoll_create( nMaxEventsNum );
	if( nEpollFd < 0 )
		cout<<"epoll create fail"<<endl;
	else
		cout<<"nEpollFd = "<<nEpollFd<<endl;
	
	pEvents = new struct epoll_event[nMaxEventsNum];
	if( NULL == pEvents )
		cout<<"epoll create fail"<<endl;

}

CEpoll :: ~CEpoll(){
	if( NULL != pEvents ){
		delete [] pEvents;
		pEvents = NULL;
	}
}

void CEpoll :: vEpollRun(){
	int i;
	int nReadyFdNum;
	CAgent * pAgent = NULL;
	
	cout<<"start epoll run()"<<endl;
	while(1){
	    nReadyFdNum = epoll_wait( nEpollFd, pEvents, nMaxEventsNum, -1 );	
		
		// cout<<nReadyFdNum<<endl;
        for( i = 0; i < nReadyFdNum; i++ ){

			pAgent = (CAgent*)pEvents[i].data.ptr;
			
            if ( NULL == pAgent ) {
                cout << "pAgent == NULL" << endl;
                continue;
            }
			
            if( pEvents[i].events & EPOLLIN ){
				// cout<<"pAgent->nReadOperator() in epoll run"<<endl;
				pAgent->vReadOperator();
				
			}
            if( pEvents[i].events & EPOLLOUT ){
				// cout<<"pAgent->nWriteOperator() in epoll run"<<endl;
				pAgent->vWriteOperator();
				
			}
			
			g_RelayAgentManager.nDeleteRelayAgentDeleteList();	
				
        }
	}

}

int CEpoll :: nCtlAddAgent( CListenAgent * pLisAgent ){
	struct epoll_event pEv;
	
	pEv.events = EPOLLIN;
	pEv.data.ptr = pLisAgent;

	if( epoll_ctl( nEpollFd, EPOLL_CTL_ADD, pLisAgent->nGetSockFd(), &pEv ) < 0 ){
		cout<<"ctl add listenAgent fail!"<<endl;
		return ERROR;
	}
	
	return SUCCESS;
}

int CEpoll :: nCtlAddAgent( CRelayAgent * pRelayAgent, struct epoll_event * pEv ){
	
	pEv->events = EPOLLIN;
	(pEv->data).ptr = pRelayAgent;
	
	if( epoll_ctl( nEpollFd, EPOLL_CTL_ADD, pRelayAgent->nGetSockFd(), pEv ) < 0 ){
		cout<<"ctl add clientAgent fail"<<endl;
		return ERROR;
	}
	
	return SUCCESS;
}

int CEpoll :: nCtlAddWrite( CRelayAgent * cRelayAgent, struct epoll_event * pEv ){
	
	pEv->events = EPOLLIN|EPOLLOUT;
	(pEv->data).ptr = cRelayAgent;
	if( epoll_ctl( nEpollFd, EPOLL_CTL_MOD, cRelayAgent->nGetSockFd(), pEv ) < 0 ){
		cout<<"ctl add clientAgent fail"<<endl;
		return ERROR;
	}
	
	return SUCCESS;

}

int CEpoll :: nCtlDelWrite( CRelayAgent * cRelayAgent, struct epoll_event * pEv ){

	pEv->events = EPOLLIN;
	(pEv->data).ptr = cRelayAgent;
	
	if( epoll_ctl( nEpollFd, EPOLL_CTL_MOD, cRelayAgent->nGetSockFd(), pEv ) < 0 ){
		cout<<"ctl add clientAgent fail"<<endl;
		return ERROR;
	}
	
	return SUCCESS;

}

int CEpoll :: nCtlDelAgent( CRelayAgent * cRelayAgent, struct epoll_event * pEv ){

	if( epoll_ctl( nEpollFd, EPOLL_CTL_DEL, cRelayAgent->nGetSockFd(), NULL ) < 0 ){
		cout<<"ctl mod out to in fail"<<endl;
		return ERROR;
	}
	
	return SUCCESS;
		
}





