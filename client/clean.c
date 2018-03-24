#include"global.h"

//关闭套接字，清理资源

int clean( int sockfd, dealPackage * dealPkg )
{
	if( close( sockfd ) < 0 )
	{
		perror("close sockfd error");
		return ERROR;
	}
	
	if( NULL != dealPkg )
	{
		free(dealPkg->pPkg);
		free(dealPkg);
        dealPkg = NULL;
	}
	return SUCCESS;
}
