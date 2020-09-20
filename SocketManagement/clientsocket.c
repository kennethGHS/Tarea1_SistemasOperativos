//
// Created by kenneth on 9/9/20.
//
#include "clientsocket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int execute_server_client( char* filename,char* ip){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    //"127.0.0.1"
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    //Envia el filename

    send(sock , filename , strlen(filename)+1 , 0 );
    printf("FilenameSend\n");
    //Lee la confirmacion
    valread = read( sock , buffer, 1024);

    printf("%s\n",buffer );
    FILE * fp = fopen(filename,"rb");
    //Ocupo ver el filesize sea mayor a 1024
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    //convierto el int a un string para enviarlo
    char str_num[50];
    sprintf(str_num, "%d", sz);
    send(sock,str_num,strlen(str_num)+1,0);
    if (sz<=1024){
        fread(buffer,sz,1,fp);
        send(sock,buffer,sz,0);
        return 0;
    } else{
        while (sz!=0){
            fread(buffer,1024,1,fp);
            sz-=1024;
            send(sock,buffer,1024,0);
            if (sz<=1024){
                fread(buffer,sz,1,fp);
                send(sock,buffer,sz,0);
                printf("Se ha terminado de enviar la imagen\n");
                printf(buffer);
                fclose(fp);
                close(sock);
                return 0;
            }
        }

    }
    printf("Se ha terminado de enviar la imagen \n");
    return 0;
}