
#include"CRelayAgent.h"
#include"CEpoll.h"
#include"CBuffer.h"
#include"CMessageTask.h"
#include"COffLineManager.h"
#include"CBufferManager.h"
#include"CTaskManager.h"
#include"CLoginTask.h"
#include"CAgentManager.h"

CRelayAgent :: CRelayAgent() {
	nMySockFd = -1;
    pEv = new struct epoll_event;//****++++####!!!!
	if( NULL == pEv ){
		cout<<"pEv new fail!"<<endl;
	}
	
}

CRelayAgent :: ~CRelayAgent(){

	cEp.nCtlDelAgent( this, pEv );
	
	if( 0 != nMySockFd )
		close( nMySockFd );
	
	// if( NULL != pDealPkgRelay->pPkg ){
		// free( pDealPkgRelay->pPkg );
		// pDealPkgRelay->pPkg = NULL;
	// }
	// if( NULL != pDealPkgRelay ){
		// delete pDealPkgRelay;
		// pDealPkgRelay = NULL;
	// }
	
	if( NULL != pBuffer ){
		g_BufferManager.nDeleteBuffer(nMySockFd);
		// delete pBuffer;
		pBuffer = NULL;
	}
	
	if( NULL != pMessageTask ){
		// g_MessageTaskManager.nDeleteMessageTask(nMySockFd);
		delete pMessageTask;
		g_OffLineManager.nOffLine(nMySockFd);///当message task 被析构之后，要将message task相应状态改为不在线状态
		pMessageTask = NULL;
	}
	
	if( NULL != pEv ){
		// cout<<"delete pEv"<<endl;
		delete pEv;
		pEv = NULL;
	}

}

int CRelayAgent :: nSetSockFd( int nSockFd ){
	nMySockFd = nSockFd;
	
	return SUCCESS;
}

int CRelayAgent :: nGetSockFd(){
	
	return nMySockFd;
}

struct epoll_event * CRelayAgent :: pGetEv(){

	if( NULL == pEv )
		cout<<"pEv is null!"<<endl;
		
	return pEv;
}

CBuffer * CRelayAgent :: pGetBuffer(){
	return pBuffer;
}


// int CRelayAgent :: nSetDealPkgFromBuffer( dealPackage * pDealPkgBuff ){
	// if( NULL != pDealPkgBuff ){
		// pDealPkgRelay = pDealPkgBuff;
		// if( NULL != pDealPkgBuff->pPkg ){
			// pDealPkgRelay->pPkg = pDealPkgBuff->pPkg;
			// return SUCCESS;
		// }
		// else{
			// return ERROR;
		// }
		
	// }
	// else{
		// cout<<"pDealPkgBuff CRelayAgent :: nSetDealPkgFromBuffer is null!"<<endl;
		// return ERROR;
	// }
	
// }


int CRelayAgent :: nNewBuffer(){
	pBuffer = g_BufferManager.pNewBuffer(nMySockFd);
	if( NULL == pBuffer ){
		cout<<"pBuffer new fail!"<<endl;
		return ERROR;
	}
	else{
		//把relay agent的pDealPkgRelay地址，传递给buffer
		if( ERROR == pBuffer->nAllocDealPkg() ){
			cout<<"pDealPkgBuff is null!"<<endl;
			return ERROR;
		}
		//把对应的buffer添加进入Buffer Manager
		// cout<<"nMySockFd = "<<nMySockFd<<"in CRelayAgent :: nSetSockFd( int nSockFd )"<<endl;
		g_BufferManager.nSetBuffer(nMySockFd, pBuffer);
		return SUCCESS;
		
	}
}

int CRelayAgent :: nNewMessageTask(){
	pMessageTask = g_MessageTaskManager.pNewMessageTask();
	if( NULL == pMessageTask ){
		cout<<"pMessageTask new fail!"<<endl;
		return ERROR;
	}
	else{

		int tempfd = nMySockFd;
		
		g_MessageTaskManager.nSetMessageTask(tempfd, pMessageTask);
		
		return SUCCESS;
	}
}

int CRelayAgent :: nSetDealPkgToBuffer( dealPackage * pDealPkgTask ){	
	//将数据向下传递给本端的Buffer
	if( NULL != pBuffer ){
		if( ERROR == pBuffer->nSetDealPkgBuffToSendList(pDealPkgTask) )
			return ERROR;
		else
			return SUCCESS;
	}
	else
		return ERROR;
}

// int CRelayAgent :: nSetDealPkgRelayToSelfBuffer( dealPackage * pDealPkg ){
	// pDealPkgRelay = pDealPkg;//将数据接收
	// 将数据向下传递给本端的Buffer
	// if( NULL != pBuffer ){
		// if( ERROR == pBuffer->nSetDealPkgBuffToSendList(pDealPkg) )
			// return ERROR;
		// else
			// return SUCCESS;
	// }
	// else
		// return ERROR;
		
// }

dealPackage * CRelayAgent :: pGetDealPkgBuffer(){
	return pBuffer->pGetDealPkgBuff();
}

