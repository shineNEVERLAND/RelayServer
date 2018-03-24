#include"global.h"

int dealData( int position, dealPackage * dealPtr )
{
	char sendMessage[DATA_SIZE+1];
  
	//设置deal一个登录消息出来
	if( (position >= 0) && (NULL == dealPtr)  )	
	{	
		
		int i;
		for( i = 0; i < DATA_SIZE; i++ ){
			sendMessage[i] = '0';
		}
		// printf("i = %d\n",i);
		sendMessage[DATA_SIZE] = '\0';						
		
		
		int packageLength;
		packageLength = strlen(sendMessage) + 1 + 2*sizeof(int);

		int dataLength;
		dataLength = packageLength - 2*sizeof(int);
		
		dealPackage *dealPtrTemp = g_EpollPtr[position]->OUTdealPackage;
		
		dealPtrTemp->pPkg = (package *)malloc( packageLength );
		if( NULL == dealPtrTemp->pPkg )
		{
			printf("malloc pkg error\n");
			return ERROR;
		}
			//负载的初始化
		dealPtrTemp->pPkg->nPackageLength = packageLength;
		memmove( dealPtrTemp->pPkg->pchPackageData, sendMessage, dataLength );
		dealPtrTemp->pPkg->nMessageType = LOGIN_MESSAGE;
		
		//根据数据的情况，对数据包的一些变量进行修改
		dealPtrTemp->pchWritePtr = (char*)(dealPtrTemp->pPkg);//写的是包
		dealPtrTemp->pchReadPtr = (char*)(dealPtrTemp->pPkg);//读的是负载

		dealPtrTemp->nMessageType = LOGIN_MESSAGE;
		dealPtrTemp->bAlreadyType = TRUE;
		
		dealPtrTemp->bAlreadyAlloc = TRUE;
		// printf("(sendMessage)dealPkg[%d]->pkg->nPackageLength = %d\n", position, dealPkg[position]->pPkg->nPackageLength);
		// printf("(sendMessage)dealPkg[%d]->pkg->packageData = %s\n\n", position, dealPkg[position]->pPkg->pchPackageData );
	}
	if( (position < 0) && (NULL != dealPtr)  )
	{
		
			
		int i;
		for( i = 0; i < DATA_SIZE; i++ ){
			sendMessage[i] = 'a';
		}
		// printf("i = %d\n",i);
		sendMessage[DATA_SIZE] = '\0';						
				
		
	
		int packageLength;
		
		
		packageLength = strlen(sendMessage) + 1 + 2*sizeof(int);

		int dataLength;
		dataLength = packageLength - 2*sizeof(int);
	
		dealPtr->pPkg = (package *)malloc( packageLength );
		if( NULL == dealPtr->pPkg )
		{
			printf("malloc pkg error\n");
			return ERROR;
		}
				
		// 添加负载
		dealPtr->pPkg->nPackageLength = packageLength;
		memmove( dealPtr->pPkg->pchPackageData, sendMessage, dataLength );
		dealPtr->pPkg->nMessageType = NORMAL_MESSAGE;////+++++++important I don't know if the term will be right.
		
		//根据负载的情况，对数据包的一些变量进行修改
		dealPtr->nMessageType = NORMAL_MESSAGE;
		dealPtr->nWriteCount = 0;
		dealPtr->pchWritePtr = (char*)(dealPtr->pPkg);//写的是包
		dealPtr->pchReadPtr = (char*)(dealPtr->pPkg);//读的是负载
		dealPtr->bAlreadyType = TRUE;
		
		dealPtr->bAlreadyAlloc = TRUE;
		// printf("(sendMessage)dealPtr->pPkg->nPackageLength = %d\n",dealPtr->pPkg->nPackageLength);
		// printf("(sendMessage)dealPtr->pPkg->packageData = %s\n",  dealPtr->pPkg->pchPackageData );
		// printf("alloc %d pkg\n", dealPtr->nMySockFd);
	}
	// free(sendMessage);
	return SUCCESS;
}
