import socket
import sys
import threading

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


server_address = ('localhost', 5000)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)


global data
global address


def get_message():
    global address
    while True:

        data, address = sock.recvfrom(4096)
        print('\n>From {} : message: {}'.format(
            address, data.decode(encoding='UTF-8')))
        sys.stdout.flush()
        sys.stdin.flush()


def send_message():
    while True:

        message = bytes(input(), encoding='UTF-8')
        sock.sendto(message, address)
        sys.stdout.flush()
        sys.stdin.flush()


def main():
    thread1 = threading.Thread(target=get_message, args=())
    thread2 = threading.Thread(target=send_message, args=())

    thread1.start()
    thread2.start()


if __name__ == '__main__':
    main()

'''

while True:
	data, address = sock.recvfrom(4096)

	if data:
		print(data.decode(encoding='UTF-8'))

	message = bytes(str(input('Enter your msg: ')), 'UTF-8')
	sock.sendto(message, address)
'''
