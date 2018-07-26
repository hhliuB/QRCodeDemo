//
//  ViewController.m
//  QRCodeTest
//
//  Created by 刘欢欢 on 2018/6/29.
//  Copyright © 2018年 刘欢欢. All rights reserved.
//

#import "ViewController.h"

#import "QRCodePNG.h"

//#import "Generator.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    int size = 20;
  
    char *imgData = QRCodePNGForString("djkvhiakvbajdlkjndjkavkjdsajvbkadjvdavkadv", "/Users/hhliu/Desktop/writepng.png", size, 0, 1);
}



@end
