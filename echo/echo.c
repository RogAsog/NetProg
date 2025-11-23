#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int bytes;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    printf("Подключено к echo серверу! Введите сообщение:\n");
    
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);
    
    send(sockfd, buffer, strlen(buffer), 0);
    
    bytes = recv(sockfd, buffer, sizeof(buffer)-1, 0);
    buffer[bytes] = '\0';
    
    printf("Эхо: %s", buffer);
    
    close(sockfd);
    return 0;
}
