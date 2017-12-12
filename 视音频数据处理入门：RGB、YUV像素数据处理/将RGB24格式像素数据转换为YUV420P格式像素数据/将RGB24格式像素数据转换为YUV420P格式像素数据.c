//
//  将RGB24格式像素数据转换为YUV420P格式像素数据.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/12.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "将RGB24格式像素数据转换为YUV420P格式像素数据.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool RGB24_TO_YUV420(unsigned char *rgbBuf,int w,int h,unsigned char *yuvBuf) {
    
    
    unsigned char *ptrY,*ptrU, *ptrV,*ptrRGB;
//    void *memset(void *s, int ch, size_t n);
//    函数解释：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。
//    memset：作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法
    memset(yuvBuf,0,w*h*3/2);
    
    ptrY = yuvBuf;
    ptrU = yuvBuf+w*h;
    ptrV = yuvBuf+w*h*5/4;
    
    unsigned char y,u,v,r,g,b;
    for (int j = 0; j<h; j++) {
        ptrRGB = rgbBuf+w*j*3;
        printf("ptrRGB==%s",ptrRGB);
        for (int i = 0; i<w; i++) {
            printf("ptrRGB=w=%s",ptrRGB);
            r = *(ptrRGB++);
            printf("ptrRGB=wr=%s",ptrRGB);
            printf("r=wr=%d",r);
            g = *(ptrRGB++);
            printf("ptrRGB=wg=%s",ptrRGB);
            printf("g=wg=%d",g);
            b = *(ptrRGB++);
            printf("ptrRGB=wb=%s",ptrRGB);
            printf("b=wb=%d",b);
        }
    }
    
    return true;
}

/**
 * Convert RGB24 file to YUV420P file
 * @param url_in  Location of Input RGB file.
 * @param w       Width of Input RGB file.
 * @param h       Height of Input RGB file.
 * @param num     Number of frames to process.
 * @param url_out Location of Output YUV file.
 */
int simplest_rgb24_to_yuv420(char *url_in,int w, int h, int num, char *url_out) {
    
    FILE *fp1 = fopen(url_in, "rb+");
    FILE *fp2 = fopen(url_out, "wb+");
    
    unsigned char* pic_rgb = (unsigned char *)malloc(w*h*3);
    unsigned char *pic_yuv420 = (unsigned char *)malloc(w*h*3/2);
    
    
    for (int i = 0; i < num; i ++) {
        
        fread(pic_rgb, 1, w*h*3, fp1);
        bool flag = RGB24_TO_YUV420(pic_rgb, w, h, pic_yuv420);
        if (!flag) {
            
        }
        fwrite(pic_yuv420, 1, w*h*3/2, fp2);
        
    }
    
    free(pic_rgb);
    free(pic_yuv420);
    fclose(fp1);
    fclose(fp2);
    
    
    return 0;
}
