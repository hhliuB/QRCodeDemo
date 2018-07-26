# QRCodeDemo
   使用qrcode库生成二维码图片，并用libpng进行处理，生成图片文件保存本地<br>
   qrcode库和libpng库都是C语言源码
   
   /*
     根据字符串生成二维码<br>
     data：生成二维码的字符串，<br>
     file：二维码文件存储位置，<br>
     size：文件大小，<br>
     level：错容率，  0 - 7%、1 - 15%、2 - 25%  3 - 30%<br>
     casesensitive：是否区分大小写<br>
 */<br><br>
char *QRCodePNGForString(char * data,char * file,int size,int level,int casesensitive);<br>

