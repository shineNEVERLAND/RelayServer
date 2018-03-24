#include"COffLineManager.h"

COffLineManager :: COffLineManager(){
	// vector<int>g_vecIsOnLine(CLI_NUM,-1);
	int i;
	for (i = 0; i < CLI_NUM + FD_NUM; ++i) {
		g_vecIsOnLine.push_back(OFF_LINE);
	}
}

COffLineManager :: ~COffLineManager(){
	int i;
	for( i = 0; i < g_vecIsOnLine.size(); ++i ){
		// cout<<i<<" is off_line"<<endl;
		g_vecIsOnLine[i] = OFF_LINE;		
	}
	
	g_vecIsOnLine.clear();
}

int COffLineManager :: nAddOnLine( int nSockFd ){
	g_vecIsOnLine[nSockFd] = ON_LINE;
	cout << nSockFd << " is online" << endl;
	return SUCCESS;
}

int COffLineManager :: nOffLine( int nSockFd ){
	g_vecIsOnLine[nSockFd] = OFF_LINE;
	return SUCCESS;
}

// int COffLineManager :: nIfOnLine( int nSockFd ){
	// ifg_vecIsOnLine[nSockFd]
// }	