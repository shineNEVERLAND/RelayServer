#pragma once

#include"global.h"

class CRelayAgent;
class CAgentManager{
	public:
		vector<CRelayAgent*>g_vecAgentManager;
		vector<int>g_vecAgentDeleteList;
		
		CAgentManager();
	   ~CAgentManager();		
		
		CRelayAgent * pNewRelayAgent();
		CRelayAgent * pGetRelayAgent( int nSockFd );
		int nSetRelayAgent( int nSockFd, CRelayAgent * cRelayAgentArgue );
		
		int nGetFriendSockFd( int nMySockFd );//用算法确定对端的套接字ID//
		
		int nAddRelayAgentDeleteList( int nSockFd );
		int nDeleteRelayAgent( int nSockFd );		
		int nDeleteRelayAgentDeleteList();
			
		
};