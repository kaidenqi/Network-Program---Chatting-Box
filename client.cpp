#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 9555

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int conn_fd;
    char buf[200];

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr.s_addr);
	
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_fd == -1){
        sys_err("client socket error");
    }

    int ret_connect;
    ret_connect = connect(conn_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret_connect == -1)
    {
        sys_err("client connect error");
    }
    
	
    int ret_read;
    ret_read= read(conn_fd, buf, sizeof(buf));
    if(ret_read == -1){
        sys_err("client connect error");
    }
    
	printf("The test message from sever: %s \n", buf);
	close(conn_fd);
    
    return 0;
}
