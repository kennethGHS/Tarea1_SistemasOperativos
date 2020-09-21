#include <stdio.h>
#include "SocketManagement/clientsocket.h"
#include "ImageProcessing/imagproc.h"
#include "FileManagement/dirmag.h"
#include "ConfigManagement/configproc.h"
#include <pthread.h>
#include <ifaddrs.h>
#include <string.h>
#include "SocketManagement/clientsocket.h"
#include "SocketManagement/hostsocket.h"
#include <unistd.h>

int check_file_existence(char *filepath) {
    FILE *fp;
    if ((fp = fopen(filepath, "rb")) == NULL) {
        return -1;
    } else {
        fclose(fp);
        return 1;
    }
}

void execute_client() {
    char ip[40];
    printf("Please enter an IP : \n");
    scanf("%s", ip);
    while (1 == 1) {
        char path[1000];
        printf("Please enter filepath of the png/jpg or fin to finish:\n");
        scanf("%s", path);
        if (strcmp("fin", path) == 0) {
            return;
        } else {
            if (check_file_existence(path) != 1) {
                printf("El archivo no existe\n");
                continue;
            }
            if(get_image_type(path)==-1){
                printf("El archivo no es soportado\n");
                continue;
            }
            int valid = execute_server_client(path, ip);
            if (valid == -1) {
                return execute_client();
            }
            memset(path, 0, 1000);
        }
    }
}

void execute_host() {
    configuresock();
    while (1 == 1) {
        check_directories();
        execute_socket_host();
    }
}

int main() {
    execute_client();
    return 0;
}

