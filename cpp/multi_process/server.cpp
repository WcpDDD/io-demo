#include <netinet/in.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

//
// Created by chenxinpei on 22-5-26.
//
int child_process(int connection_fd) {
    printf("子进程处理中");
}

int main() {
    int listen_fd;
    struct sockaddr_in server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    if (bind(listen_fd, reinterpret_cast<const sockaddr *>(&server_addr),
             sizeof(server_addr)) != 0) {
        printf("bind fail");
        return -1;
    }
    if (listen(listen_fd, 1024) != 0) {
        printf("listen fail");
        return -1;
    }

    while(true) {
        struct sockaddr_in connection_addr;
        socklen_t len;

        len = sizeof(connection_addr);
        int connection_fd = accept(listen_fd, reinterpret_cast<sockaddr *>(&connection_addr), &len);

        if (connection_fd == -1) {
            return -1;
        }

        if (fork() == 0) {
            close(listen_fd);
            child_process(connection_fd);
            return 0;
        } else {
            close(connection_fd);
        }
    }
}
