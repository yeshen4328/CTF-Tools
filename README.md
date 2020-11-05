# CTF-Tools
# 任务列表
+ [x] wrapper
  给pwn加层壳，流量劫持,seccomp限制系统调用
+ [ ] soinjector
  流量劫持功能放到so库，给pwn添加动态链接
+ [x] aflfuzzer
  用afl快速找pwn的漏洞
+ [ ] elfpatcher
  用elfpathcer给pwn添加so库
+ [ ] turnOnProtection
  添加nx等保护功能，got表不可写，修改got表import函数（比如malloc改为alloc，printf改为puts）
+ [ ] nomalPatch
  普通patch，快速替换free、printf等函数
+ [ ] fridaJSscripts
  利用frida的hook特性实现
  1. 流量存储
  2. 危险函数调用参数过滤，如/bin/sh
  3. nop掉某些函数，如free
