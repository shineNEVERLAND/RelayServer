// #include"global.h"
#include"CBufferManager.h"
#include"CBuffer.h"

CBufferManager :: CBufferManager(){
	int i;
	for (i = 0; i < CLI_NUM + FD_NUM; ++i) {
		g_vecBufferManager.push_back(NULL);
	}
	
}
	
CBufferManager :: ~CBufferManager(){
	int i;
	
	
	for( i = 0; i < g_vecBufferManager.size(); ++i ){
		if( g_vecBufferManager[i] ){
			
			delete g_vecBufferManager[i];
			g_vecBufferManager[i] = NULL;
						
		}		
	}
	
	g_vecBufferManager.clear();
	// cout << "CBufferManager delete" << endl;
}
	
CBuffer * CBufferManager :: pNewBuffer( int nSockFd ){
	CBuffer * pBuffer = new CBuffer(nSockFd);
	return pBuffer;
}
		
int CBufferManager :: nDeleteBuffer( int nSockFd ){
	if( NULL != g_vecBufferManager[nSockFd] ){
		delete g_vecBufferManager[nSockFd];
		g_vecBufferManager[nSockFd] = NULL;
		return SUCCESS;
	}			
	else{
		cout<<"aim buffer is null!"<<endl;
		return ERROR;
	}
}
		
CBuffer * CBufferManager :: pGetBuffer( int nSockFd ){
	return g_vecBufferManager[nSockFd];		
}
	
int CBufferManager :: nSetBuffer( int nSockFd, CBuffer * cBufferArgue ){
	g_vecBufferManager[nSockFd] = cBufferArgue;
	return SUCCESS;
}
		
