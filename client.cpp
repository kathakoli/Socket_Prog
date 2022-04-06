#ifndef SOCKET_PROG_CLIENT
#define SOCKET_PROG_CLIENT

#include <iostream>
#include <memory>

#ifndef __LINUX
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

int main() {

  // client
  // create socket
  int socket_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  std::cout << socket_client << std::endl;
  if (socket_client < 0) {
    std::cout << "Socket Not created" << std::endl;
    exit(0);
  }

  // to server address
  struct sockaddr_in toserver_addr;
  toserver_addr.sin_family = AF_INET;
  toserver_addr.sin_port = htons(1027);

  // send to server
  char data_sent[100] = "abcde";
  while (1) {
    int bytes_sent = sendto(socket_client, data_sent, sizeof(data_sent), 0,
                            (struct sockaddr *)&toserver_addr,
                            sizeof(toserver_addr)); // returns size of data sent
    std::cout << bytes_sent << std::endl;
    std::cout << data_sent << std::endl;
  }

  return 0;
}

#endif
