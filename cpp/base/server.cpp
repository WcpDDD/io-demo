//
// Created by chenxinpei on 5/26/22.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "iostream";

using namespace std;

int main() {
    int listenfd;
    struct sockaddr_in serveraddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(8080);

    if (bind(listenfd, (sockaddr *)(&serveraddr), sizeof(serveraddr)) != 0) {
        cout << "";
    }
}