//
// Created by kenneth on 17/9/20.
//
#include "hostsocket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../FileManagement/dirmag.h"
int server_fd, new_socket;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
void configuresock(){

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}
int execute_socket_host() {
    printf("\nInicio Host\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                             (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //AQUI Incia LA LACTURA DE IP
    printf("\nInicio Host 2\n");

    struct sockaddr_in *pV4Addr = (struct sockaddr_in *) &address;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
    printf("El ip es:");
    printf(str);
    printf("\n");
    //AQUI SE TERMINA LA LACTURA DE IP
     read(new_socket, buffer, 1024);
    printf(" El filename es: %s\n", buffer);
    check_directories();
    send(new_socket, "Confirmado", sizeof("confirmado"), 0);
    //Lee el largo de la imagen
    read(new_socket, buffer, 1024);
    int len = atoi(buffer);

    if (len <= 1024) {
        read(new_socket, buffer, len);
        FILE *fp = fopen("../Lol.png", "wb");
        fwrite(buffer, len, 1, fp);
        fclose(fp);
        close(new_socket);
        return 0;
    } else {
        FILE *fp = fopen("../Lol.png", "wb");
        while (len!=0){
            printf("lol \n");
            read(new_socket, buffer, 1024);
            len-=1024;
            fwrite(buffer, 1024, 1, fp);
            if (len<=1024){
                printf("Leyendo \n");
                read(new_socket, buffer, len);
                fwrite(buffer, len, 1, fp);
                printf("lol \n");

                printf("Se ha terminado de escribir la imagen, procediendo a clasificarla...");
//CODIOGO CLASIFICACION______________________________-

//TERMINA CODIGO CLASIFICACION_________________________
                close(new_socket);
                fclose(fp);
                return 0;
            }
        }
}
    return 0;
}