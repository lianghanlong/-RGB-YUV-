//
//  YUV444P.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "YUV444P.h"
#include <stdlib.h>

//如果视频帧的宽和高分别为w和h，那么一帧YUV444P像素数据一共占用w*h*3 Byte的数据。其中前w*h Byte存储Y，接着的w*h Byte存储U，最后w*h Byte存储V。上述调用函数的代码运行后，将会把一张分辨率为256x256的名称为lena_256x256_yuv444p.yuv的YUV444P格式的像素数据文件分离成为三个文件：
//output_444_y.y：纯Y数据，分辨率为256x256。
//output_444_u.y：纯U数据，分辨率为256x256。
//output_444_v.y：纯V数据，分辨率为256x256。
int simplest_yuv444_split(char *url,int w,int h, int num) {
    FILE *fp = fopen(url, "rb+"); //rb+ 读写打开一个二进制文件，只允许读写数据。
    FILE *fp1 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/yuv444p/output_444_y.y", "wb+");//wb+ 读写打开或建立一个二进制文件，允许读和写。
    FILE *fp2 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/yuv444p/output_444_u.y", "wb+");
    FILE *fp3 = fopen("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/yuv444p/output_444_v.y", "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3);
    
    for (int i = 0; i < num; i ++) {
        fread(pic, 1, w*h, fp);
        //y
        fwrite(pic, 1, w*h, fp1);
        //u
        fwrite(pic+w*h, 1, w*h, fp2);
        
        //v
        fwrite(pic+w*h*2, 1, w*h, fp3);
    }
    
    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    
    return 0;
}
