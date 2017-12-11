//
//  将YUV420P像素数据的周围加上边框.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "将YUV420P像素数据的周围加上边框.h"
#include <stdlib.h>

/**
 * Add border for YUV420P file
 * @param url     Location of Input YUV file.
 * @param w       Width of Input YUV file.
 * @param h       Height of Input YUV file.
 * @param border  Width of Border.
 * @param num     Number of frames to process.
 */

//图像的边框的宽度为border，本程序将距离图像边缘border范围内的像素的亮度分量Y的取值设置成了亮度最大值255。
int simplest_yuv420_border(char *url, int w, int h, int border, int num) {
    
    FILE *fp = fopen(url, "rb+"); //rb+ 读写打开一个二进制文件，只允许读写数据。
    FILE *fp1 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/将YUV420P像素数据的周围加上边框/output_border.yuv", "wb+"); //　wb+ 读写打开或建立一个二进制文件，允许读和写。
    
    // 初始化一个 w*h*3/2 的内存空间
    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);
    
    for (int i = 0 ; i < num; i ++) {
        
//        size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
//        参 数
//        buffer
//        用于接收数据的内存地址
//        size
//        要读的每个数据项的字节数，单位是字节
//        count
//        要读count个数据项，每个数据项size个字节.
//        stream
//        输入流
        fread(pic, 1, w*h*3/2, fp);
        
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k ++) {
                if (k<border || k > (w-1-border) || j<border || j>(h-1-border)) {
                    pic[j*w+k] = 255;
                }
            }
        }
        
//        size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
//        返回值：返回实际写入的数据块数目
//        （1）buffer：是一个指针，对fwrite来说，是要获取数据的地址；
//        （2）size：要写入内容的单字节数；
//        （3）count:要进行写入size字节的数据项的个数；
//        （4）stream:目标文件指针；
//        （5）返回实际写入的数据项个数count。
        
        fwrite(pic, 1, w*h*3/2, fp1);
    }
    
    free(pic);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}
