#include"global.h"

int set_no_block( int sockfd )
{
    int result_fcntl;
    int opts;
    result_fcntl = fcntl( sockfd, F_GETFL );
    if( 0 > result_fcntl )
    {
        perror("fcntl(sockfd,GETFL)");
        return ERROR;
    }

    opts = result_fcntl | O_NONBLOCK;
    result_fcntl = fcntl( sockfd, F_SETFL, opts );
    if( 0 > result_fcntl )
    {
        perror("fcntl(sockfd,SETFL)");
        return ERROR;
    }

    return SUCCESS;

}      