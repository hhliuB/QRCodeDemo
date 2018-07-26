//
//  QRCodePNG.h
//  QRCodeTest
//
//  Created by 刘欢欢 on 2018/7/3.
//  Copyright © 2018年 刘欢欢. All rights reserved.
//

/*
 根据字符串生成二维码
 data：生成二维码的字符串，
 file：二维码文件存储位置，
 size：文件大小，
 level：错容率，  0 - 7%、1 - 15%、2 - 25%  3 - 30%
 casesensitive：是否区分大小写
 */
char *QRCodePNGForString(char * data,char * file,int size,int level,int casesensitive);

