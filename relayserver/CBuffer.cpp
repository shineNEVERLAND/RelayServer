#include"CBuffer.h"
#include"CRelayAgent.h"
#include"CAgentManager.h"


CBuffer :: CBuffer( int nMySocketFd ){
//需要初始化发送队列;另：dealPackage*pDealPkgBuff是被赋值，来获得地址空间的
	
	nMySockFd = nMySocketFd;//+++important####
	
	pDealPkgBuff = NULL;
	
	nPackageLength = 0;
	nReadHeadCount = 0;
	pchReadHeadPtr = (char*)(&nPackageLength);//++++####!!!!****
	
	nType = 0;
	nReadTypeCount = 0;	
	pchReadTypePtr = (char*)(&nType);
	
}

CBuffer :: ~CBuffer(){
	if( pDealPkgBuff ){
		if( pDealPkgBuff->pPkg ){
			++nFreePkg;
			free(pDealPkgBuff->pPkg);
			pDealPkgBuff->pPkg = NULL;
		}
	
		delete pDealPkgBuff;
		pDealPkgBuff = NULL;
	}
	
	
	// list<dealPackage*>::iterator itList;
	dealPackage * pDealPkgTemp;
	
	while( false == lSendList.empty() ){
		pDealPkgTemp = NULL;
		pDealPkgTemp = lSendList.front();
		if( pDealPkgTemp ){
			if( pDealPkgTemp->pPkg ){
				++nFreePkg;
				free(pDealPkgTemp->pPkg);
				pDealPkgTemp->pPkg = NULL;
			}
			delete pDealPkgTemp;
			pDealPkgTemp = NULL;
		}
		lSendList.pop_front();
	}
	

}

int CBuffer :: nListInsertThis( dealPackage * pDealPkg ){
	lSendList.push_back(pDealPkg);
	return SUCCESS;
}

int CBuffer :: nListDeleteThis( dealPackage * pDealPkg  ){
	list<dealPackage*>::iterator itList;
	itList = find( lSendList.begin(), lSendList.end(), pDealPkg );
	if( lSendList.end() != itList ){
		if (pDealPkg) {
			if (pDealPkg->pPkg) {
				++nFreePkg;
				free(pDealPkg->pPkg);
				pDealPkg->pPkg = NULL;
			}
			delete pDealPkg;//++++++++++++++++give me a reason
			pDealPkg = NULL;
		}
		
		lSendList.erase(itList);
		return SUCCESS;
	}
	else
		return ERROR;
}

list<dealPackage*>::iterator CBuffer :: pGetDealPkgFromSendList(){
	
	list<dealPackage*>::iterator itList = lSendList.begin();
	*itList = lSendList.front();
	// pDealPkgBuff = *itList;+++++++++++++++++++++++++++give me a reason!!!!!!作为成员变量的pDealPkgBuff不能随便改！
	
	return itList;
}

int CBuffer :: nIsEmptySendList(){

	if( true == lSendList.empty() ){
		// cout<<"lSendList is empty!"<<endl;
		return SUCCESS;
	}
	else{
		// cout<<"lSendList is not empty!"<<endl;
		return ERROR;
	}
	
}

dealPackage * CBuffer :: pMakeLoginACK(){

	dealPackage * pDealPkgTemp = new dealPackage;
	
	if( NULL == pDealPkgTemp ){
		cout<<"new pDealPkgTemp fail!"<<endl;
		return pDealPkgTemp;
	}
	else{
		pDealPkgTemp->nMySockFd = nMySockFd;//++++****####!!!!important####
		pDealPkgTemp->nMyFriendSockFd = -1;
		
		pDealPkgTemp->bAlreadyAlloc = false;
		pDealPkgTemp->bAlreadyType = false;
				
		pDealPkgTemp->nMessageType = LOGIN_ACK;
		pDealPkgTemp->nWriteCount = 0;
		pDealPkgTemp->nReadCount = 0;
		
		pDealPkgTemp->pchReadPtr = NULL;
		
		
		char message[4];
		// message = (char*)malloc(sizeof(char)*4);
		strcpy( message, "ACK" );
		message[3] = '\0';
		
		int nPackageLengthTemp = strlen(message) + 1 + 2*sizeof(int);
		
		pDealPkgTemp->pPkg = (package*)malloc(nPackageLengthTemp);
		memmove( pDealPkgTemp->pPkg->pchPackageData, message, sizeof(message) );
		
		++nMallocPkg;
		
		pDealPkgTemp->pPkg->nMessageType = LOGIN_ACK;
		pDealPkgTemp->pPkg->nPackageLength = nPackageLengthTemp;
		
		pDealPkgTemp->pchWritePtr = (char*)(pDealPkgTemp->pPkg);
		
		return pDealPkgTemp;
	}

}