void CRelayAgent :: vReadOperator(){
	int status;
	CLoginTask cLoginTask;//这样就已经被初始化了
	CRelayAgent * cMyFriendAgent;
	
	dealPackage * pDealPkgTemp = pBuffer->pGetDealPkgBuff();
	
	status = pBuffer->nReadOperator();
	
	if( ERROR ==  status ){
		// cout<<"nMySockFd "<<nMySockFd<<" pBuffer->nReadOperator() is fail!"<<endl;
		//把当前relay agent添加到agent的删除队列中
		g_RelayAgentManager.nAddRelayAgentDeleteList(nMySockFd);
		return ;
	}
	else if( ECONTINUE == status ){
		return ;
	}
	else if( READ_OVER == status ){
		//如果是登陆消息		
		
		if( LOGIN_MESSAGE == pDealPkgTemp->nMessageType ){
			//将这个relayagent添加到在线列表中去。这个动作不能用agent去做。
			// cout<< pDealPkgTemp->nMySockFd << " is logining "<<endl;
			//释放收到的包
			pBuffer->nFreeDealPackage();
			//交给LoginTask，让其创建ACK包并加入Buffer的发送队列
			int nStatusNext = cLoginTask.nNext( nMySockFd );
		
			if( SUCCESS == nStatusNext ){//LoginTask成功完成任务，并且成功生成一个确认ACK。
				// g_OffLineManager.g_vecIsOnLine[nMySockFd] = 1;
				
				if( ERROR == cEp.nCtlAddWrite(this, this->pEv) ){
					cout<<"add write EPOLLIN -> EPOLLIN|EPOLLOUT fail!"<<endl;
					g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
					return ;
				}
			}		
			//创建一个新包
			pBuffer->nAllocDealPkg();

		
			
		}
		//如果是普通消息
		else if( NORMAL_MESSAGE == pDealPkgTemp->nMessageType ){
			
			//将收到的包交给Task处理，返回对端sockfd
			nMyFriendSockFd = pMessageTask->nNext( nMySockFd );
			//创建一个新包
			pBuffer->nSetDealPackageNull();//+++++++++++++++++++++++++不知道有问题没有
			pBuffer->nAllocDealPkg();
			
			if( nMyFriendSockFd < 0 )
				return ;
		
			
		
			//如果对端在线
			if( ON_LINE == g_OffLineManager.g_vecIsOnLine[nMyFriendSockFd] ){
				// cout<<"my friend " << nMyFriendSockFd << " is online  222222222222" << endl;
				//根据对端sockfd，找到对端的relay agent
				cMyFriendAgent = g_RelayAgentManager.pGetRelayAgent(nMyFriendSockFd);
				if( NULL == cMyFriendAgent ){
					cout<<"cMyFriendAgent get fail!"<<endl;
					g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
					return ;
				}				
				//////是不是需要给对端的buffer也创建一个新包？
				//////答：需要的。这里增加了这条语句，可以让对端连接不被关闭
				// CBuffer * pBufferTemp = cMyFriendAgent->pGetBuffer();
				// pBufferTemp->nRecoverDealPkg();
				
				//将对端的relay agent添加进入epoll的
				if( ERROR == cEp.nCtlAddWrite(cMyFriendAgent, cMyFriendAgent->pEv) ){
					cout<<"add friend agent EPOLLIN|EPOLLOUT fail!"<<endl;
					g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
					return ;
				} 
				// else
					// cout<<"nCtlAddWrite friend success"<<endl;
			}
		}
		
		
	}
	return ;
	
}


void CRelayAgent :: vWriteOperator(){
	// cout<<"CRelayAgent :: vWriteOperator"<<endl;
	list<dealPackage*>::iterator itList;
	if( ERROR == pBuffer->nIsEmptySendList() ){//说明发送队列不为空，可以从中取出数据进行发送
		itList = pBuffer->pGetDealPkgFromSendList();
		// pDealPkgRelay = *itList;
		
		int nWriteStatus = pBuffer->nWriteOperator(*itList);
	
		//如果数据都写完了
		if( WRITE_OVER == nWriteStatus ){
			//将本条数据包从Buffer的发送队列中删除
			if( ERROR == pBuffer->nListDeleteThis(*itList) ){
				cout<<"delete this pkg fail!"<<endl;
				g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
				return ;
			}
			//如果数据都写完了,再确认一下是否还有数据
			if( SUCCESS == pBuffer->nIsEmptySendList() ){//表示没有数据了(发送队列真的为空)
		
				if( ERROR == cEp.nCtlDelWrite(this,this->pEv) ){// 此时的relay agent不需要被可写触发
					cout<<"del write fail!"<<endl;
					g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
					return ;
				}
			}
		
		}
		else if( ECONTINUE == nWriteStatus ){
			return ;
		}
		else if( ERROR == nWriteStatus ){
			g_RelayAgentManager.nAddRelayAgentDeleteList(this->nGetSockFd());
			return ;
		}
	
	}
	else
		return ;
}

int CRelayAgent :: nDeleteDealPkg() {
	if (pBuffer) 
		return pBuffer->nFreeDealPackage();
	else 
		return SUCCESS;
}
