//
// Created by kenneth on 14/9/20.
//

#ifndef TAREA1_SISTEMASOPERATIVOS_CLIENTINFORMATION_H
#define TAREA1_SISTEMASOPERATIVOS_CLIENTINFORMATION_H
struct client * create_new_client();
void destroy_list_clients( struct client* client);
struct client {
    struct client * next_client ;
    char * client_ip;
    boolean accepted;
};
void add_list_clients(struct client* list_header,struct client* new_client);
int check_if_accepted(char* ip, struct client* list_header);
#endif //TAREA1_SISTEMASOPERATIVOS_CLIENTINFORMATION_H