int CBuffer :: nAddDealPkgToBufferSendList( dealPackage * pDealPkg ){
	if( SUCCESS == nListInsertThis(pDealPkg)){
		// cout<<"CBuffer :: nAddDealPkgToBufferSendList success!"<<endl;
		return SUCCESS;
	}
	else{
		cout<<"CBuffer :: nAddDealPkgToBufferSendList fail!"<<endl;
		return ERROR;		
	}
	
}

int CBuffer :: nSetDealPkgBuffToSendList( dealPackage * pDealPkg ){
	//pDealPkgBuff只负责存读的数据，不负责写，防止覆盖未读完的数据
	// pDealPkgBuff = pDealPkg;
	
	if( SUCCESS == nAddDealPkgToBufferSendList(pDealPkg) ){
		// cout<<"CBuffer :: nSetDealPkgBuffToSendList"<<endl;
		return SUCCESS;
	}
	else{
		cout<<"CBuffer :: nSetDealPkgBuffToSendList"<<endl;
		return ERROR;
	}
	
}

dealPackage * CBuffer :: pGetDealPkgBuff(){
	if( NULL != pDealPkgBuff ) ;
	else
		cout<<"pDealPkgBuff is NULL!"<<endl;
		
	return pDealPkgBuff;
}

int CBuffer :: nSetDealPackageNull(){
	pDealPkgBuff = NULL;
	return SUCCESS;
}

int CBuffer :: nAllocDealPkg(){
	if( pDealPkgBuff ){
		if( pDealPkgBuff->pPkg ){
			++nFreePkg;
			free(pDealPkgBuff->pPkg);
			pDealPkgBuff->pPkg = NULL;
		}
	
		delete pDealPkgBuff;
		pDealPkgBuff = NULL;
	}
	pDealPkgBuff = new dealPackage;
	
	if( NULL == pDealPkgBuff ){
		cout<<"new pDealPkgBuff fail"<<endl;
		return ERROR;
	}
	else{ 
	
		pDealPkgBuff->nMySockFd = nMySockFd;//++++****####!!!!important####
		pDealPkgBuff->nMyFriendSockFd = -1;
		
		pDealPkgBuff->bAlreadyAlloc = false;
		pDealPkgBuff->bAlreadyType = false;
				
		pDealPkgBuff->nMessageType = -1;
		pDealPkgBuff->nWriteCount = 0;
		pDealPkgBuff->nReadCount = 0;
		
		pDealPkgBuff->pchReadPtr = NULL;
		pDealPkgBuff->pchWritePtr = NULL;
		
		
		pDealPkgBuff->pPkg = NULL;
	
	}
	
	return SUCCESS;
		
}

int CBuffer :: nInitDealPkg(){

	// printf("%d InitDealPkg\n", nMySockFd);
	
    if ( nPackageLength <= 0 ) 
		return ERROR;
		
	pDealPkgBuff->nWriteCount = 0;
	pDealPkgBuff->nReadCount = 0;
	
	pDealPkgBuff->pPkg = ( package* )malloc( nPackageLength );
    if( NULL == pDealPkgBuff->pPkg ){
		cout<<"pDealPkgBuff malloc fail"<<endl;
		return ERROR;
	}
	else
		++nMallocPkg;
	
	pDealPkgBuff->pPkg->nMessageType = pDealPkgBuff->nMessageType;
    pDealPkgBuff->pPkg->nPackageLength = nPackageLength;
    pDealPkgBuff->pchReadPtr = pDealPkgBuff->pPkg->pchPackageData;
    
	
	
	return SUCCESS;
}

