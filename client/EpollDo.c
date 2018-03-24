#include"global.h"


void EpollDo( int epollFd )
{
	int readyFdNum;
	int i;


    struct timeval dwStart;
    struct timeval dwEnd;
    unsigned long dwTime;
	
	struct epoll_event events[CLI_NUM];

	dealPackage * dealPtr;//临时变量，指向每个连接的处理模块

	while(1)
	{
		readyFdNum = epoll_wait( epollFd, events, CLI_NUM, 20 );
		
        for( i = 0; i < readyFdNum; i++ )
		{
			if( events[i].events & EPOLLIN  )//是否是可读事件
			{		
					
					int returnRead;
					dealPtr = ((EpollPtr*)events[i].data.ptr)->INdealPackage;
					
                    returnRead = nReadOperator( dealPtr );
						
					if ( SUCCESS == returnRead) {
						if (dealPtr->nMessageType == LOGIN_ACK) {
							//登陆ACK						
							// printf("%d login success %d\n\n", dealPtr->nMySockFd, dealPtr->pPkg->nPackageLength);
							
							g_numLOGINACK += 1;
							//全部已经登陆
							if( CLI_NUM == g_numLOGINACK ){
								// printf("All login success\n");
								if( ERROR == nAddAllAgentToEpoll(epollFd) ){
									return ;
								}
							}							
						} 
						 else {
							//普通
							// printf("%d receives %d\n\n", dealPtr->nMySockFd, dealPtr->pPkg->nPackageLength);
						}
						//释放收到的负载
						nRecoverDealPkg(dealPtr);
						
						continue;
					} 
					else if ( ERROR == returnRead) {
						clean(dealPtr->nMySockFd, dealPtr);
						continue;
					} 
					else{
						continue;
					}
					
			}//end of EPOLLIN
			
			else//触发可写事件
			{
				int returnWrite;
				
				dealPtr = ((EpollPtr*)events[i].data.ptr)->OUTdealPackage;                

                returnWrite = writePackage( dealPtr );
				if( SUCCESS == returnWrite ){
                    if (dealPtr->pPkg->nMessageType == LOGIN_MESSAGE) {
						// printf("%d sends LOGIN_MESSAGE %s\n", dealPtr->nMySockFd, dealPtr->pPkg->pchPackageData);
						// printf("%d sends LOGIN_MESSAGE %d\n\n\n", dealPtr->nMySockFd, dealPtr->pPkg->nPackageLength );
						nRecoverDealPkg(dealPtr);
						nEpollDelWrite( epollFd, dealPtr, &events[i] );
						
					} else {
						// printf("%d sends NORMAL_MESSAGE %s\n", dealPtr->nMySockFd, dealPtr->pPkg->pchPackageData);
						// printf("%d sends %d\n\n\n", dealPtr->nMySockFd, dealPtr->pPkg->nPackageLength );
						nRecoverDealPkg(dealPtr);
					}
					dealData(-1,dealPtr);//+++不停的发数据
					
					// nRecoverDealPkg(dealPtr);
					
				}
				else
					continue;			
			}
			
		}//end of for(i = 0;)..
		
	}//end of while
}
