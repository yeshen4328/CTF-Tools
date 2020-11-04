from pwn import *
import os


#p = remote(ip, port)
#没有开启ASLR
p = process('./')
def parse(file):
    f = open(file,'rb')
    for line in f.readlines():
        pos = line.find(b'##input##')
        payload = line[pos+9:]
        p.send(payload)
        

def forward():
   
    files = os.listdir('./')
    for file in files:
        if(file.startswith('a_log')):
            parse(file)

if __name__ == '__main__':
    forward()
