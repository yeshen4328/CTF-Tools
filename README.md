# CTF-Tools
# 任务列表
+ [X] wrapper

  给pwn加层壳，流量劫持
  + [ ] prctl 限制子进程系统调用
  
+ [X] aflfuzzer

  用afl快速找pwn的漏洞(不太靠谱。。)
  honggfuzz有点效果，可以写成简单的fuzz工具
  
+ [ ] soinjector（高优先）

  流量劫持功能放到so库，给pwn添加动态链接
  

  
+ [ ] elfpatcher

  用elfpathcer给pwn添加so库
  
+ [ ] turnOnProtection（高优先）

  添加nx等保护功能
  
+ [ ] nomalPatch（高优先）

  普通patch，快速替换free、printf等函数
  
+ [ ] 种马（给自己）
  
  提升权限到shell