int CBuffer :: nFreeDealPackage() {
	
	if (pDealPkgBuff) {
		if (pDealPkgBuff->pPkg) {
			++nFreePkg;
			free(pDealPkgBuff->pPkg);
			pDealPkgBuff->pPkg = NULL;
		}
		delete(pDealPkgBuff);
		pDealPkgBuff = NULL;
	}
	return SUCCESS;
}

int CBuffer :: nRecoverDealPkg(){
	
	pDealPkgBuff->nReadCount = 0;
    pDealPkgBuff->nWriteCount = 0;
	
    pDealPkgBuff->bAlreadyAlloc = false;
	pDealPkgBuff->bAlreadyType = false;
	
	pDealPkgBuff->nMessageType = -1;//消息类型初始被赋值为-1
	
	if( NULL == pDealPkgBuff->pPkg ){
        // cout<<"pPkg = NULL "<<endl;
		return ERROR;
	}
    else{
		++nFreePkg;
        free( pDealPkgBuff->pPkg );
        pDealPkgBuff->pPkg = NULL;
    }
	
    pDealPkgBuff->pchWritePtr = NULL;
    pDealPkgBuff->pchReadPtr = NULL;
	
	if(pDealPkgBuff->pPkg){
		++nFreePkg;
		free(pDealPkgBuff->pPkg);
		pDealPkgBuff->pPkg = NULL;
	}
	
	
	return SUCCESS;
	
}

int CBuffer :: nReadType(){
	int nRead;
    
	nRead = read( nMySockFd, pchReadTypePtr, ( sizeof(int) - nReadTypeCount ) );
	
    if( nRead < 0 )
    {
        if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
			return ECONTINUE;
        else
        {
			perror("nReadType read socket error");
            return ERROR;
        }		
    }

    else if( 0 == nRead )
    {
		cout<<"another close in readType"<<endl;
		return ERROR;
    }

    else
    {
        nReadTypeCount += nRead;
        pchReadTypePtr += nRead;
        
        if( nReadTypeCount == sizeof(int) ){

			pDealPkgBuff->nMessageType = nType;
			
			// printf("%d read %d Type\n", nMySockFd, nPackageLength);
			
			nReadTypeCount = 0;
			pchReadTypePtr = (char*)&nType;
			
			return SUCCESS;
		}
		return ECONTINUE;
	}
}

int CBuffer :: nReadHead(){
	int nRead;

    nRead = read( nMySockFd, pchReadHeadPtr, ( sizeof(int) - nReadHeadCount ) );
	
    if( nRead < 0 )
    {
        if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
			return ECONTINUE;
        else
        {
			perror("nReadHead read socket error");
            return ERROR;
        }		
    }

    else if( 0 == nRead )
    {
		cout<<"another close in readHead"<<endl;
		return ERROR;
    }

    else
    {
        nReadHeadCount += nRead;
        pchReadHeadPtr += nRead;
        
        if( nReadHeadCount == sizeof(int) ){
		
			// printf("%d read %d B length: %d\n", nMySockFd, nRead, nPackageLength);
			
			nReadHeadCount = 0;
			pchReadHeadPtr = (char*)(&nPackageLength);
			
			return SUCCESS;
		}
		return ECONTINUE;
	}
}

int CBuffer :: nReadData(){
	int nRead;
    int nDataLength;
	
    if( NULL == pDealPkgBuff->pPkg )
    {
        cout<<"nMySockFd "<<nMySockFd<<"pDealPkgBuff->pPkg = NULL in nReadData!!!"<<endl;///++++问题出在here！
        return ERROR;
    }
    else 
		nDataLength = pDealPkgBuff->pPkg->nPackageLength - 2*sizeof(int);
	
    nRead = read( nMySockFd, pDealPkgBuff->pchReadPtr, ( nDataLength - pDealPkgBuff->nReadCount ) );
    if( nRead < 0 )
    {
        if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
			return ECONTINUE;
        else
        {
            perror("nReadData read socket error");
            return ERROR;
        }
    }
    else if( 0 == nRead )
    {
        cout<<"another close in readData"<<endl;
        return ERROR;
    }

    else
    {
        pDealPkgBuff->nReadCount += nRead;
        pDealPkgBuff->pchReadPtr += nRead;
		// printf("nReadCount: %d, nDataLength: %d\n", pDealPkgBuff->nReadCount, nDataLength);
        if( nDataLength == pDealPkgBuff->nReadCount ){
			// printf("%d reads %s\n\n", pDealPkgBuff->nMySockFd, pDealPkgBuff->pPkg->pchPackageData);
			// printf("%d reads %d\n\n", pDealPkgBuff->nMySockFd, pDealPkgBuff->pPkg->nPackageLength);
			
			
			pDealPkgBuff->nReadCount = 0;
			pDealPkgBuff->nWriteCount = 0;
			
			nPackageLength = 0;//记录readHead()函数中，读到的头的长度结果	
			
			//读完,写之前，把写指针赋初值//这盘需要写的是整个 头部+负载(头部包含：负载消息类型 和 负载头部长度)
			// pDealPkgBuff->pchWritePtr = ( pDealPkgBuff->pPkg )->chPackageData;
			pDealPkgBuff->pchWritePtr = (char*)pDealPkgBuff->pPkg;
			
			return READ_OVER;
			
		}
		return ECONTINUE;
	}
}


