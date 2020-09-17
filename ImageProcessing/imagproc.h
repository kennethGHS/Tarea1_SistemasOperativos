//
// Created by kenneth on 9/9/20.
//

#ifndef TAREA1_SISTEMASOPERATIVOS_IMAGPROC_H
#define TAREA1_SISTEMASOPERATIVOS_IMAGPROC_H

int processPNG(char *filename);
int processJPEG(char *filename);
int process_picture(char * filename);
int get_type(int red, int green , int blue);
int get_image_type(char* filename);
struct info_container *getInfoPicturePNG(char *filename);

#endif //TAREA1_SISTEMASOPERATIVOS_IMAGPROC_H
