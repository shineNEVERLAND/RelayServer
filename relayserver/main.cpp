#include"CListenAgent.h"
#include"CSocketOperator.h"
#include"CEpoll.h"
#include"COffLineManager.h"
#include"CBufferManager.h"
#include"CAgentManager.h"
#include"CTaskManager.h"
#include<pthread.h>
#include<signal.h>

CEpoll cEp( CLI_NUM + FD_NUM );
CListenAgent cLisAgt;


COffLineManager g_OffLineManager;

CBufferManager g_BufferManager;

CAgentManager g_RelayAgentManager;

CTaskManager g_MessageTaskManager;



int nMallocPkg = 0;
int nFreePkg = 0;

// vector<int>g_vecIsOnLine(CLI_NUM,-1);
// vector<dealPackage*>g_vecOffLineMessage(CLI_NUM,NULL);

void handle(int s){
	// if( NULL != &cEp ){
		// delete &cEp;
	// }
	
	// if( NULL != &cLisAgt ){
		// delete &cLisAgt;
	// }	
	// if( NULL != &g_RelayAgentManager ){
		// delete &g_RelayAgentManager;
	// }
		
	// if( NULL != &g_BufferManager ){
		// delete &g_BufferManager;
	// }
	
	// if( NULL != &g_MessageTaskManager ){
		// delete &g_MessageTaskManager;
	// }
	// cout<<"nMallocPkg"<<nMallocPkg<<endl;
	// cout<<"nFreePkg"<<nFreePkg<<endl;
		
	exit(0);
	
}


int main(){

	if( SIG_ERR == signal( SIGINT, handle ) ){
		cout<<"signal SIGINT error"<<endl;
	}
	// if( SIG_ERR == signal( SIGPIPE, SIG_IGN ) ){
		// cout<<"signal SIGPIPE error"<<endl;
	// }    
	//屏蔽SIGPIPE信号    
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGPIPE);
    if (0 != pthread_sigmask(SIG_BLOCK, &signal_mask, NULL)) {
        cout << "block sigpipe error" << endl;
    }


//创建listen agent里的CSocketOperator
	if( ERROR == cLisAgt.nInitCSocketOperator() ){
		cout<<"CSocketOperator init fail!"<<endl;
		return ERROR;
	}
	
	int nTempFd;	
	CSocketOperator * cTempSockOp = cLisAgt.pGetSockOperator();
	if( NULL != cTempSockOp ){
		nTempFd = cTempSockOp->nSocketCreate();//这里返回的是监听套接字
		if( ERROR == nTempFd ){
			cout<<"cTempSockOp.nSocketCreate() fail!"<<endl;
			return ERROR;
		}
		else{
			cLisAgt.nSetSockFd(nTempFd);//把返回的监听套接字复制给listen agent
		}
	}
	
	cout<<"listen fd in main() = "<<cLisAgt.nGetSockFd()<<endl;
	
	if( ERROR == cEp.nCtlAddAgent( &cLisAgt ) ){
		cout<<"cEp.nCtlAddAgent( &cLisAgt ) fail!"<<endl;
		return ERROR;
	}
	
    cEp.vEpollRun();

    return 1;

}