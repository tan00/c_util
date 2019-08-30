#include <iostream>
#include "gtest/gtest.h"
#include "encoding.h"
#include "print.h"
#include "read_write_file.h"

using namespace std;


TEST(BufToBase64, BufToBase64_1){
    char* base64 = "ASNFZ4mrze/+3LqYdlQyEA==";
    char* hex =  "0123456789ABCDEFFEDCBA9876543210";
    char buf[128];
    int buflen = 0;
    char outBase64[128];

    buflen  = HexToBuf(hex , strlen(hex) , buf);

    ASSERT_EQ(buflen,16);
    BufToBase64((unsigned char*)buf,buflen,outBase64);

    char outBuf[128];
    int outBufLen = 0;
    outBufLen = Base64ToBuf(base64,(unsigned char*)outBuf);

    ASSERT_STREQ(outBase64, base64);
}

TEST(FileRW , FileRW_1){
    unsigned char writeBuf[1024];
    unsigned char readBuf[1024];
    memset(writeBuf , 0xff , sizeof writeBuf);
    memset(readBuf , 0 , sizeof readBuf);

    int ret =  0;
    ret = WriteFileFromBuf("test_file", writeBuf , sizeof writeBuf);
    ASSERT_EQ(ret,sizeof writeBuf);


    ret = ReadFileToBuf("test_file", readBuf , sizeof readBuf);
    ASSERT_EQ(ret,sizeof readBuf);

    ASSERT_EQ( memcmp(writeBuf , readBuf ,  sizeof writeBuf )  , 0);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}