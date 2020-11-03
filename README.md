# CTF-Tools

# 用法

## build.sh
作用：编译项目
用法：修改以下代码
```c
FILE* file = fopen("./freenote2", "wb+");
system("chmod 777 ./freenote2");
```
将fopen以及system中的文件名修改为需要劫持的pwn文件名

## b2c.py 
作用：将二进制文件转为字节数组，输出为char.h文件

用法：python3 ./b2c.py ./demo

## wrapper
作用：pwn的流量劫持和保存

用法：修改源码，