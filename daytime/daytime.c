#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 13

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int bytes;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    printf("Отправляем запрос на daytime сервер...\n");
    
    sendto(sockfd, NULL, 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    bytes = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, NULL, NULL);
    buffer[bytes] = '\0';
    
    printf("Текущее время: %s", buffer);
    
    close(sockfd);
    return 0;
}
