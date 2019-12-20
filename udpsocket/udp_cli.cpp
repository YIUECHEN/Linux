#include"udpsocket.hpp"
#define CHECK_RET(q) if((q)==false){return -1;}
int main(int argc,char *argv[]){
	if(argc!=3){
		printf("./_udp_cli ip port\n");
		return -1;
	}
	string ip=argv[1];
	uint16_t port=atoi(argv[2]);

	//1.创建套接字
	UdpSocket sock;
	CHECK_RET(sock.Socket());
	//2.绑定地址信息(客户端并不推荐手动绑定地址信息)
      //CHECK_RET(sock.Bind(ip,port));
	//3.数据的接收
	//4.数据的发送

        //服务端的地址，让客户端知道数据请求应该发到哪里
	struct sockaddr_in srv_addr;
	srv_addr.sin_family=AF_INET;
        srv_addr.sin_port=htons(port);
        srv_addr.sin_addr.s_addr=inet_addr(ip.c_str());

        while(1){
		string buf;
		cout<<"client say:";
                fflush(stdout);
		cin>>buf;
		CHECK_RET(sock.Send(buf,&srv_addr));

		CHECK_RET(sock.Recv(buf,&srv_addr));
		cout<<"server say:"<<buf<<endl;

	}
	sock.Close();
}
