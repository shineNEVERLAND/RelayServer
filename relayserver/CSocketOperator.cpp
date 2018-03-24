// #include"global.h"
#include"CSocketOperator.h"

CSocketOperator :: CSocketOperator(){
	
}

CSocketOperator :: ~CSocketOperator(){
	
}


int CSocketOperator :: nSocketCreate(){
	struct sockaddr_in servAddr;
	socklen_t servLen;
    
	servLen = sizeof( servAddr );

    //create socket
    nSockFd = socket( AF_INET, SOCK_STREAM, 0 );
    if( nSockFd < 0 )
    {
        perror( "create socket error[socket]" );
        return ERROR;
    }

	bzero( &servAddr, sizeof( servAddr ) );   
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons( SERV_PORT );
    servAddr.sin_addr.s_addr = htonl( INADDR_ANY );//???                                       
    	
    int flag;
    flag = 1;
    if( ( setsockopt( nSockFd, SOL_SOCKET, SO_REUSEADDR, &flag ,sizeof(int) ) ) < 0 )
    {
        perror("setsockopt failed");
        
    }

    if( bind( nSockFd, (struct sockaddr*)&servAddr, servLen ) < 0 )
    {
        perror("bind error");
        delete this;
        return ERROR;
    }

    if( nSetNonBlock( nSockFd ) < 0 )
    {
        perror("nSetNonBlock error");
        delete this;
        return ERROR;
    }

    if( listen( nSockFd, LISTENQ ) < 0 )
    {
        perror("listen error");
        delete this;
        return ERROR;
    }

	// cout<<"nSockFd in nSocketCreate = "<<nSockFd<<endl;
	
    return nSockFd;
	
}

int CSocketOperator :: nAcceptNonBlock(){
	int connfd;
	struct sockaddr_in clientAddr;
	socklen_t clientLen;
	
    clientLen = sizeof( clientAddr );
	
	if( ( connfd = accept( nSockFd, (struct sockaddr*)&clientAddr, &clientLen )) < 0 )
	{

        if( EWOULDBLOCK == errno ){
            cout<<"EWOULDBLOCK"<<endl;
			return ECONTINUE;
		}
        if( EAGAIN == errno ){
            cout<<"EAGAIN"<<endl;
			return ECONTINUE;		
		}
        if( EMFILE == errno ){
            cout<<"EMFILE"<<endl;
			return ECONTINUE;
        }
	}
	
	if( nSetNonBlock( connfd ) < 0 ){
		cout<<"set no block fail!"<<endl;
		return ERROR;
	}
	
	// cout<<"accept no block success!"<<endl;
	return connfd;
		
}

int CSocketOperator :: nSetNonBlock( int fd ){
	int result_fcntl;
    int opts;
    result_fcntl = fcntl( fd, F_GETFL );
    if( 0 > result_fcntl )
    {
    //    perror("fcntl(fd,GETFL)");
        return ERROR;
    }

    opts = result_fcntl | O_NONBLOCK;
    result_fcntl = fcntl( fd, F_SETFL, opts );
    if( 0 > result_fcntl )
    {
     //   perror("fcntl(fd,SETFL)");
        return ERROR;
    }
	return fd;
}



