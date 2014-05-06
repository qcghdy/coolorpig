#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#define BUF_SIZE 1024
using namespace std;
int main(int argc,char* argv[]){
    if(argc<=2){
        cout<<"argc<=2"<<endl;
        return 1;
    }
    const char* ip=argv[1];
    int port=atoi(argv[2]);
    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&server_address.sin_addr);
    server_address.sin_port=htons(port);
    int sockfd=socket(PF_INET,SOCK_STREAM,0);
    int sockudp=socket(PF_INET,SOCK_DGRAM,0);
    assert(sockfd>=0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0){//TCP数据发送与接收
        cout<<"connect error"<<endl;
        return 1;
    }
    else{
        const char* tcp="this is TCP data\n";
        send(sockfd,tcp,strlen(tcp),0);
        char buf[BUF_SIZE];
        int ret=recv(sockfd,buf,BUF_SIZE-1,0);
        if(ret<0){
            cout<<"recv tcp error"<<endl;
        }
        else{
            buf[ret+1]='\0';
            cout<<ret<<" "<<buf<<endl;
        }
    }
    if(connect(sockudp,(struct sockaddr*)&server_address,sizeof(server_address))<0){//UDP数据发送与接收
        cout<<"connect error"<<endl;
        return 1;
    }
    else{
        const char* udp="this is UDP data\n";
        send(sockudp,udp,strlen(udp),0);
        char buf[BUF_SIZE];
        int ret=recv(sockudp,buf,BUF_SIZE-1,0);
        if(ret<0){
            cout<<"recv udp error"<<endl;
        }
        else{
            buf[ret+1]='\0';
            cout<<ret<<" "<<buf<<endl;
        }
    }
    close(sockfd);
    return 0;
}
