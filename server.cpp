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
    int listen_fd = 0, conn_fd = 0;
    //int ret_read;
    char message[200] = "The test message from server!";
    
    struct sockaddr_in serv_addr, client_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    socklen_t client_addr_len;
    client_addr_len = sizeof(client_addr);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // create a socket for server
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1){
        sys_err("server socket error");
    }
    
    int ret_bind;
    ret_bind = bind(listen_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if(ret_bind == -1){
           sys_err("server bind error");
    }
    
    listen(listen_fd, 128);
    
    conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if(conn_fd == -1){
           sys_err("server accept error");
    }
    
	
	write(conn_fd, message, sizeof(message));
	
	close(listen_fd);
	close(conn_fd);
    
    return 0;
}
