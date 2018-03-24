#include"CListenAgent.h"
#include"CSocketOperator.h"
#include"CRelayAgent.h"
#include"CAgentManager.h"
#include"CEpoll.h"

CListenAgent :: CListenAgent(){
	
}

CListenAgent :: ~CListenAgent(){
	if( 0 != nMySockFd )
		close( nMySockFd );
		
	if( NULL != pSockOperator ){
		delete pSockOperator;
		pSockOperator = NULL;
	}
	
}

int CListenAgent :: nInitCSocketOperator(){
	pSockOperator = new CSocketOperator;
	if( NULL == pSockOperator ){
		cout<<"pSockOperator new is fail!"<<endl;
		return ERROR;
	}
	else{
		// cout<<"pSockOperator new is success!"<<endl;
		// cout<<"pSockOperator = "<<pSockOperator<<endl;
		// cout<<endl;
		return SUCCESS;
	}
}

CSocketOperator * CListenAgent :: pGetSockOperator(){
	if( NULL == pSockOperator ){
		cout<<"pSockOperator is null!"<<endl;
	}
		
	return pSockOperator;
}

int CListenAgent :: nGetSockFd(){
	return nMySockFd;
}

int CListenAgent :: nSetSockFd( int nSockFd ){
	nMySockFd = nSockFd;
	return SUCCESS;
}

void CListenAgent :: vReadOperator(){
	// cout<<"CListenAgent :: vReadOperator"<<endl;
	int connfd;//++++####!!!!局部变量
	
	connfd = pSockOperator->nAcceptNonBlock();
	
	if( connfd < 0 ){
		cout<<"connfd < 0"<<endl; 
		return ;
	}
	else
		cout<<"connfd = "<<connfd<<endl;

	CRelayAgent * pRelayAgent = NULL;
	pRelayAgent = g_RelayAgentManager.pNewRelayAgent();
	if( NULL == pRelayAgent ){
		cout<<"pRelayAgent new fail!"<<endl;
		return ;
	}
	
	
	pRelayAgent->nSetSockFd(connfd);//###***important	
	
	//建立连接时把agent添加进入agent manager，但不代表agent成功登陆了
	
	g_RelayAgentManager.nSetRelayAgent(connfd, pRelayAgent);
	
	
	if( ERROR == pRelayAgent->nNewMessageTask() ){//调用全局变量g_MessageTaskManager，new一个message task出来
		cout<<"new message task fail!"<<endl;	//并且把对应的MessageTask添加进入MessageTask Manager
		return ;
	}

	if( ERROR == pRelayAgent->nNewBuffer() ){//调用全局变量g_BufferManager，new一个buffer出来
		cout<<"new buffer fail!"<<endl;		//并且把对应的buffer添加进入Buffer Manager
		return ;                        	//并且把relay agent的pDealPkgRelay地址，传递给buffer
	}
		
	
	//将relay agent添加到epoll中
	if( ERROR == cEp.nCtlAddAgent( pRelayAgent, pRelayAgent->pGetEv() ) ){
		cout<<"add relay agent EPOLLIN fail!"<<endl;
		return ;
	}
	
	return ;
	
}

void CListenAgent :: vWriteOperator(){

}
