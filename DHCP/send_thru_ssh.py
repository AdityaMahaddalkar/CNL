import os

try:
	print('Entering arp command')
	os.system('arp')
	ip_add = input('Enter the ip to which you want to install: ')
	os.system('scp installer.py root@' + ip_add + ':/home/tecomp')
	os.system("ssh root@" + ip_add)
	print('Success')
except Exception as e:
	print(e)