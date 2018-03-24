// #include"global.h"
#include"CMessageTask.h"
#include"CRelayAgent.h"
#include"CBuffer.h"
#include"CBufferManager.h"
#include"COffLineManager.h"
#include"CAgentManager.h"
#include"CTaskManager.h"

CMessageTask :: CMessageTask(){
	
}

CMessageTask :: ~CMessageTask(){
	// if( pDealPkgTask ){
		// delete pDealPkgTask;
		// if( pDealPkgTask->pPkg )
			// pDealPkgTask->pPkg = NULL;		
		
		// pDealPkgTask = NULL;
	// }
}

// int CMessageTask :: nSetDealPkgMessageTask( dealPackage * pDealPkg ){
	// pDealPkgTask = pDealPkg;
	// if( NULL != pDealPkg ){
		// cout<<"pDealPkg is not null!"<<endl;
		// return SUCCESS;
	// }
	// else{
		// cout<<"pDealPkg is null!"<<endl;
		// return ERROR;
	// }
// }

int CMessageTask :: nDeliverMessageBetweenTask( int nMySockFd, int nMyFriendSockFd ){
	//MessageTask得到自己对应的relay agent//类似连接发起者A
	CRelayAgent * pMyAgentTemp;
	pMyAgentTemp = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
	if( NULL == pMyAgentTemp ){
		cout<<"pMyAgentTemp is null!"<<endl;
		return ERROR;
	}
	
	//从自己的relay agent中得到 数据包
	dealPackage * pDealPkgTemp = pMyAgentTemp->pGetDealPkgBuffer();
	if( NULL == pDealPkgTemp ){
		cout<<"pDealPkgTemp is null!"<<endl;
		return ERROR;
	}
	
	//根据对端sockfd，找到对端message task
	CMessageTask * pFriendMessTask;
	pFriendMessTask = g_MessageTaskManager.pGetMessageTask(nMyFriendSockFd);
	if( NULL == pFriendMessTask ){
		cout<< nMySockFd << " pFriendMessTask " << nMyFriendSockFd << " is null!"<<endl;
		return ERROR;
	}
	
	//把数据传给对端message task
	if( ERROR == nSendMessageToAnotherTask(nMyFriendSockFd, pDealPkgTemp, pFriendMessTask) ){
		cout<<"CMessageTask :: nSendMessageToAnotherTask is fail!"<<endl;
		return ERROR;
	}
	
	return SUCCESS;	
	
}

int CMessageTask :: nSendMessageToAnotherTask( int nMyFriendSockFd, dealPackage * pDealPkg, CMessageTask * pMessageTask ){
	//调用对端的message task，去接收数据包
	/*if( SUCCESS == pMessageTask->nReceiveMessageFromAnotherTask(pDealPkg)) ;
		// cout<<"send dealPackage success!"<<endl;
	else{
		cout<<"send dealPackage fail!"<<endl;
		return ERROR;
	}*/
	//在对端的message task ，将数据传递给本端的共同体relay agent
	if( ERROR == pMessageTask->nDeliverDealPkgToSelfAgent(nMyFriendSockFd, pDealPkg)){
		cout<<"pMessageTask->nDeliverDealPkgToSelfAgent is error!"<<endl;
		return ERROR;
	}
	
	return SUCCESS;
}

//对端message task 接收数据包
// int CMessageTask :: nReceiveMessageFromAnotherTask( dealPackage * pDealPkg ){
	// 类似连接接收者B
	// if( NULL != pDealPkg ){
		// pDealPkgTask = pDealPkg;
		// return SUCCESS;		
	// }
	// else{
		// cout<<"pDealPkg is null!"<<endl;
		// return ERROR;
	// }
		
// }

//将本端message task的数据，传给本端relay agent
int CMessageTask :: nDeliverDealPkgToSelfAgent( int nMySockFd, dealPackage * pDealPkg ){
	//找到本端的relay agent
	CRelayAgent * pRelayAgentTemp;
	pRelayAgentTemp = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
	if( NULL == pRelayAgentTemp ){
		cout<<"pRelayAgentTemp is null!"<<endl;
		return ERROR;
	}
		
	//先将数据给本端的agent
	// if( ERROR == pRelayAgentTemp->nSetDealPkgSelfAgent(pDealPkg) ){
		// cout<<"pRelayAgentTemp->nSetDealPkgSelfAgent is error!"<<endl;
		// return ERROR;
	// }
	
	//将数据给本端的agent，在agent中将数据给本端的buffer
	if( ERROR == pRelayAgentTemp->nSetDealPkgToBuffer(pDealPkg)){//relay agent 的nSetDealPkgRelay把数据包传给本端的buffer
		cout<<"pRelayAgentTemp->nSetDealPkgRelayToSelfBuffer is error!"<<endl;
		return ERROR;
	}
	
	return SUCCESS;
	
}

//message task的这个函数，函数的是对端的sockfd
int CMessageTask :: nNext( int nMySockFd ){
	// cout<<"CMessageTask :: nNext"<<endl;
	//获得调用这个CMessageTask的relayagent对应的buffer
	// CBuffer * pBuff;
	// pBuff = g_BufferManager.pGetBuffer(nMySockFd);
	// if( NULL == pBuff ){
		// cout<<"pBuff get fail!"<<endl;
		// return ERROR;
	// }	
	
	//查找对端的sockfd
	int nMyFriendSockFd; 
	nMyFriendSockFd = g_RelayAgentManager.nGetFriendSockFd(nMySockFd);
	
	//根据对端sockfd，查看对端是否在线
	//如果对端不在线
	// if( -1 == g_vecIsOnLine[nMyFriendSockFd] ){
	
	
	// if( -1 == g_OffLineManager.g_vecIsOnLine[nMyFriendSockFd] ){	
		// cout<<"nMyFriendSockFd = "<<nMyFriendSockFd<<"is off line!"<<endl;
		// if( ERROR == g_GlobalValueManager.nAddOffLineMessage(nMyFriendSockFd,pBuff->pDealPkgBuff) ){
			// cout<<"add off line message fail!"<<endl;
			// return ERROR;
		// }
	// }
	
	
	//如果对端在线
	 if( OFF_LINE != g_OffLineManager.g_vecIsOnLine[nMyFriendSockFd] ){
		// cout<<"nMyFriendSockFd = "<<nMyFriendSockFd<<" is on line!"<<endl;
		if( ERROR == nDeliverMessageBetweenTask(nMySockFd, nMyFriendSockFd) ){
			cout<<"message deliver from " << nMySockFd << " to " << nMyFriendSockFd << " fail!"<<endl;
			//传递失败，将该消息释放
			CRelayAgent * pMyAgentTemp;
			pMyAgentTemp = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
			if( NULL == pMyAgentTemp ){
				cout<<"pMyAgentTemp is null!"<<endl;
				return ERROR;
			}
			
			//从自己的relay agent中得到 数据包
			pMyAgentTemp->nDeleteDealPkg();
			return ERROR;
		}
	} else {
		//不在线，将该消息释放
		CRelayAgent * pMyAgentTemp;
		pMyAgentTemp = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
		if( NULL == pMyAgentTemp ){
			cout<<"pMyAgentTemp is null!"<<endl;
			return ERROR;
		}
		
		//从自己的relay agent中得到 数据包
		pMyAgentTemp->nDeleteDealPkg();
		
	}
	
	return nMyFriendSockFd;
	
}




