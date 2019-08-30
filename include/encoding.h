//
// Created by a8398 on 2019/8/29.
//

#ifndef C_UTIL_ENCODING_H
#define C_UTIL_ENCODING_H

#ifdef __cplusplus
extern "C"{
#endif

int BufToHex(const char* buf,int len,char* hex);
int HexToBuf(const char* hex,int len,char* asc);


int Base64ToBuf(const char *in, unsigned  char *out);
int BufToBase64(const unsigned char *in, int inlen , char *out);

#endif //C_UTIL_ENCODING_H

#ifdef __cplusplus
}
#endif
