// Client side 
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFSIZE 1024

int main(int argc, char const* argv[]) {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[BUFSIZE] = { 0 };
    char* hello = "Hello from client";

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creating error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n Invalid address/ Adress not supported");
        return -1;
    }
    /* Convert from presentation format of an Internet number in buffer
    starting at CP to the binary network format and store result for
    interface type AF in buffer starting at BUF.  */

    if ((status = connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))  ) < 0 ) {
        printf("\n Connection Failed \n");
        return -1;
    }

    /*
    The connect() system call connects the socket referred to by the 
    file descriptor sockfd to the address specified by addr. Server’s 
    address and port is specified in addr.
    */

    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent \n");
    valread = read(client_fd, buffer, BUFSIZE -1);
    printf("%s\n",buffer);

    close(client_fd);
    return 0;
}
