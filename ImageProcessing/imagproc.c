//
// Created by kenneth on 9/9/20.
//
#include <string.h>
#include <png.h>
#include <malloc.h>
#include <jpeglib.h>

struct info_container {
    png_uint_32 height;
    png_uint_32 width;
};
int get_image_type(char* filename){
    int filenamesize= strlen(filename);
    char fileextension[] = {filename[filenamesize-3],filename[filenamesize-2],filename[filenamesize-1],"\0" };
    char pngExtension[] = "PNGpng";
    char jpgExtension[] = "JPGjpgJPEGjpeg";
    if(strstr(pngExtension, fileextension)!=NULL){
        return 1;
    }
    if(strstr(jpgExtension, fileextension)!=NULL){
        return 2;
    } else{
        return -1;
    }
    return -1;
}


int get_type(int red, int green, int blue) {
    printf("Los valores de entrada son rojo: %d verde: %d Azul :%d \n",red , green ,
           blue );
    if (red > blue) {
        if (red > green) {
            return 1;
        } else {
            return 3;
        }
    } else {
        if (blue > green) {
            return 2;
        }
    }
    return 3;
}

struct info_container *getInfoPicturePNG(char *filename) {
    FILE *fp = fopen(filename, "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);
    struct info_container *contenedor = malloc(sizeof(struct info_container));
    contenedor->width = png_get_image_width(png, info);
    contenedor->height = png_get_image_height(png, info);
    fclose(fp);
    return contenedor;
}

int processPNG(char *filename) {
    struct info_container *info = getInfoPicturePNG(filename);
    FILE *fp = fopen(filename, "r");
    png_structp pngptr =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
    png_init_io(pngptr, fp);

    png_bytepp rows;
    png_uint_32 height = png_get_image_height(pngptr, pnginfo);

    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);
    rows = png_get_rows(pngptr, pnginfo);

    int i = 0;
    int j = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    for (i = 0; i < info->height; i++) {
        for (j = 0; j < info->width * 3; j += 3) {
            printf("%d", rows[i][j]);
            red += rows[i][j];
            green += rows[i][j + 1];
            blue += rows[i][j + 2];
        }
        printf("\n");
    }
    fclose(fp);
    return get_type(red / (info->height * info->width), green / (info->height * info->width),
                    blue / (info->height * info->width));

}
int processJPEG(char *filename) {
    unsigned char a, r, g, b;
    int width, height;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile;        /* source file */
    JSAMPARRAY pJpegBuffer;       /* Output row buffer */
    int row_stride;       /* physical row width in output buffer */
    if ((infile = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
        return 0;
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;
    int size = width * height * 4;
    unsigned char *pDummy = malloc(size);
    unsigned char *pTest = pDummy;
    if (!pDummy) {
        printf("NO MEM FOR JPEG CONVERT!\n");
        return 0;
    }
    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++) {
            a = 0; // alpha value is not supported on jpg
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }
            *(pDummy++) = b;
            *(pDummy++) = g;
            *(pDummy++) = r;
            *(pDummy++) = a;
        }
    }
    fclose(infile);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    int red = 0;
    int blue = 0;
    int green = 0;
    for (int i = 0; i < size; i += 4) {
        red += pTest[i + 2];
        green += pTest[i + 1];
        blue += pTest[i];
    }
    free(pTest);
    printf("Los valores de salida son rojo: %d verde: %d Azul :%d \n",red / (size / 4), green / (size / 4),
           blue / (size / 4) );
    return get_type(red / (size / 4), green / (size / 4),
                    blue / (size / 4));
}
int process_picture(char * filename){
    if(get_image_type(filename) == 1){
        return processPNG(filename);
    }
    else if (get_image_type(filename) == 2){
        processJPEG(filename);
    } else{
        return -1;
    }
}