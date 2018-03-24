// #include"global.h"
#include"CAgentManager.h"
#include"CRelayAgent.h"

CAgentManager :: CAgentManager(){
	int i;
	// for (i = 0; i < CLI_NUM + 1000; ++i) {
	for (i = 0; i < CLI_NUM + FD_NUM; ++i) {
		g_vecAgentManager.push_back(NULL);
	}
	
}

CAgentManager :: ~CAgentManager(){
	
	int i;
	for( i = 0;i < g_vecAgentManager.size(); ++i ){
		if( g_vecAgentManager[i] ){
			// printf("i = %d\n",i);
			delete g_vecAgentManager[i];
			g_vecAgentManager[i] = NULL;
			
		}
		else
			continue;
	}
	g_vecAgentManager.clear();
	g_vecAgentDeleteList.clear();
	
}

CRelayAgent * CAgentManager :: pNewRelayAgent(){//分配agent空间
	CRelayAgent * pRelayAgent = new CRelayAgent(); 		
	return pRelayAgent;
}		
			
CRelayAgent * CAgentManager :: pGetRelayAgent( int nSockFd ){//获取agent
	return g_vecAgentManager[nSockFd];
}
		 
int CAgentManager :: nSetRelayAgent( int nSockFd, CRelayAgent * cRelayAgentArgue ){//重置（修改）agent 
	
	// cout<<"nSockFd = "<<nSockFd<<" CAgentManager :: nSetRelayAgent"<<endl;
	g_vecAgentManager[nSockFd] = cRelayAgentArgue;
	
	return SUCCESS;
	
}

int CAgentManager :: nGetFriendSockFd( int nMySockFd ){

	int i;
	for( i = 0; i < g_vecAgentManager.size(); ++i ){
		if( NULL == g_vecAgentManager[i] )
			continue;
		else
			break;
	}
	
	
	nMySockFd -= i;
		
	int nMyFriendSockFd;
	if( 0 == (nMySockFd%2) )
		nMyFriendSockFd = nMySockFd + 1 + i;
	else if( 1 == (nMySockFd%2) )
		nMyFriendSockFd = nMySockFd - 1 + i;

	return nMyFriendSockFd;
	
	
}


int CAgentManager :: nAddRelayAgentDeleteList( int nSockFd ){
	g_vecAgentDeleteList.push_back(nSockFd);
	return SUCCESS;
}

int CAgentManager :: nDeleteRelayAgent( int nSockFd ){

	// vector<CRelayAgent*>::iterator itRelayAgent;
	// itRelayAgent = g_vecAgentManager.begin() + *itList;
	
	// cout<<"g_vecAgentManager[*itList] = "<<g_vecAgentManager[*itList]<<endl;
	if( g_vecAgentManager[nSockFd] ){
		delete g_vecAgentManager[nSockFd];
		g_vecAgentManager[nSockFd] = NULL;
	}
	// g_vecAgentManager.erase(itRelayAgent);
	return SUCCESS;
}

int CAgentManager :: nDeleteRelayAgentDeleteList(){//agent要删除的队列里面装的是int nSockFd

	vector<int>::iterator itDeleteList = g_vecAgentDeleteList.begin();
	while( g_vecAgentDeleteList.end() != itDeleteList ){
		nDeleteRelayAgent( *itDeleteList );
		g_vecAgentDeleteList.erase(itDeleteList);
	}
	return SUCCESS;
}
			


		