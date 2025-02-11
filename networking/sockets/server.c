/* Socket programming is a way of connecting two nodes on a network 
to communicate with each other. One socket(node) listens on a particular 
port at an IP, while the other socket reaches out to the other to form 
a connection. The server forms the listener socket while the client reaches 
out to the server. */

// Server side 
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFSIZE 1024

int main(int argc, char const* argv[]) {
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFSIZE] = { 0 };
    char* hello = "Hello from server";

   // Creating socket file descriptor
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
   } 

   /* 
    domain: integer, specifies communication domain. We use AF_ LOCAL as 
    defined in the POSIX standard for communication between processes on
    the same host. For communicating between processes on different hosts 
    connected by IPV4, we use AF_INET and AF_I NET 6 for processes connected 
    by IPV6.
    type: communication type
    SOCK_STREAM: TCP(reliable, connection-oriented)
    SOCK_DGRAM: UDP(unreliable, connectionless)
    protocol: Protocol value for Internet Protocol(IP), which is 0. This is 
    the same number that appears on the protocol field in the IP header of 
    a packet.(man protocols for more details) 
   */

   // Forcefully attaching socket to the port 8080
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
   }

   /*
   This helps in manipulating options for the socket referred by the file 
   descriptor sockfd. This is completely optional, but it helps in reuse 
   of address and port. Prevents error such as: “address already in use”.
   */

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   // Forcefully attaching socket to the port 8080
   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
   }

   /*
  After the creation of the socket, the bind function binds the socket 
  to the address and port number specified in addr(custom data structure). 
  In the example code, we bind the server to the localhost, hence we use 
  INADDR_ANY to specify the IP address. 
   */

   if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
   }

   /*
   It puts the server socket in a passive mode, where it waits for the 
   client to approach the server to make a connection. The backlog, 
   defines the maximum length to which the queue of pending connections 
   for sockfd may grow. If a connection request arrives when the queue 
   is full, the client may receive an error with an indication of ECONNREFUSED.
   */

   if (( new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
   }

   /*
   It extracts the first connection request on the queue of pending 
   connections for the listening socket, sockfd, creates a new connected 
   socket, and returns a new file descriptor referring to that socket. At 
   this point, the connection is established between client and server, 
   and they are ready to transfer data. 
   */

   valread = read(new_socket, buffer, BUFSIZE-1);

   printf("%s\n", buffer);
   send(new_socket, hello, strlen(hello),0);
   printf("Hello message sent\n");

   close(new_socket);
   close(server_fd);
   return 0;
}