#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

using namespace std;
class UdpSocket{
	public:

		UdpSocket():_sock(-1){}
		~UdpSocket(){}

		bool Socket(){
			_sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			if(_sock<0){
				perror("socket error");
				return false;
			}
			return true;
		}

		bool Bind(string &ip,uint16_t port){
			struct sockaddr_in addr;
			addr.sin_family=AF_INET;
			addr.sin_port=htons(port);
			addr.sin_addr.s_addr=inet_addr(ip.c_str());
                        socklen_t len=sizeof(struct sockaddr_in);

			int ret=bind(_sock,(struct sockaddr*)&addr,len);
			if(ret<0){
				perror("bind error");
				return false;
			}		
		}

		bool Recv(string &buf,struct sockaddr_in *saddr){
			char tmp[1500]={0};
			socklen_t len=sizeof(struct sockaddr_in);
			int ret=recvfrom(_sock,tmp,1500,0,(struct sockaddr*)saddr,&len);
			if(ret<0){
				perror("recvfrom error");
				return false;
			}
                        buf.assign(tmp,ret);
			return true;
		}

		bool Send(string &buf,struct sockaddr_in *daddr){
			socklen_t len=sizeof(struct sockaddr_in);
			int ret=sendto(_sock,buf.c_str(),buf.size(),0,(struct sockaddr*)daddr,len);//.c_str():获取字符的首地址
			if(ret<0){
				perror("sendto error");
				return false;
			}
			return true;
		}

		bool Close(){
			close(_sock);
                        _sock=-1;
		}

	private:
		int _sock;
};
