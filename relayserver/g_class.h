#pragma once

#include"global.h"

// extern vector<CRelayAgent*>g_vecIsOnLine;
// extern vector<SOffLineMessage*>g_vecStorageOffLineMessage;

class CGlobalValueMessage{
	public:
		int nGetFriendSockFd( int nMySockFd );
		int pFindFriendRelayAgent( int nMyFriendSockFd );
		int nAddRelayAgentToOnLineTable( CAgent cMyAgent );
		int nFindIsOffLineMessage();
		int nAddOffLineMessage();
		int nDeliverMessageBetweenTask( dealPackage * pDealPkgGlobal, CAgent cMyFriendAgent );
};

class CBuffer;
class CBufferManager{
	public:
		vector<CBuffer*>g_vecBufferManager(CLI_NUM,NULL);
		CBuffer * pGetBuffer( int nSockFd ){
			return g_vecBufferManager[nSockFd];		
		};
		int nSetBuffer( int nSockFd, CBuffer * cBufferArgue ){
			g_vecBufferManager[nSockFd] = cBufferArgue;
			return SUCCESSS;
		};
		
};

class CRelayAgent;
class CAgentManager{
	public:
		vector<CRelayAgent*>g_vecAgentManager(CLI_NUM,NULL);
		CRelayAgent * pGetRelayAgent( int nSockFd ){
			return g_vecAgentManager[nSockFd];
		};
		int nSetRelayAgent( int nSockFd, CRelayAgent * cRelayAgentArgue ){
			g_vecAgentManager[nSockFd] = cRelayAgentArgue;
			return SUCCESSS;
		};
		
};

class CMessageTask;
class CTaskManager{
	public:
		vector<CMessageTask*>g_vecMessageTask(CLI_NUM,NULL);
		CMessageTask * pGetMessageTask( int nSockFd ){
			return g_vecMessageTask[nSockFd];
		};
		int nSetMessageTask( int nSockFd, CMessageTask * cMessageTaskArgue ){
			g_vecMessageTask[nSockFd] = cMessageTaskArgue;
			return SUCCESS;
		};
		
};

