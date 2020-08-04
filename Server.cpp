#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<unistd.h>//uni std
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<assert.h>
using std::endl;
using std::cout;
using std::string;
typedef int SOCKET;
#define MYPORT 4567
#define SOCK_ERROR -1
int main(int argc, char const *argv[])
{
    /* code */
    //建立一个socket
    SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock == SOCK_ERROR)
    {
        cout<<"socket创建失败\n";
        #if 0
        assert(sock!=SOCK_ERROR);
        #endif
        exit(1);
    }
    /*准备通讯地址*/
    struct sockaddr_in addr;
    /*协议*/
    addr.sin_family=AF_INET;
    /*端口*/
    /*将一个无符号短整型的主机数值转换为网络字节顺序，即大尾顺序(big-endian)*/
    addr.sin_port=htons(MYPORT);
    /*协议地址，本次例子是ip地址*/
    /*inet_addr方法可以转化字符串，主要用来将一个十进制的数转化为二进制的数，用途多于ipv4的IP转化。*/
    /*本机地址，防止外网访问*/
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    /*INADDR_ANY内外网都可以访问*/
    /*bind绑定用于接受客户端连接的网络端口*/
    /*
    *参数１socket(....)返回值
    *参数２(struct sockaddr*)&addr　结构体地址
    *参数３addr结构体的长度
    */
    int res=bind(sock,(sockaddr*)&addr,sizeof(addr));
    if(res == SOCK_ERROR)
    {
        cout<<"绑定端口失败\n";
    }
    else
    {
        cout<<"绑定端口成功\n";
    }
    /*监听客户端 listen()*/
    /*
     * 参数１socket(....)返回值
     * 参数２ 进程上限
    */
    res = listen(sock,5);
    if(res == SOCK_ERROR)
    {
        cout<<"错误，监听网络端口失败\n";
    }
    else
    {
        /* code */
        cout<<"监听网络端口成功\n";
    }
    /*等待客户端的连接,accept(),返回用于交互的socket描述符*/
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int fd;
    char *ip=NULL;
    string msg;
    char buffer[255]={};
    //持续接收客户端的连接
    while(1)
    {
        fd=accept(sock,(sockaddr*)&client,&len);
        if(fd == SOCK_ERROR)
        {
            cout<<"Accept错误,接受到无效客户端\n";
        }
        /*使用上一步返回的socket描述符,进行读写通信*/
        ip = inet_ntoa(client.sin_addr);
        cout<<"客户：［"<<ip<<"]连接成功\n";
        /*向客户端发送一条数据*/
        msg = "Hello,I'am server\n";
        send(fd,msg.c_str(),strlen(msg.c_str())+1,0);
        /*通过fd与客户端联系在一起,返回接收到的字节数*/
        /*接收客户端的数据*/
        /*
        *第一个参数：accept 返回的文件描述符
        *第二个参数：存放读取的内容
        *第三个参数：内容的大小
        */
        int size=read(fd,buffer,sizeof(buffer));
        cout<<"接收到的字节数"<<size<<"\n";
        cout<<"内容: "<<buffer<<endl;
    }
    /*关闭套接字*/
    close(fd);
    close(sock);
    return 0;
}
