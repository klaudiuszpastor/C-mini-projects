#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8181

int main() {
    int s, c;  // two fd - socket and client
    socklen_t addrlen;
    struct sockaddr_in srv, cli;
    char buf[512];
    char *data;

    addrlen = 0;
    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));

    s = socket(AF_INET, SOCK_STREAM, INADDR_ANY); // all IP adresses
    if (s < 0) {
        printf("socket() \n");
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0; // all IP adresses
    srv.sin_port = htons(PORT);

    
    if (bind(s, (struct sockaddr*)&srv, sizeof(srv)) < 0 ) {
        printf("bind() \n");
        close(s);
        return -1;
    }

    if (listen(s, 5) < 0) {
        printf("bind() \n");
        close(s);
        return -1;
    }
    
    printf("Listening on 0.0.0.0:%d\n", PORT);

    c = accept(s, (struct sockaddr *)&cli, &addrlen); 
    if (c < 0) {
        printf("accept() \n");
        close(s);
        return -1;
    }

    printf("Client connected\n");
    read(c, buf, 511);
    data = "http v1.0\n";
    write(c, data, strlen(data));

    close(c);
    close(s);

    return 0;
}