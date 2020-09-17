//
// Created by kenneth on 14/9/20.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "dirmag.h"
void check_directories(){
    struct stat st = {0};
    if (stat("../RED", &st) == -1) {
        mkdir("../RED", 0700);
    }
    if (stat("../BLUE", &st) == -1) {
        mkdir("../BLUE", 0700);
    }
    if (stat("../GREEN", &st) == -1) {
        mkdir("../GREEN", 0700);
    }
    if (stat("../INVALID", &st) == -1) {
        mkdir("../INVALID", 0700);
    }
    if (stat("../TEMP", &st) == -1) {
        mkdir("../TEMP", 0700);
    }
}
void move_file_directory(char *filename,int color){
    check_directories();
    char* filename_direction = strcat("../TEMP/",filename);
    if (color==1){
        char* filename_new_dir = strcat("../RED/",filename);
        rename(filename_direction,filename_new_dir);
    }
    if (color==2){
        char* filename_new_dir = strcat("../BLUE/",filename);
        rename(filename_direction,filename_new_dir);
    }
    if (color ==3){
        char* filename_new_dir = strcat("../GREEN/",filename);
        rename(filename_direction,filename_new_dir);
    }

}
int get_last_index(char *file_directory){
    int filename_size= strlen(file_directory);
    int last_slash_index = -1;
    for (int i = 0; i < filename_size; ++i) {
        if(file_directory[i]=='/' || file_directory[i]=='\\'){
            last_slash_index = i;
        }
    }
    return last_slash_index;

}
char* get_file_name(char *file_directory){
    int last_slash_index = get_last_index( file_directory);
    int size_filename = sizeof(char)*(strlen(file_directory) - last_slash_index+1);
    char *filename = malloc(size_filename);
    filename[size_filename-1] = '\0';
    last_slash_index+=1;
    int i = 0;
    while (i<size_filename){
        filename[i] = file_directory[last_slash_index+i];
        i++;
    }
    return filename;
}

