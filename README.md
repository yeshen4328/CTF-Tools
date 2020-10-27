# CTF-Tools
# 任务列表
+ [X] wrapper

  给pwn加层壳，流量劫持
  + [ ] prctl 限制子进程系统调用
  
+ [ ] aflfuzzer

  用afl快速找pwn的漏洞
  
+ [ ] soinjector（高优先）

  流量劫持功能放到so库，给pwn添加动态链接
  

  
+ [ ] elfpatcher

  用elfpathcer给pwn添加so库
  
+ [ ] turnOnProtection（高优先）

  添加nx等保护功能
  
+ [ ] nomalPatch（高优先）

  普通patch，快速替换free、printf等函数
