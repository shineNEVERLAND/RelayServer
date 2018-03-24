#include"global.h"

//主函数
EpollPtr * g_EpollPtr[CLI_NUM];
void sig_fun(int signo);

long timeAll = 0;
int alreadyRecordCliNum = 0;

int g_numLOGINACK = 0;

long long timeWhole = 0;
long long HandleCount = 0;

int main( int argc, char * argv[] )
{
	int clifd[CLI_NUM];
	int epollFd;
	struct sockaddr_in serv_addr;
	socklen_t serv_len;
	struct epoll_event ev;

	int i;
	

    if( 2 != argc )
        printf("please enter an address\n");

	if( ( epollFd = epoll_create( CLI_NUM ) ) < 0 )
		exit(1);

	for( i = 0; i < CLI_NUM; i++ )
	{
        clifd[i] = create_connect( clifd[i], serv_addr, serv_len, argv[1] );
        if( clifd[i] < 0 )
            exit(1);
			
		if( set_no_block( clifd[i] ) < 0 )
			exit(1);

		allocDealPackage( clifd[i], i );//发送登录消息

		if( g_EpollPtr[i] == NULL )
		{
			printf("g_EpollPtr[%d] = NULL\n", i );
			exit(1);
		}
		if( dealData( i, NULL ) < 0 )    
			exit(1);
			
		if( EpollAdd( epollFd, clifd[i], i ) < 0 )
			exit(1);	
    }

	EpollDo( epollFd );
}

/*	void sig_fun(int signo)
	{
		int i;
		for( i = 0 ; i < CLI_NUM; i++ )
		{
			if( dealPkg[i] != NULL )
			{
				free( dealPkg[i]->pkg );
			    free( dealPkg[i] );
				dealPkg[i] = NULL;
			}
			printf("free num : %d success\n",i);
		}
		raise(SIGQUIT);
	}*/
