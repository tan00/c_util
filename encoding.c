//
// Created by a8398 on 2019/8/29.
//

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "encoding.h"

static char hexlowtoasc(int xxc)
{
    xxc&=0x0f;
    if (xxc<0x0a) xxc+='0';
    else xxc+=0x37;
    return (char)xxc;
}
static char hexhightoasc(int xxc)
{
    xxc&=0xf0;
    xxc = xxc>>4;
    if (xxc<0x0a) xxc+='0';
    else xxc+=0x37;
    return (char)xxc;
}
static char asctohex(char ch1,char ch2)
{
    char ch;
    if (ch1>='A') ch=(char )((ch1-0x37)<<4);
    else ch=(char)((ch1-'0')<<4);
    if (ch2>='A') ch|=ch2-0x37;
    else ch|=ch2-'0';
    return ch;
}


int BufToHex(const char* buf,int len,char* hex)
{
    int i;

    for (i=0;i<len;i++)
    {
        hex[2*i]   = hexhightoasc(buf[i]);
        hex[2*i+1] = hexlowtoasc(buf[i]);
    }

    return(len*2);
}

int HexToBuf(const char* hex,int len,char* asc)
{
    int i,j;
    if (len % 2 == 0)
        j = len / 2;
    else
        j = len / 2 + 1;

    for (i = 0; i < j; i++)
        asc[i] = asctohex(hex[2*i],hex[2*i+1]);

    return(j);
}




static const char base64digits[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define BAD     -1
static const char base64val[] = {
        BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
        BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
        BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD, 62, BAD,BAD,BAD, 63,
        52, 53, 54, 55,  56, 57, 58, 59,  60, 61,BAD,BAD, BAD,BAD,BAD,BAD,
        BAD,  0,  1,  2,   3,  4,  5,  6,   7,  8,  9, 10,  11, 12, 13, 14,
        15, 16, 17, 18,  19, 20, 21, 22,  23, 24, 25,BAD, BAD,BAD,BAD,BAD,
        BAD, 26, 27, 28,  29, 30, 31, 32,  33, 34, 35, 36,  37, 38, 39, 40,
        41, 42, 43, 44,  45, 46, 47, 48,  49, 50, 51,BAD, BAD,BAD,BAD,BAD
};

#define DECODE64(c)  (isascii(c) ? base64val[c] : BAD)


int Base64ToBuf(const char *in, unsigned char *out){
    int len = 0;
    register unsigned char digit1, digit2, digit3, digit4;

    if (in[0] == '+' && in[1] == ' ')
        in += 2;
    if (*in == '\r')
        return(0);

    do {
        digit1 = in[0];
        if (DECODE64(digit1) == BAD)
            return(-1);
        digit2 = in[1];
        if (DECODE64(digit2) == BAD)
            return(-1);
        digit3 = in[2];
        if (digit3 != '=' && DECODE64(digit3) == BAD)
            return(-1);
        digit4 = in[3];
        if (digit4 != '=' && DECODE64(digit4) == BAD)
            return(-1);
        in += 4;
        *out++ = (DECODE64(digit1) << 2) | (DECODE64(digit2) >> 4);
        ++len;
        if (digit3 != '=')
        {
            *out++ = ((DECODE64(digit2) << 4) & 0xf0) | (DECODE64(digit3) >> 2);
            ++len;
            if (digit4 != '=')
            {
                *out++ = ((DECODE64(digit3) << 6) & 0xc0) | DECODE64(digit4);
                ++len;
            }
        }
    } while (*in && *in != '\r' && digit4 != '=');

    return (len);
}

int BufToBase64(const unsigned char *in, int inlen , char *out){
    int outlen = 0;
    char *ptmp = out;

    outlen = (inlen+2)/3*4;
    if(ptmp == NULL) {
        return outlen;
    }
    for (; inlen >= 3; inlen -= 3)
    {
        *ptmp++ = base64digits[in[0] >> 2]; //取出第一个字符的前6位并找出对应的结果字符
        *ptmp++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];//将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        *ptmp++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        *ptmp++ = base64digits[in[2] & 0x3f]; //取出第三个字符的后6位并找出结果字符
        in += 3;
    }

    if (inlen > 0)
    {
        unsigned char fragment;

        *ptmp++ = base64digits[in[0] >> 2];
        fragment = (in[0] << 4) & 0x30;

        if (inlen > 1)
            fragment |= in[1] >> 4;

        *ptmp++ = base64digits[fragment];
        *ptmp++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
        *ptmp++ = '=';
    }

    *ptmp = '\0';
    return outlen;
}


