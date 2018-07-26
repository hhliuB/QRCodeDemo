//
//  QRCodePNG.m
//  QRCodeTest
//
//  Created by 刘欢欢 on 2018/7/3.
//  Copyright © 2018年 刘欢欢. All rights reserved.
//

#include "QRCodePNG.h"
#include "qrencode.h"
#include "writePNG.h"


char *QRCodePNGForString(char * data,char * file,int size,int level,int casesensitive)
{
    /* QR_ECLEVEL_L 容错率 0 7%，1 15%，2 25%，3 30% */
    QRcode *code = QRcode_encodeString(data, 0, level, QR_MODE_8, casesensitive); // 最后位的1位区分大小写，0为不区分大小写
    char *imgData = writePNG(code,file,size);
    
    
    return imgData;
}

