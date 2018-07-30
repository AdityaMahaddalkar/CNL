import os

try:
	os.system('yum install nasm -y')
except Exception as e:
	print(e)