int CBuffer :: nReadOperator(){
	// cout<<"CBuffer :: nReadOperator"<<endl;
	if( false == pDealPkgBuff->bAlreadyType ){
	
		int nTypeStatus = nReadType();
		
		if( ERROR == nTypeStatus ){
			cout<<"nReadType error!"<<endl;
			return ERROR;
		}
		else if( ECONTINUE == nTypeStatus ){
			return ECONTINUE;
		}
		else if( SUCCESS == nTypeStatus ){
			pDealPkgBuff->bAlreadyType = true;
			return ECONTINUE;
		}
		
	}
	
	
	if( false == pDealPkgBuff->bAlreadyAlloc ){
	
		int nHeadStatus = nReadHead();
		
		if( ERROR == nHeadStatus ){
			cout<<"nReadType error!"<<endl;
			return ERROR;
		}
		else if( ECONTINUE == nHeadStatus ){
			return ECONTINUE;
		}
		else if( SUCCESS == nHeadStatus ){
			if( ERROR == nInitDealPkg() )
				return ERROR;
			else{
				pDealPkgBuff->bAlreadyAlloc = true;
				return ECONTINUE;
			}
		}
		
	}
	
	else if( true == pDealPkgBuff->bAlreadyAlloc ){
		
		int nDataStatus = nReadData();
	
		if( ERROR == nDataStatus ){
			cout<<"nReadType error!"<<endl;
			return ERROR;
		}
		else if( ECONTINUE == nDataStatus ){
			return ECONTINUE;
		}
		else if( READ_OVER == nDataStatus ){
			// nAllocDealPkg();
			
			// CRelayAgent * pMyRelayAgentTemp;
			// pMyRelayAgentTemp = g_RelayAgentManager.pGetRelayAgent(nMySockFd);
			// pMyRelayAgentTemp->nSetDealPkgFromBuffer(pDealPkgBuff);
			
			return READ_OVER ;
		}
		
	}

		
}

int CBuffer :: nWriteOperator( dealPackage * pDealPkg ){
	// cout<<"CBuffer :: nWriteOperator"<<endl;
	int nWrite;
	int nPackageLengthTemp = ( pDealPkg->pPkg )->nPackageLength;
	
	nWrite = write( nMySockFd, pDealPkg->pchWritePtr, ( nPackageLengthTemp - pDealPkg->nWriteCount ) );
	
	if( nWrite < 0 )
	{
		if( EWOULDBLOCK == errno || EAGAIN == errno || EINTR == errno )
        {
			return ECONTINUE;
		}
        else
		{
			perror("write socket error");
			return ERROR;
		}
	}
	else if( 0 == nWrite )
	{
		cout<<"nWrite = 0"<<endl;
	    return ECONTINUE;
	}
	else if( 0 < nWrite )
	{
		pDealPkg->nWriteCount += nWrite;
		pDealPkg->pchWritePtr += nWrite;
		
		if( nPackageLengthTemp ==  pDealPkg->nWriteCount ){
			
			// printf("%d sends %d\n\n\n", pDealPkg->nMySockFd, pDealPkg->pPkg->nPackageLength);
			pDealPkg->nWriteCount = 0;			
            
			return WRITE_OVER;
			
			
		}
	}
	
}




