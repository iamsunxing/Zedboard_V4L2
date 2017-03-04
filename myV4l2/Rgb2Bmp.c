
#include <stdio.h>
#include <stdlib.h>
//#include <jpeglib.h>

typedef int LONG;
typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct {
        WORD    bfType;
        DWORD   bfSize;
        DWORD   bfReserved;
        DWORD   bfOffBits;
} BMPFILEHEADER_T;

typedef struct{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BMPINFOHEADER_T;

void Rgb2Bmp(unsigned char * pdata, char * bmp_file, int width, int height )
{      //分别为rgb数据，要保存的bmp文件名，图片长宽
       BMPFILEHEADER_T bfh;
       BMPINFOHEADER_T bih;
       FILE * fp = NULL;
       
       bih.biSize = 40;
       bih.biWidth = width;
       bih.biHeight = height;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了
       bih.biPlanes = 1;//为1，不用改
       bih.biBitCount = 24;
       bih.biCompression = 0;//不压缩
       bih.biSizeImage = width*height*3;
       bih.biXPelsPerMeter = 0 ;//像素每米
       bih.biYPelsPerMeter = 0 ;
       bih.biClrUsed = 0;//已用过的颜色，24位的为0
       bih.biClrImportant = 0;//每个像素都重要
       
       bfh.bfType = 0x4d42;  //bm
       bfh.bfSize = 54 + width*height*3;       
       bfh.bfReserved = 0; 
	   bfh.bfOffBits = 54;
       
       fp = fopen( bmp_file,"wb" );
       if(!fp) 
       {
       		printf("open %s failed in %s,line number is %d",bmp_file,__FILE__,__LINE__);
       		perror("");
       		return;
	   }
/*
不能用 fwrite(&bfh,14,1,fp); 代替以下四行，否则会出错
因为linux上是4字节对齐，14不是4的倍数，所以分若干次写入
*/
       fwrite(&bfh.bfType,2,1,fp);
       fwrite(&bfh.bfSize,4,1,fp);
       fwrite(&bfh.bfReserved,4,1,fp); 
       fwrite(&bfh.bfOffBits ,4,1,fp);
       
       fwrite(&bih, 40,1,fp);
       fwrite(pdata,bih.biSizeImage,1,fp);
       fclose(fp);
       
}

