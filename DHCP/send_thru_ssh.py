import os

try:
	print('Entering arp command')
	os.system('arp')
	ip_add = input('Enter the ip to which you want to install: ')
	os.system('scp installer.py root@' + ip + '/home/tecomp')
	os.system("sshpass -p 'tecomp' root@" + ip)
	print('Success')
except Exception as e:
	print(e)