import os

try:
    os.system('ssh root@192.168.1.1 yum install nasm -y')
except Exception as e:
    print(e)
