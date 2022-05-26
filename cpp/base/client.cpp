#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

//
// Created by chenxinpei on 22-5-26.
//
int main() {
    int clienfd;
    struct sockaddr_in serveraddr;
    char *content;

    clienfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);

    if (connect(clienfd, (const sockaddr *)(&serveraddr), sizeof(serveraddr)) != 0) {
        printf("connect fail\n");
        return -1;
    }

    content = static_cast<char *>(malloc(10241));
    for (int i = 0; i < 10241; i ++) {
        if (i != 10240) {
            content[i] = 'a';
        } else {
            content[i] = '\0';
        }
    }

    ssize_t remain = strlen(content);
    while (true) {
        int len = write(clienfd, content, remain);
        if (len == -1) {
            return -1;
        }
        if (len == 0) {
            break;
        }
        remain -= len;
        content += len;
        printf("已发送:%d\n", len);
        usleep(3 * 1000 * 1000);
    }

}
