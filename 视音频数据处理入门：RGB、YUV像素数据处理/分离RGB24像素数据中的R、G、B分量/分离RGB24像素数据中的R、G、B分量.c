//
//  分离RGB24像素数据中的R、G、B分量.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/12.
//  Copyright © 2017年 pc-570. All rights reserved.
//

#include "分离RGB24像素数据中的R、G、B分量.h"
#include <stdlib.h>
/**
 * Split R, G, B planes in RGB24 file.
 * @param url  Location of Input RGB file.
 * @param w    Width of Input RGB file.
 * @param h    Height of Input RGB file.
 * @param num  Number of frames to process.
 *
 */

//与YUV420P三个分量分开存储不同，RGB24格式的每个像素的三个分量是连续存储的。一帧宽高分别为w、h的RGB24图像一共占用w*h*3 Byte的存储空间。RGB24格式规定首先存储第一个像素的R、G、B，然后存储第二个像素的R、G、B…以此类推。类似于YUV420P的存储方式称为Planar方式，而类似于RGB24的存储方式称为Packed方式。
int simplest_rgb24_split(char *url, int w, int h, int num) {
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("", "wb+");
    FILE *fp2 = fopen("", "wb+");
    FILE *fp3 = fopen("", "wb+");
    
    unsigned char *pic = (unsigned char *)malloc(w*h*3);
    
    for (int i = 0; i < num ; i++) {
        //一帧宽高分别为w、h的RGB24图像一共占用w*h*3 Byte的存储空间
        fread(pic, 1, w*h*3, fp);
        //RGB24格式的每个像素的三个分量(R,G,B)是连续存储的
        //RGB24格式规定首先存储第一个像素的R、G、B，然后存储第二个像素的R、G、B…以此类推。
        for (int j = 0; j < w*h*3; j=j+3) {
            //R
            fwrite(pic+j, 1, 1, fp1);
            //G
            fwrite(pic+j+1, 1, 1, fp2);
            //B
            fwrite(pic+j+2, 1, 1, fp3);
        }
        
    }
    
    free(pic);
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    
    
    return 0;
}
