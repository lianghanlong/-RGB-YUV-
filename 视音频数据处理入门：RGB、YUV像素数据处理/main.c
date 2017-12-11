//
//  main.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include <stdio.h>
#include "YUV444P.h"
#include "yuv420_gray.h"
#include "将YUV420P像素数据的亮度减半.h"
#include "将YUV420P像素数据的周围加上边框.h"
#include "生成YUV420P格式的灰阶测试图.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    char *filePath = "/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/source/lena_256x256_yuv420p.yuv";
    
    //2.分离YUV444P像素数据中的Y、U、V分量
//    simplest_yuv444_split("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/source/lena_256x256_yuv444p.yuv", 256, 256, 1);
   
    //3. 将YUV420P像素数据去掉颜色（变成灰度图）
//    simplest_yuv420_gray("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/source/lena_256x256_yuv420p.yuv", 256, 256, 1);
    
    //4.将YUV420P像素数据的亮度减半
//    simplest_yuv420_halfy("/Users/admin/Desktop/HL/ffmpeg/视音频数据处理入门：RGB、YUV像素数据处理/视音频数据处理入门：RGB、YUV像素数据处理/source/lena_256x256_yuv420p.yuv", 256, 256, 1);
    
    //将YUV420P像素数据的周围加上边框
//    simplest_yuv420_border(filePath, 256, 256, 1, 1);
    
    simplest_yuv420_graybar(640, 360, 0, 255, 10, "graybar_640x360.yuv");
    return 0;
}
