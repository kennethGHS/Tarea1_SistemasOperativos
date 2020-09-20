#include <stdio.h>
#include "SocketManagement/clientsocket.h"
#include "ImageProcessing/imagproc.h"
#include "FileManagement/dirmag.h"
#include "ConfigManagement/configproc.h"
#include <pthread.h>
#include <ifaddrs.h>
#include "SocketManagement/clientsocket.h"
#include "SocketManagement/hostsocket.h"
#include <unistd.h>
void * client(void * none){
    printf("\n Iniciar socket del Cliente \n");
    execute_server_client("../ejemplo.jpg","127.0.0.1");

}
void * host(void * none){
    printf("\n Iniciar socket del host \n");
    execute_socket_host();
}
void testServers()
{
    pthread_t ptid[2];
    pthread_create(&(ptid[1]), NULL, &host, NULL);

    // Creating a new thread
    pthread_create(&(ptid[0]), NULL, &client, NULL);

    // Waiting for the created thread to terminate
    pthread_join(ptid[0], NULL);
    pthread_join(ptid[1], NULL);
    sleep(1);

}

int main() {
    int testInteger=0;
    configuresock();
    while (testInteger==0){
    execute_socket_host();
    }

    return 0;
}

