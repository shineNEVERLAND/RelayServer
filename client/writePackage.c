#include"global.h"

int writePackage( dealPackage * dealPkg )
{
	int nWrite;
	int nPackageLength = ( dealPkg->pPkg )->nPackageLength;
		
	nWrite = write( dealPkg->nMySockFd, dealPkg->pchWritePtr, nPackageLength - dealPkg->nWriteCount );
	if( nWrite < 0 )
	{
		if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
			return ECONTINUE;
		else
		{
			perror("write socket error");
			clean( dealPkg->nMySockFd, dealPkg );
			return ERROR;
		}
	}
	else if( 0 == nWrite )
	{
		return ECONTINUE;
	}
	else
	{
		dealPkg->nWriteCount += nWrite;
		dealPkg->pchWritePtr += nWrite;
		if( nPackageLength ==  dealPkg->nWriteCount )
		{
	//		printf("data write finished!\nthe whole data of (write): %s\n\n", dealPkg->pPkg->pchPackageData );
			
			return SUCCESS;
		}
		else
			return ECONTINUE;
	}
}
