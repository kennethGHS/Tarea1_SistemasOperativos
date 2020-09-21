//
// Created by kenneth on 14/9/20.
//
#include <jmorecfg.h>
#include <string.h>
#include <stdlib.h>
#include "clientinformation.h"
/**
 * Creates a client structure
 * @param ip the ip of the client
 * @param accepted if the client has a different status
 * @return the client pointer
 */
struct client* create_new_client(char * ip,boolean accepted){
    struct client* new_client = malloc(sizeof(struct client));
    new_client->accepted = accepted;
    new_client->client_ip = ip;
    new_client->next_client = NULL;
    return new_client;
}
/**
 * Destroys all clients in a list
 * @param client the head of the list
 */
void destroy_list_clients( struct client* client){
    if (client==NULL){
        return;
    }
    struct client* next = client->next_client;
    while (next!=NULL){
        free(client);
        client = next;
        next = client->next_client;
    }
}
/**
 * Adds a client to the list
 * @param list_header
 * @param new_client
 */
void add_list_clients(struct client* list_header,struct client* new_client){
    if (list_header==NULL){
        return;
    }
    while (list_header->next_client!=NULL){
        list_header = list_header->next_client;
    }
    list_header->next_client = new_client;
}
/**
 * Checks if a client has the status "accepted"
 * @param ip
 * @param list_header the start of the clients list
 * @return 1 if accepted,0 otherwise
 */
int check_if_accepted(char* ip, struct client* list_header){
    while (list_header!=NULL){
        if( (strcmp(list_header->client_ip,ip)==0 ) && list_header->accepted==TRUE){
            return 1;
        } else if ((strcmp(list_header->client_ip,ip)==0 ) && (list_header->accepted==FALSE)){
            return 0;
        }
    }
    return -1;
}


