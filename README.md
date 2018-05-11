# ip2location algorithm, C implemented

功能：查询给定IP的地理信息
地址库来源：https://raw.githubusercontent.com/itbdw/ip-database/master/src/qqwry.dat

# 介绍
- src/pack.php
> 将文本ip.txt转化为二进制ip.data，每个ip段＋定长的地理信息为一个entry（72字节）
- src/test.c
> 测试文件打包是否正确
- src/ip2location.c
> 从二进制ip.data中查询特定IP，ip.dat是有序的乱序分段，因此我们可以用二分查找的方式去找到给定IP所在的IP段，并查处对应地理信息


# 编译和使用

```shell
[tf@jp002 ip2location]$ ./make.sh 
[tf@jp002 ip2location]$ bin/ip2location 176.192.102.130 data/ip.dat 
start finding 176.192.102.130(2965399170)
index:222532, 202.197.123.1(3401939713) ~ 202.197.123.125(3401939837) <-
index:111266, 95.52.0.0(1597243392) ~ 95.55.255.255(1597505535) ->
index:166899, 146.71.0.0(2454126592) ~ 146.71.255.255(2454192127) ->
index:194715, 194.0.143.0(3254816512) ~ 194.0.143.255(3254816767) <-
index:180807, 185.23.204.0(3105344512) ~ 185.23.207.255(3105345535) <-
index:173853, 178.42.0.0(2989096960) ~ 178.43.255.255(2989228031) <-
index:170376, 165.87.0.0(2773942272) ~ 165.89.255.255(2774138879) ->
index:172114, 173.242.224.0(2918375424) ~ 173.243.31.255(2918391807) ->
index:172983, 175.192.0.0(2948595712) ~ 175.255.255.255(2952790015) ->
index:173418, 176.115.88.0(2960349184) ~ 176.115.95.255(2960351231) ->
index:173635, 176.227.240.0(2967728128) ~ 176.227.247.255(2967730175) <-
index:173527, 176.123.63.0(2960867072) ~ 176.123.63.255(2960867327) ->
index:173581, 176.126.60.0(2961062912) ~ 176.126.63.255(2961063935) ->
index:173608, 176.221.96.0(2967298048) ~ 176.221.127.255(2967306239) <-
index:173595, 176.206.0.0(2966290432) ~ 176.207.255.255(2966421503) <-
index:173588, 176.127.0.0(2961113088) ~ 176.127.255.255(2961178623) ->
index:173591, 176.198.0.0(2965766144) ~ 176.199.255.255(2965897215) <-
index:173590, 176.192.0.0(2965372928) ~ 176.197.255.255(2965766143) HIT!
ret=0, location=俄罗斯, CZ88.NET
```
