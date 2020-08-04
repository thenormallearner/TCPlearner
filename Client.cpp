#include<iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>//uni std
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<assert.h>
#include<stdlib.h>
using std::endl;
using std::cout;
typedef int SOCKET;
#define MYPORT 4567
#define SOCK_ERROR -1
int main(int argc, char const *argv[])
{
    //SOCKET 
    /*建立一个SOCKET*/
    SOCKET socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd == SOCK_ERROR)
    {
        cout<<"socket　创建失败:"<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"socket 创建成功:"<<endl;
    }
    /*连接服务器*/
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    //连接到服务器的端口号
    addr.sin_port=htons(MYPORT);
    /*指向服务器的地址，服务器哪个个地址这个填的就是哪个个地址*/
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int res=connect(socket_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(res==SOCK_ERROR)
    {
        cout<<"connect连接成功\n";
        exit(EXIT_FAILURE);
    }
    cout<<"连接成功\n";
    /*给服务器写信息*/
    write(socket_fd,"Hello,linmuchuan",15);
    /*接受服务器的信息*/
    char recvbuf[256]={};
    int nlen = recv(socket_fd,recvbuf,256,0);
    if(nlen>0)
    {
        cout<<"接收到数据\n"<<recvbuf;
    }
    /*关闭套接字*/
    close(socket_fd);
    return 0;
}
