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

//data file is sorted file by iprange, entry: size_t(8bytes iprange)+string(64byte location),445065 counts
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
    return 0;
}

int findIpLocation(char *location, char *ipstr, char *dataFile) {
    unsigned int ip = ip2int(ipstr);
    printf("start finding %s(%u)\n", ipstr, ip);
    FILE *fp = fopen(dataFile, "rb");
    assert(NULL != fp);
    unsigned int l = 0;
    unsigned int r = ENTRY_COUNT - 1;
    unsigned int index = ENTRY_COUNT / 2;
    long offset;
    char buff[ENTRY_SIZE + 1], leftStr[16], rightStr[16];
    unsigned int left, right;
    for (;;) {
        offset = (long)(index * ENTRY_SIZE);
        fseek(fp, offset, SEEK_SET);
        size_t n = fread(buff, ENTRY_SIZE, 1, fp);
        left = *( (unsigned int*)buff );
        right = *( (unsigned int*)&buff[IP_SIZE] );
        int2ip(leftStr, left);
        int2ip(rightStr, right);
        if (ip < left) {    //查左半部分
            printf("index:%u, %s(%u) ~ %s(%u) <-\n", index, leftStr, left, rightStr, right);
            r = index;
            if ((index - l) == 1) {
                index = l;
            } else if (index == l) {
                close(fp);
                return 1;   //查不到
            } else {
                index = index - ( (index - l) / 2 );
            }
        } else if (ip > right) {    //查右半部分
            printf("index:%u, %s(%u) ~ %s(%u) ->\n", index, leftStr, left, rightStr, right);
            l = index;
            if ((r - index) == 1) {
                index = r;
            } else if (r == index) {
                close(fp);
                return 2; //查不到
            } else {
                index = index + ( (r - index) / 2 );
            }
        } else {    //命中
            printf("index:%u, %s(%u) ~ %s(%u) HIT!\n", index, leftStr, left, rightStr, right);
            snprintf(location, LOCATION_SIZE, "%s", &buff[IPRANGE_SIZE]);
            close(fp);
            return 0;
        }
    }
}

int main(size_t argc, char *argv[]) {
    assert(NULL != argv[1] && NULL != argv[2]);
    char location[64];
    location[63] = '\0';
    int r = findIpLocation(location, argv[1], argv[2]);
    printf("ret=%d, location=%s\n", r, location);
    return 0;
}
