//
//  yuv420_gray.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "yuv420_gray.h"
#include <stdlib.h>
#include <string.h>

int simplest_yuv420_gray(char *url, int w, int h, int num) {
    FILE *fp = fopen(url, "rb+"); //　rb+ 读写打开一个二进制文件，只允许读写数据。
    
    FILE *fp1 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/yuv420p去掉颜色（变成灰度图）/output_gray.yuv", "wb+");//wb+ 读写打开或建立一个二进制文件，允许读和写。
    
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0; i < num; i++) {
        fread(pic, 1, w*h*3/2, fp);
        
        // gray
//        如果想把YUV格式像素数据变成灰度图像，只需要将U、V分量设置成128即可。
//        这是因为U、V是图像中的经过偏置处理的色度分量。色度分量在偏置处理前的取值范围是-128至127，这时候的无色对应的是“0”值。经过偏置后色度分量取值变成了0至255，因而此时的无色对应的就是128了。
        
//        memset()函数原型是extern void *memset(void *buffer, int c, int count)        buffer：为指针或是数组,
//        c：是赋给buffer的值,
//        count：是buffer的长度.
//
//        这个函数在socket中多用于清空数组.如:原型是memset(buffer, 0, sizeof(buffer))
//        Memset 用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为‘ ’或‘/0’；
//        例:char a[100];memset(a, '/0', sizeof(a));
//         memset可以方便的清空一个结构类型的变量或数组。
        memset(pic+w*h,128,w*h/2);
        
        fwrite(pic, 1, w*h*3/2, fp1);
        
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}
