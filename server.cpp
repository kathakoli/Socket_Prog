#ifndef SOCKET_PROG_SERVER
#define SOCKET_PROG_SERVER

#include <iostream>
#include <memory>
#include <string.h>

#ifndef __LINUX
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

using namespace std;

int main() {

  // server
  // create socket
  int socket_server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  std::cout << socket_server << std::endl;
  if (socket_server < 0) {
    std::cout << "Socket Not created" << std::endl;
    exit(0);
  }

  // bind SOCKET
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1027); // host to n/w short,range 1025-45191
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // can connect to any IP
  int bind_server =
      bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
  std::cout << bind_server << std::endl;
  if (bind_server < 0) {
    std::cout << "Socket bind unsuccessful" << std::endl;
    exit(0);
  }

  // listen mode & accept
  struct sockaddr_in client_addr;
  char buffer[100];
  int clientaddr_size = sizeof(client_addr);
  int ByteReceived =
      recvfrom(socket_server, (char *)buffer, sizeof(buffer), 0,
               (sockaddr *)&client_addr,
               (socklen_t *)&clientaddr_size); // returns sizeof data received
  std::cout << buffer << std::endl;
  if (ByteReceived < 0) {
    std::cout << "Byte recieve from client unsuccessful" << std::endl;
    exit(0);
  }
  std::cout << ByteReceived << std::endl;

  return 0;
}

#endif