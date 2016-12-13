//
// Created by wxy on 2016/12/13.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "com_example_wxy_hellondk_MainActivity.h"


static char Base64Code[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
                            'U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                            'o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7',
                            '8','9','+','/','=','\0'};

/*编码*/
char* encode(char *buf,int length)
{
    char* enbuf,*p;
    p=enbuf=malloc((length%3==0?length/3*4:(length/3+1)*4)*sizeof(char));
    int i;
    char b1,b2,b3,temp;/*辅助变量*/
    /*3字节一次进行解码，没有满足3字节用0补充*/
    for (i=0;i<length;i=i+3){
        b1=buf[i];
        *(p++)=Base64Code[((b1>>2)&0x3f)];
        b2=(i+1)>=length?0:buf[i+1];
        *(p++)=Base64Code[(((b1<<4)&0x3f)+((b2>>4)&0xf))];
        b3=(i+2)>=length?0:buf[i+2];
        /*补充的用code码表中的64位代替，就是=*/
        temp=b2==0?64:(((b2<<2)&0x3f)+((b3>>6)&0x3));
        *(p++)=Base64Code[temp];
        *(p++)=Base64Code[b3==0?64:(b3&0x3f)];
    }
    *(p)='\0';/*字符串结尾*/
    return enbuf;
}
/*取码表索引*/
char getIndex(char c,char* buf)
{
    int i;
    for (i=0;i<strlen(buf);++i){
        if (c==buf[i]){return i;}
    }
    return 0;
}
/*解码*/
char* decode(char* buf,int length)
{
    char b1,b2,b3,b4;
    int i;
    char* debuf,*p;
    p=debuf=malloc((length/4*3)*sizeof(char));
    /*4字节进行解码*/
    for (i=0;i<length;i=i+4){
        b1=getIndex(buf[i],Base64Code);
        b2=getIndex(buf[i+1],Base64Code);
        b3=getIndex(buf[i+2],Base64Code);
        b4=getIndex(buf[i+3],Base64Code);
        *(p++)=((b1<<2)+((b2>>4)&0x3));
        /*64对应=号，表示原字节空*/
        if (b3!=64){
            *(p++)=((b2&0x0f)<<4)+((b3>>2)&0xf);
            if (b4!=64){
                *(p++)=((b3<<6)+b4);
            }
        }
    }
    *(p)='\0';
    return debuf;
}
JNIEXPORT jbyteArray JNICALL Java_com_example_wxy_hellondk_MainActivity_encryptBase64
        (JNIEnv *env, jobject obj, jbyteArray array){
    jbyte * buf;
    /*获取字节数组*/
    buf=(*env)->GetByteArrayElements(env,array,NULL);
    /*GetArrayLength 取数组长度*/
    char* enbuf=encode((char*)buf,(*env)->GetArrayLength(env,array));
    printf("%s\n",enbuf);
    /*new一个字节数组*/
    jbyteArray enarray=(*env)->NewByteArray(env,strlen(enbuf));
    (*env)->SetByteArrayRegion(env,enarray,0,strlen(enbuf),(jbyte*)enbuf);
    return enarray;

}

JNIEXPORT jbyteArray JNICALL Java_com_example_wxy_hellondk_MainActivity_decryptBase64
        (JNIEnv *env, jobject obj, jbyteArray array){
    jbyte * buf;
    buf=(*env)->GetByteArrayElements(env,array,NULL);
    /*解码*/
    char* debuf=decode((char*)buf,(*env)->GetArrayLength(env,array));
    jbyteArray dearray=(*env)->NewByteArray(env,strlen(debuf));
    (*env)->SetByteArrayRegion(env,dearray,0,strlen(debuf),(jbyte*)debuf);
    return dearray;

}