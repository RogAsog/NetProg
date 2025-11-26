#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "использование: " << argv[0] << " <сообщение>" << std::endl;
        return 1;
    }

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "ошибка создания сокета" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7);
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");

    std::cout << "установка соединения с сервером 172.16.40.1:7" << std::endl;
    if (connect(client_socket, (const struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "ошибка подключения к серверу" << std::endl;
        close(client_socket);
        return 1;
    }

    std::cout << "соединение установлено" << std::endl;

    const char* message = argv[1];
    ssize_t send_result = send(client_socket, message, strlen(message), 0);
    if (send_result == -1) {
        std::cerr << "ошибка отправки сообщения" << std::endl;
        close(client_socket);
        return 1;
    }

    std::cout << "отправленное сообщение: " << message << std::endl;
    std::cout << "отправленные байты: " << send_result << std::endl;

    char buffer[1024];
    ssize_t recv_result = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (recv_result == -1) {
        std::cerr << "ошибка приема ответа" << std::endl;
        close(client_socket);
        return 1;
    }

    buffer[recv_result] = '\0';
    std::cout << "эхо: " << buffer << std::endl;
    std::cout << "возвращённые байты: " << recv_result << std::endl;

    close(client_socket);
    std::cout << "соединение закрыто" << std::endl;
    return 0;
}

