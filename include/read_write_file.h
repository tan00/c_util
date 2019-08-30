//
// Created by a8398 on 2019/8/29.
//

#ifndef C_UTIL_READ_WRITE_FILE_H
#define C_UTIL_READ_WRITE_FILE_H

#ifdef __cplusplus
extern "C"{
#endif

int GetFileSize(const char* file);
int ReadFileToBuf(const char *name, unsigned char *buf, int len);
int WriteFileFromBuf(const char *name, unsigned char *buf, int len);


#endif //C_UTIL_READ_WRITE_FILE_H


#ifdef __cplusplus
}
#endif
