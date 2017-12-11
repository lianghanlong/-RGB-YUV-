//
//  生成YUV420P格式的灰阶测试图.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/11.
//  Copyright © 2017年 pc-570. All rights reserved.
//

//本程序一方面通过灰阶测试图的亮度最小值ymin，亮度最大值ymax，灰阶数量barnum确定每一个灰度条中像素的亮度分量Y的取值。另一方面还要根据图像的宽度width和图像的高度height以及灰阶数量barnum确定每一个灰度条的宽度。有了这两方面信息之后，就可以生成相应的图片了。上述调用函数的代码运行后，会生成一个取值范围从0-255，一共包含10个灰度条的YUV420P格式的测试图。

#include "生成YUV420P格式的灰阶测试图.h"
#include <stdlib.h>

/**
 * Generate YUV420P gray scale bar.
 * @param w        Width of Output YUV file.
 * @param h        Height of Output YUV file.
 * @param ymin     Max value of Y
 * @param ymax     Min value of Y
 * @param barnum   Number of bars
 * @param url_out  Location of Output YUV file.
 */

int simplest_yuv420_graybar(int w,int h,int ymin, int ymax, int barnum, char *url_out) {
    int barW;
    float lum_inc;
    unsigned char lum_temp;
    int uv_width,uv_height;
    unsigned char *data_y = NULL;
    unsigned char *data_u = NULL;
    unsigned char *data_v = NULL;
    FILE *fp = NULL;
    int t,i,j;
    // 每一个bar的宽度
    barW = w/barnum;
    
    //bar之间的间隔
    lum_inc = ((float)(ymax-ymin)) / ((float)(barnum-1));
    
    // 除于2： y：w*h , uv：w*h/2 （？？？）
    uv_width = w / 2;
    uv_height = h / 2;
    
    data_y = (unsigned char *)malloc(w*h);
    data_u = (unsigned char *)malloc(uv_width*uv_height);
    data_v = (unsigned char *)malloc(uv_width*uv_height);
    
    // 读不到内容
    if ((fp=fopen(url_out, "wb+")) == NULL) {
        printf("Error: Cannot create file!");
        return -1;
    }
    
    // output Info
    printf("Y, U, V value from picture's left to right:\n");
    for (t = 0; t<barnum; t++) {
        lum_temp = ymin+(char)(t*lum_inc);
        
        printf("%3d, 128, 128\n",lum_temp);
//        0, 128, 128
//        28, 128, 128
//        56, 128, 128
//        85, 128, 128
//        113, 128, 128
//        141, 128, 128
//        170, 128, 128
//        198, 128, 128
//        226, 128, 128
//        255, 128, 128
    }
    
    // Gen Data
    for (j = 0; j < h; j ++) {
        for (i = 0; i < w; i ++) {
            t = i / barW;
            lum_temp = ymin+(char)(t*lum_inc);
            data_y[j*w+i] = lum_temp;
        }
    }
    
    for (j = 0; j < uv_height; j++) {
        for (i = 0; i < uv_width; i ++) {
            data_u[j*uv_width+i]=128;
            
        }
    }
    
    for (j = 0; j < uv_height; j ++) {
        for (i = 0; i < uv_width; i ++) {
            data_v[j*uv_width+i] = 128;
        }
    }
    
    fwrite(data_y, w*h, 1, fp);
    fwrite(data_u, uv_width*uv_height, 1, fp);
    fwrite(data_v, uv_width*uv_height, 1, fp);
    fclose(fp);
    free(data_y);
    free(data_u);
    free(data_v);
    
    
    return 0;
}
