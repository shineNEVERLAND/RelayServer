#include"CTaskManager.h"
#include"CMessageTask.h"
#include"COffLineManager.h"

CTaskManager :: CTaskManager(){
	// vector<CMessageTask*>g_vecMessageTask(CLI_NUM,NULL);
	int i;
	for (i = 0; i < CLI_NUM + FD_NUM; ++i) {
		g_vecMessageTask.push_back(NULL);
	}
	
}
		
CTaskManager :: ~CTaskManager(){
	// int i;
	
	// for( i = 0; i < g_vecMessageTask.size(); ++i ){
		// if( g_vecMessageTask[i] ){
			// g_OffLineManager.nOffLine(i);
			// delete g_vecMessageTask[i];
			// g_vecMessageTask[i] = NULL;
		// }	
	// }
	
	g_vecMessageTask.clear();
	
}	
	
CMessageTask * CTaskManager :: pNewMessageTask(){
	CMessageTask * pMessageTask = new CMessageTask();
	return pMessageTask;
}
		
int CTaskManager :: nDeleteMessageTask( int nSockFd ){
	if( NULL != g_vecMessageTask[nSockFd] ){
		delete g_vecMessageTask[nSockFd];
		g_vecMessageTask[nSockFd] = NULL;
		return SUCCESS;
	}
	else{
		cout<<"aim message task is null!"<<endl;
		return ERROR;
	}
}
		
CMessageTask * CTaskManager :: pGetMessageTask( int nSockFd ){
	return g_vecMessageTask[nSockFd];
}
	
int CTaskManager :: nSetMessageTask( int nSockFd, CMessageTask * cMessageTaskArgue ){

	
	g_vecMessageTask[nSockFd] = cMessageTaskArgue;

	return SUCCESS;
}
		