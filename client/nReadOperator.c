#include"global.h"


int nInitDealPkg( int nPackageLength, dealPackage * pDealPkg ){

    if ( nPackageLength <= 0 ) 
		return ERROR;
	
	pDealPkg->nWriteCount = 0;
	pDealPkg->nReadCount = 0;
	
	pDealPkg->pPkg = ( package* )malloc( nPackageLength );
    if( NULL == pDealPkg->pPkg ){
		printf("pDealPkg malloc fail\n");
		return ERROR;
	}
	
    pDealPkg->pPkg->nPackageLength = nPackageLength;
	pDealPkg->pPkg->nMessageType = pDealPkg->nMessageType;
	
    pDealPkg->pchReadPtr = pDealPkg->pPkg->pchPackageData;
	
	return SUCCESS;
}

int nRecoverDealPkg(dealPackage * pDealPkg){
	
	pDealPkg->nReadCount = 0;
    pDealPkg->nWriteCount = 0;
	
    pDealPkg->bAlreadyAlloc = FALSE;
	pDealPkg->bAlreadyType = FALSE;
	
	pDealPkg->nMessageType = -1;//消息类型初始被赋值为-1
	
	if( NULL == pDealPkg->pPkg ){
        //printf("pPkg = NULL\n");
		//return ERROR;
	}
    else{
        free( pDealPkg->pPkg );
        pDealPkg->pPkg = NULL;
    }
	
    pDealPkg->pchWritePtr = NULL;
    pDealPkg->pchReadPtr = NULL;
	
	return SUCCESS;
	
}



int nReadType(dealPackage * pDealPkg){
	int nReadTypeCount = 0;
	int nRead = 0;
	int nType = -1;
    char * pchReadTypePtr = (char*)&nType;
	
	while( nRead < sizeof(int) ){
		nRead = read( pDealPkg->nMySockFd, pchReadTypePtr, ( sizeof(int) - nReadTypeCount ) );
		if( nRead < 0 )
		{
			if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
				continue;
			else
			{
				perror("read socket error");
				return ERROR;
			}		
		}
		else if( 0 == nRead )
		{
			printf("another close in readType\n");
			return ERROR;
		}
		else
		{
			nReadTypeCount += nRead;
			pchReadTypePtr += nRead;
			
			if( nReadTypeCount == sizeof(int) ){
				
				pDealPkg->nMessageType = nType;
				
				nReadTypeCount = 0;
				pchReadTypePtr = (char*)&nType;
				
				return SUCCESS;
			}
			continue;
		}
	}
}

int nReadHead(dealPackage * pDealPkg){
	int nReadHeadCount = 0;
	int nPackageLength = 0;
	int nRead;
	char * pchReadHeadPtr = (char*)&nPackageLength;
	
	while( nReadHeadCount < sizeof(int) ){
		nRead = read( pDealPkg->nMySockFd, pchReadHeadPtr, ( sizeof(int) - nReadHeadCount ) );
		
		if( nRead < 0 )
		{
			if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
				continue;
			else
			{
				perror("read socket error");
				return ERROR;
			}		
		}

		else if( 0 == nRead )
		{
			printf("another close in readHead\n");
			return ERROR;
		}

		else
		{
			nReadHeadCount += nRead;
			pchReadHeadPtr += nRead;
			
			if( nReadHeadCount == sizeof(int) ){
				nReadHeadCount = 0;
				pchReadHeadPtr = (char*)(&nPackageLength);
				return nPackageLength;
			}
			continue;
		}
	}
}

int nReadData(dealPackage * pDealPkg){
	int nRead;
    int nDataLength;
	
    if( NULL == pDealPkg->pPkg )
    {
        printf("pDealPkg->pPkg = NULL\n");
        return ERROR;
    }
    else 
		nDataLength = pDealPkg->pPkg->nPackageLength - 2*sizeof(int);
	
    nRead = read( pDealPkg->nMySockFd, pDealPkg->pchReadPtr, ( nDataLength - pDealPkg->nReadCount ) );

    if( nRead < 0 )
    {
        if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
			return ECONTINUE;
        else
        {
            perror("read socket error");
            return ERROR;
        }
    }
    else if( 0 == nRead )
    {
        printf("another close in readData\n");
        return ERROR;
    }

    else
    {
        pDealPkg->nReadCount += nRead;
        pDealPkg->pchReadPtr += nRead;
		
        if( nDataLength == pDealPkg->nReadCount ){
			
					
			pDealPkg->nReadCount = 0;
			pDealPkg->nWriteCount = 0;
			
			pDealPkg->pchWritePtr = (char*)pDealPkg->pPkg;
			
			return SUCCESS;
			
		}
		return ECONTINUE;
	}
}


int nReadOperator(dealPackage * pDealPkg){
	if( FALSE == pDealPkg->bAlreadyType ){
	
		int nTypeStatus = nReadType(pDealPkg);
		
		if( ERROR == nTypeStatus ){
			printf("nReadType error!\n");
			return ERROR;
		}
		else if( SUCCESS == nTypeStatus ){
			pDealPkg->bAlreadyType = TRUE;
			return ECONTINUE;
		}
		
	}
	
	if( FALSE == pDealPkg->bAlreadyAlloc ){
	
		int nHeadStatus = nReadHead(pDealPkg);
		
		if( ERROR == nHeadStatus ){
			printf("nReadType error!\n");
			return ERROR;
		}
		else if( 0 < nHeadStatus ){
			if( ERROR == nInitDealPkg(nHeadStatus, pDealPkg) )
				return ERROR;
			else{
				pDealPkg->bAlreadyAlloc = TRUE;
				return ECONTINUE;
			}
		}
		
	}
	
	else if( TRUE == pDealPkg->bAlreadyAlloc ){
	
		int nDataStatus = nReadData(pDealPkg);
	
		if( ERROR == nDataStatus ){
			printf("nReadType error!\n");
			return ERROR;
		}
		else if( ECONTINUE == nDataStatus ){
			return ECONTINUE;
		}
		else if( SUCCESS == nDataStatus ){
			
			return SUCCESS ;
		}
		
	}

		
}