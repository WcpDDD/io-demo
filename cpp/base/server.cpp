//
// Created by chenxinpei on 5/26/22.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>

using namespace std;

int read_data(int connection_fd) {
    char buffer[1024];

    while(true) {
        ssize_t len;
        len = read(connection_fd, buffer, 1024);
        if (len == 0) {
            break;
        }
        if (len == -1) {
            return -1;
        }
        printf("接收到字节数:%d\n", len);
        usleep(3 * 1000 * 1000);
    }

    return 0;
}

int main() {
    int listen_fd, connection_fd;
    struct sockaddr_in server_addr, client_addr;

    // 创建一个stream socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    if (bind(listen_fd, (sockaddr *)(&server_addr), sizeof(server_addr)) != 0) {
        printf("bind fail\n");
        return -1;
    }
    // 设置为监听模式
    if (listen(listen_fd, 1024) != 0) {
        printf("listen fail\n");
        return -1;
    }

    printf("server start success\n");

    while (true) {
        socklen_t client_len = sizeof(client_addr);
        // 等待客户端连接
        connection_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        printf("client connected\n");
        read_data(connection_fd);
        close(connection_fd);
    }
}