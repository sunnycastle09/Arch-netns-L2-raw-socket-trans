#include <sys/syscall.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/syscall.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

int main(){
	int fd=syscall(SYS_socket,AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	std::cout<<"enter receiver interface index: ";
	int ifindex;
	std::cin>>ifindex;
	std::vector <unsigned char> frame;
	int tmp;
	std::cout<<"enter Des mac addr per one byte\n";
	for(int i=0;i<6;i++){
		std::cout<<i+1<<": ";
		std::cin>>std::hex>>tmp;
		frame.push_back(tmp);
	}
	std::cout<<"enter Src mac addr per one byte\n";
	for(int i=0;i<6;i++){
		std::cout<<i+1<<": ";
		std::cin>>std::hex>>tmp;
		frame.push_back(tmp);
	}
	frame.push_back(0x88);
	frame.push_back(0xb5);
	std::cout<<"enter string data for send: ";
	std::string str;
	std::cin>>str;
	for(char c: str){
		frame.push_back(static_cast<unsigned char>(c));
	}
	struct sockaddr_ll addr{0};
	addr.sll_family = AF_PACKET;
	addr.sll_protocol=htons(0x88b5);
	addr.sll_ifindex=ifindex;
	addr.sll_halen=ETH_ALEN;
	memcpy(addr.sll_addr,frame.data(),ETH_ALEN);
	long result=syscall(SYS_sendto,fd,frame.data(),frame.size(),0,&addr,sizeof(addr));
	std::cout<<"des mac addr: ";
	for(int i=0;i<6;i++){
		std::cout<<std::hex<<int(frame[i])<<":";
	}
	std::cout<<"\nsrc mac addr: ";
	for(int i=0;i<6;i++){
		std::cout<<int(frame[i+6])<<":";
	}
	std::cout<<"\n";
	perror("sendto");
}
