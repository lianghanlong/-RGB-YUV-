//
//  将YUV420P像素数据的亮度减半.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "将YUV420P像素数据的亮度减半.h"
#include <stdlib.h>
/**
 * Halve Y value of YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param num     Number of frames to process.
 */

//如果打算将图像的亮度减半，只要将图像的每个像素的Y值取出来分别进行除以2的工作就可以了。图像的每个Y值占用1 Byte，取值范围是0至255，对应C语言中的unsigned char数据类型。
int simplest_yuv420_halfy(char *url, int w, int h, int num) {
    
    FILE *fp = fopen(url, "rb+");//　rb+ 读写打开一个二进制文件，只允许读写数据。
    FILE *fp1 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/将YUV420P像素数据的亮度减半/output_half.yuv", "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0; i < num; i++) {
        
        fread(pic, 1, w*h*3/2, fp);
        
        //half 将YUV数据中的亮度分量Y的数值减半的方法，降低图像的亮度
        for (int j=0; j<w*h; j++) {
            unsigned char temp = pic[j]/2;
            
            printf("temp---%d\n",temp);
            pic[j] = temp;
        }
        
        fwrite(pic, 1, w*h*3/2, fp1);
    }
    
    free(pic);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}
