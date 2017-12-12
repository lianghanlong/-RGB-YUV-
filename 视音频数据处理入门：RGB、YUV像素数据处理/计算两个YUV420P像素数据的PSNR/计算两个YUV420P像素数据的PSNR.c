//
//  计算两个YUV420P像素数据的PSNR.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/12.
//  Copyright © 2017年 pc-570. All rights reserved.
//

/**
 * PSNR是最基本的视频质量评价方法。本程序中的函数可以对比两张YUV图片中亮度分量Y的PSNR
 * 经过程序计算后得到的PSNR取值为26.693。PSNR取值通常情况下都在20-50的范围内，取值越高，代表两张图像越接近，反映出受损图像质量越好。
     PSNR通常用于质量评价，就是计算受损图像与原始图像之间的差别，以此来评价受损图像的质量。
 */

#include "计算两个YUV420P像素数据的PSNR.h"
#include <stdlib.h>
#include <math.h>


/**
 * Calculate PSNR between 2 YUV420P file
 * @param url1     Location of first Input YUV file.
 * @param url2     Location of another Input YUV file.
 * @param w        Width of Input YUV file.
 * @param h        Height of Input YUV file.
 * @param num      Number of frames to process.
 */

int simplest_yuv420_psnr(char *url1, char *url2, int w, int h, int num) {
    
    FILE *fp1 = fopen(url1, "rb+");
    FILE *fp2 = fopen(url2, "rb+");
    
    //本程序中的函数可以对比两张YUV图片中亮度分量Y的PSNR,所以 是 w*h
    unsigned char* pic1 = (unsigned char *)malloc(w*h);
    unsigned char* pic2 = (unsigned char *)malloc(w*h);
    
    for (int i = 0; i < num; i ++) {
        //fread是一个函数，它从文件流中读数据，最多读取count个项，每个项size个字节，如果调用成功返回实际读取到的项个数（小于或等于count），如果不成功或读到文件末尾返回 0。
        fread(pic1, 1, w*h, fp1);
        fread(pic2, 1, w*h, fp2);
        
        double mse_sum=0,mse=0,psnr=0;
        
        for (int j = 0; j < w*h; j++) {
//            extern float pow(float x, float y);   用法：#include <math.h>   功能：计算x的y次幂。   说明：x应大于零，返回幂指数的结果。
            mse_sum += pow((double)(pic1[j]-pic2[j]), 2);
        }
        
        mse=mse_sum/(w*h);
        
        psnr = 10*log10(255.0*255.0/mse);
        
        printf("%5.3f\n",psnr);
        
//        int fseek(FILE *stream, long offset, int fromwhere);
//        函数设置文件指针stream的位置。如果执行成功，stream将指向以fromwhere（偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）为基准，偏移offset（指针偏移量）个字节的位置。如果执行失败(比如offset超过文件自身大小)，则不改变stream指向的位置。
        int flag1 = fseek(fp1, w*h/2, SEEK_CUR);
        fseek(fp2, w*h/2, SEEK_CUR);
        
        
    }
    
    free(pic1);
    free(pic2);
    
    fclose(fp1);
    fclose(fp2);
    
    
    
    return 0;
}
