#include <sys/syscall.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

int main() {
	int fd=syscall(SYS_socket,AF_PACKET,SOCK_RAW,htons(0x88b5));
	unsigned char buffer[65536];
	long result=syscall(SYS_recvfrom,fd,buffer,sizeof(buffer),0,nullptr,nullptr);
	std::cout<<"Des Mac addr: ";
	for(int i=0;i<6;i++){
		std::cout<<buffer[i];
	}
	std::cout<<"\nSrc Mac addr: ";
	for(int i=0;i<6;i++){
		std::cout<<buffer[i+6];
	}
	std::cout<<"\nPayload: ";
	for(int i=14;i<result;i++){
		std::cout<<buffer[i];
	}
	syscall(SYS_close,fd);
}
	
	
