
/*
 *  writePNG.c
 *  QREncoder
 *
 *  Created by Rafael Vega on 9/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "writePNG.h"

#include <string.h>

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>

/* 将图片文件转换成二进制字符流*/
char * imageToDataForImageFile(char * file)
{
    
    //读二进制文件
    FILE * fp = fopen(file, "rb");//rb读二进制的
    
    char buff[50];
    char *imgData;
    
    long len = 0;
    long allLen = 0;
    long total;
    
    //获取图片大小
    fseek(fp, 0, SEEK_END);
    total = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    imgData = (char*)malloc(total);

    while ((len = fread(buff,sizeof(char),50,fp)) != 0){
        
        memcpy(imgData + allLen, buff, len);
        allLen += len;
    }
    
//    FILE * write_fp = fopen("/Users/hhliu/Desktop/writepng2.png","wb");
//    fwrite(imgData,sizeof(char),len,write_fp);
    
    fclose(fp);
    
    return imgData;
}

char * writePNG(QRcode *qrcode, char *outfile ,int size){
    static FILE *fp; // avoid clobbering by setjmp.
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;
    int margin = 4;
    
    realwidth = (qrcode->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    
    if(outfile[0] == '-' && outfile[1] == '\0') {
        fp = stdout;
    } else {
        fp = fopen(outfile, "wb");
        if(fp == NULL) {
            fprintf(stderr, "Failed to create file: %s\n", outfile);
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }
    
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL) {
        fprintf(stderr, "Failed to initialize PNG writer.\n");
        exit(EXIT_FAILURE);
    }
    
    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL) {
        fprintf(stderr, "Failed to initialize PNG write.\n");
        exit(EXIT_FAILURE);
    }
    
    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fprintf(stderr, "Failed to write PNG image.\n");
        exit(EXIT_FAILURE);
    }
    
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr,
                 realwidth, realwidth,
                 1,
                 PNG_COLOR_TYPE_GRAY,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    
    /* top margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }
    
    /* data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        bit = 7;
        memset(row, 0xff, (realwidth + 7) / 8);
        q = row;
        q += margin * size / 8;
        bit = 7 - (margin * size % 8);
        for(x=0; x<qrcode->width; x++) {
            for(xx=0; xx<size; xx++) {
                *q ^= (*p & 1) << bit;
                bit--;
                if(bit < 0) {
                    q++;
                    bit = 7;
                }
            }
            p++;
        }
        for(yy=0; yy<size; yy++) {
            png_write_row(png_ptr, row);
        }
    }
    /* bottom margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }
    
    
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    
    fclose(fp);
    free(row);
    
    char *imgData = imageToDataForImageFile(outfile);
    
    return imgData;
}

