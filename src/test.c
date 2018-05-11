// 全世界的ip库，都是分段的，比如有如下存储于文件的ip数据：
// 10.111.1.3    10.111.5.8    北京市海淀区           表示从10.111.1.3开始到10.111.5.8结束的ip，其对应的地域信息都是北京市海淀区。
// 这样的数据大约有几百万条。
// 设计相应的数据结构，以及数据存储方式。
// 编写根据ip查找对应地域信息的函数。
// 即：String findIpLocation(String ip) 


#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <memory.h>

#define DATA "ip.dat"	//sorted file by iprange, entry: size_t(64bit iprange)+string(64bit location)
#define ENTRY_SIZE 72
#define IP_SIZE 4
#define IPRANGE_SIZE 8
#define LOCATION_SIZE 64
#define ENTRY_COUNT 445065 

unsigned int ip2int(char *ip) {
    unsigned char a, b, c, d; 
    sscanf(ip, "%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d); 
    return (unsigned int)((a << 24) | (b << 16) | (c << 8) | d);  
}

int int2ip(char *ipString, unsigned int ip) {
    unsigned char a, b, c, d;
    a = (unsigned char)(ip >> 24 & 0x000000FF);
    b = (unsigned char)(ip >> 16 & 0x000000FF);
    c = (unsigned char)(ip >> 8 & 0x000000FF);
    d = (unsigned char)(ip & 0x000000FF);
    snprintf(ipString, 16, "%hhu.%hhu.%hhu.%hhu", a, b, c, d);
}

int main(unsigned int argc, char *argv[]) {
    FILE *fp = fopen(DATA, "rb");
    char buff[ENTRY_SIZE + 1], leftStr[16], rightStr[16];
    unsigned int left, right;
    size_t n, pos;
    do {
        n = fread(buff, ENTRY_SIZE, 1, fp);
        if (n != 1) {
            break;
        }
        pos = ftell(fp);
        buff[ENTRY_SIZE] = '\0';
        left = *((unsigned int *)buff);
        right = *((unsigned int *)&buff[IP_SIZE]);
        int2ip(leftStr, left);
        int2ip(rightStr, right);
        printf("%u: %s; %s(%u) ~ %s(%u)\n", pos, &buff[IPRANGE_SIZE], leftStr, left, rightStr, right);
    } while (n == 1);
    fclose(fp);
    return 0;
}
