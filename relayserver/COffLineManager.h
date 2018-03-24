#include"global.h"

class COffLineManager{
	public:
		vector<int>g_vecIsOnLine;
		COffLineManager();
	   ~COffLineManager();
		int nAddOnLine( int nSockFd );
		int nOffLine( int nSockFd );

};