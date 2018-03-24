// #include"global.h"
#include"CLoginTask.h"
#include"CRelayAgent.h"
#include"CAgentManager.h"
#include"CBufferManager.h"
#include"CBuffer.h"
#include"COffLineManager.h"

CLoginTask :: CLoginTask(){
	
	
}

CLoginTask :: ~CLoginTask(){
	
	
}

int CLoginTask :: nNext( int nMySockFd ){
	// cout<<"CLoginTask :: nNext"<<endl;
	//获得调用这个nMySockFd对应的relayagent
	CRelayAgent * cMyAgent;
	cMyAgent = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
	if( NULL == cMyAgent ){
		cout<<"agent is null in CLoginTask :: nNext() !"<<endl;
		return ERROR;
	}
	
	// //将cRelayAgent在线的信息加入到全局变量中，
	g_OffLineManager.nAddOnLine(nMySockFd); //g_vecIsOnLine[nMySockFd] = 1;
	
	// 获得这个sockfd对应的buffer
	CBuffer * pTempBuffer;
	pTempBuffer = g_BufferManager.pGetBuffer(nMySockFd);
	if( NULL == pTempBuffer ){
		cout<<"get pTempBuffer fail!"<<endl;
		return ERROR;
	}
	
	// 调用函数cBuffer.nMakeLoginACK(),构造一个业务的登录ACK数据包	
	dealPackage * ackpDealPkg;
	ackpDealPkg = pTempBuffer->pMakeLoginACK();
	if( NULL == ackpDealPkg ){
		cout<<"make login ack fail"<<endl;
		return ERROR;
	}	
	else{
		// cout<<"ackpDealPkg = "<<ackpDealPkg<<endl;
	}
	//将这个ack放入buffer的发送队列中
	if( ERROR == pTempBuffer->nListInsertThis( ackpDealPkg ) ){
		cout<<"insert list fail!"<<endl;
		return ERROR;
	}
	
	//在全局变量g_vecStorageOffMessage中查找，是否有离线消息
	// dealPackage * pofflineDealPkg;
	// if( NON_EMPTY == g_OffLineManager.nFindIsOffLineMessage(nMySockFd) ){
	
	//如果有离线消息，先把消息读出来
	
	// //加入listSendList发送队列
		// if( ERROR == cTempBuffer->nListInsert(pofflineDealPkg) ){
			// cout<<"there is no off line message fail!"<<endl;
			// return ERROR;			
		// }

		
	// }
	
	return SUCCESS;
	
}



