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
    if (stat("/OS/R", &st) == -1) {
        mkdir("/OS/R", 0700);
    }
    if (stat("/OS/B", &st) == -1) {
        mkdir("/OS/B", 0700);
    }
    if (stat("/OS/G", &st) == -1) {
        mkdir("/OS/G", 0700);
    }
    if (stat("/OS/Not Trusted", &st) == -1) {
        mkdir("/OS/Not Trusted", 0700);
    }
    if (stat("/OS/TEMP", &st) == -1) {
        mkdir("/OS/TEMP", 0700);
    }
}
char* concat_files(char * directory,char* filename){
    char *result = malloc(strlen(filename) + strlen(directory) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, directory);
    strcat(result, filename);
    return result;
}
void move_file_directory(char *filename,int color){
    check_directories();
    char* filename_direction = concat_files("/OS/TEMP/",filename);
    if (color==1){
        char* filename_new_dir = concat_files("/OS/R/",filename);
        rename(filename_direction,filename_new_dir);
    }
    if (color==2){
        char* filename_new_dir = concat_files("/OS/B/",filename);
        rename(filename_direction,filename_new_dir);
    }
    if (color ==3){
        char* filename_new_dir = concat_files("/OS/G/",filename);
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
char* concact_dir(char * filename,int directory){
    if (directory==0){
        char *result = malloc(strlen(filename) + strlen("/OS/Not Trusted/") + 1); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(result, "/OS/Not Trusted/");
        strcat(result, filename);
        return result;
    } else{
        char *result = malloc(strlen(filename) + strlen("/OS/TEMP/") + 1); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(result, "/OS/TEMP/");
        strcat(result, filename);
        return result;
    }
}

