//
// Created by kenneth on 9/9/20.
//

#ifndef TAREA1_SISTEMASOPERATIVOS_CLIENTSOCKET_H
#define TAREA1_SISTEMASOPERATIVOS_CLIENTSOCKET_H
struct clientdata{
    char * conectionIp;
    int port;
    char * clientip;
}ClientData;
int getclientip(struct clientdata *client);

#endif //TAREA1_SISTEMASOPERATIVOS_CLIENTSOCKET_H
