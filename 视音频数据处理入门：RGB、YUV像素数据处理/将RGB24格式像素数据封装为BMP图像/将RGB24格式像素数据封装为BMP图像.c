//
//  将RGB24格式像素数据封装为BMP图像.c
//  视音频数据处理入门：RGB、YUV像素数据处理
//
//  Created by pc-570 on 2017/12/12.
//  Copyright © 2017年 pc-570. All rights reserved.
//

//BMP图像内部实际上存储的就是RGB数据。本程序实现了对RGB像素数据的封装处理。通过本程序中的函数，可以将RGB数据封装成为一张BMP图像。
//BMP采用的是小端（Little Endian）存储方式。这种存储方式中“RGB24”格式的像素的分量存储的先后顺序为B、G、R。由于RGB24格式存储的顺序是R、G、B，所以需要将“R”和“B”顺序作一个调换再进行存储。
#include "将RGB24格式像素数据封装为BMP图像.h"
#include <stdlib.h>

typedef struct{
    long imageSize;
    long blank;
    long startPosition;
} BmpHead;

typedef struct {
    long Length;
    long width;
    long height;
    unsigned short colotPlane;
    unsigned short bitColor;
    long zipFormat;
    long realSize;
    long xPels;
    long yPels;
    long colorUse;
    long colorImportant;
} InfoHead;

//1)将RGB数据前面加上文件头。
//2)将RGB数据中每个像素的“B”和“R”的位置互换。
//BMP文件是由BITMAPFILEHEADER、BITMAPINFOHEADER、RGB像素数据共3个部分构成，它的结构如下图所示。
/**
 * Convert RGB24 file to BMP file
 * @param rgb24path    Location of input RGB file.
 * @param w        Width of input RGB file.
 * @param h       Height of input RGB file.
 * @param bmppath      Location of Output BMP file.
 */

int simleat_rgb24_to_bmp(const char *rgb24path,int w, int h,const char *bmppath) {
    
    int i = 0,j = 0;
    BmpHead m_BMPHeader={0};
    InfoHead m_BMPInfoHeader={0};
    char bfType[2]={'B','M'};
    int header_size= sizeof(bfType)+sizeof(BmpHead)+sizeof(InfoHead);
    unsigned char *rgb24_buffer=NULL;
    FILE *fp_rgb24=NULL,*fp_bmp=NULL;
    
    if ((fp_rgb24=fopen(rgb24path, "rb+"))==NULL) {
        printf("Error: Cannot open input RGB24 file.\n");
        return -1;
    }
    
    if ((fp_bmp=fopen(bmppath, "wb+"))==NULL) {
        printf("Error: Cannot open output BMP file.\n");
        return -1;
    }
    
    rgb24_buffer=(unsigned char *)malloc(w*h*3);
    
    fread(rgb24_buffer, 1, w*h*3, fp_rgb24);
    
    m_BMPHeader.imageSize = 3*w*h+header_size;
    m_BMPHeader.startPosition=header_size;
    
    m_BMPInfoHeader.Length=sizeof(InfoHead);
    m_BMPInfoHeader.width = w;
    //BMP storage pixel data in opposite direction of Y-axis (from bottom to top).
    m_BMPInfoHeader.height = -h;
    m_BMPInfoHeader.colotPlane=1;
    m_BMPInfoHeader.bitColor=24;
    m_BMPInfoHeader.realSize=3*w*h;
    
    fwrite(bfType, 1, sizeof(bfType), fp_bmp);
    fwrite(&m_BMPHeader, 1, sizeof(m_BMPHeader), fp_bmp);
    fwrite(&m_BMPInfoHeader, 1, sizeof(m_BMPInfoHeader), fp_bmp);
    
    //BMP save R1|G1|B1,R2|G2|B2 as B1|G1|R1,B2|G2|R2
    //It saves pixel data in Little Endian
    //So we change 'R' and 'B'
    
    for (j = 0; j<h; j++) {
        for (i = 0; i<w; i++) {
            char temp=rgb24_buffer[(j*w+i)*3+2]; // B
            rgb24_buffer[(j*w+i)*3+2]=rgb24_buffer[(j*w+i)*3+0]; // R
            rgb24_buffer[(j*w+i)+0]=temp;
        }
    }
    
    fwrite(rgb24_buffer, 3*w*h, 1, fp_bmp); // fwrite(rgb24_buffer, 1, 3*w*h, fp_bmp); ???
    fclose(fp_rgb24);
    fclose(fp_bmp);
    free(rgb24_buffer);
     printf("Finish generate %s!\n",bmppath);
    
    return 0;
}

//size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
//返回值：返回实际写入的数据块数目
//（1）buffer：是一个指针，对fwrite来说，是要获取数据的地址；
//（2）size：要写入内容的单字节数；
//（3）count:要进行写入size字节的数据项的个数；
//（4）stream:目标文件指针；
//（5）返回实际写入的数据项个数count。
//说明：写入到文件的哪里？ 这个与文件的打开模式有关，如果是w+，则是从file pointer指向的地址开始写，替换掉之后的内容，文件的长度可以不变，stream的位置移动count个数；如果是a+，则从文件的末尾开始添加，文件长度加大。
//fseek对此函数有作用，但是fwrite[1]  函数写到用户空间缓冲区，并未同步到文件中，所以修改后要将内存与文件同步可以用fflush（FILE *fp）函数同步。

