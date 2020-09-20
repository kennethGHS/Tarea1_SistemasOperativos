//
// Created by kenneth on 16/9/20.
//
#include <stdio.h>
#include <stdlib.h>
#include "configproc.h"
#include <string.h>

int contains_ip(char *line);

int check_if_valid(char *ip) {
    int valid = 0;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/home/kenneth/config.config", "r");
    if (fp == NULL)
        return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, ip) != NULL) {
            char *valid = extract_ip_valid(line);
            if (valid == NULL) { return -1; }
            else if (valid[0] == '1') {
                fclose(fp);
                free(valid);
                if (line) {
                    free(line);
                }
                return 1;
            } else {
                fclose(fp);
                free(valid);
                if (line) {
                    free(line);
                }
                return 0;
            }
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }
    return -1;
}

char *extract_ip_valid(char *line) {
    int i = 0;
    int len = strlen(line);
    while (i != len) {
        if (line[i] == ':') {
            break;
        }
        i++;
    }
    if (i == len) {
        return NULL;
    }
    char *extracted_ip_validation = malloc(2);
    extracted_ip_validation[1] = '\0';
    extracted_ip_validation[0] = line[i + 1];
    return extracted_ip_validation;
}

