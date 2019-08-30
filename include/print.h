//
// Created by a8398 on 2019/8/29.
//

#ifndef C_UTIL_PRINT_H
#define C_UTIL_PRINT_H

#ifdef __cplusplus
extern "C"{
#endif

#define LOG_EMERGE(fmt, ARGS...)	printf("[EMERGE][F:%s][L:%d]: "  fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_ALERT(fmt, ARGS...)	printf("[ALERT][F:%s][L:%d]: "  fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_CRIT(fmt, ARGS...)		printf("[CRIT][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_ERR(fmt, ARGS...)		printf("[ERR][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_WAR(fmt, ARGS...)		printf("[WAR][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_NOTICE(fmt, ARGS...)	printf("[NOTICE][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_INF(fmt, ARGS...)		printf("[INF][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)
#define LOG_DEBUG(fmt, ARGS...)	printf("[DEBUG][F:%s][L:%d]: " fmt"\n",__FUNCTION__,__LINE__, ##ARGS)

void DumpBuf(const char *tip, unsigned char *buf, int len);

#ifdef __cplusplus
}
#endif

#endif //C_UTIL_PRINT_H
