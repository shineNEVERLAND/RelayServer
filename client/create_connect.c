#include"global.h"


int create_connect( int clifd, struct sockaddr_in serv_addr, socklen_t serv_len, char * argv ){
	
	serv_len = sizeof( serv_addr );
	
	//create socket
	clifd = socket( AF_INET, SOCK_STREAM, 0 );
	if( clifd < 0 )
	{
		perror( "create socket error[socket]" );
		return ERROR;
	}
	// else{
		// printf("clifd = %d\n",clifd);
	// }
	
	//init socket
    int result;

    bzero( &serv_addr, sizeof( serv_addr ) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( SERV_PORT );
    if( (result = inet_pton( AF_INET, argv, &serv_addr.sin_addr ) ) < 0 )
    {
        perror("inet_pton error");
        exit(1);
    } 

	if( connect( clifd, (struct sockaddr*)&serv_addr, serv_len ) < 0 )
	{
		perror("connect error");
        exit(EXIT_FAILURE);
        return ERROR;
	}
	else
	{
        return clifd;
	}

}
