//
// Created by a8398 on 2019/8/29.
//
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "read_write_file.h"

int GetFileSize(const char* file)
{
    int fp;
    fp=open(file, O_RDONLY);
    if(fp==-1) {
        return -1;
    }

    struct stat statbuff;
    if(fstat(fp, &statbuff) < 0) {
        close(fp);
        return -1;
    }
    close(fp);
    return statbuff.st_size;
}

int ReadFileToBuf(const char *name, unsigned char *buf, int len)
{
    int i=0,rcvd=0,fp=0;

    fp=open(name, O_RDONLY);
    if(fp==-1) {
        return -1;
    }

    while(rcvd<len) {
        i=read(fp,buf+rcvd,len-rcvd);
        if(i<=0) {
            break;
        }
        rcvd+=i;
    }

    close(fp);
    return rcvd;
}

int WriteFileFromBuf(const char *name, unsigned char *buf, int len){
    int i=0,rcvd=0,fp=0;

    fp=open(name, O_CREAT | O_TRUNC | O_WRONLY);
    if(fp==-1) {
        return -1;
    }

    while(rcvd<len) {
        i=write(fp,buf+rcvd,len-rcvd);
        if(i<=0) {
            break;
        }
        rcvd+=i;
    }
    close(fp);
    return rcvd;
}