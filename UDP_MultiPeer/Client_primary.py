import socket
import threading
import sys


server_address = ('localhost', 10000)
socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
other_name = None


def initiate_chat():
    socket.sendto('Start', server_address)

def send_message():

    while True:

        message_out = bytes(input(), encoding='UTF-8')
        socket.sendto(message_out, server_address)


def receive_message():
    global other_name

    while True:
        message_in, _ = socket.recvfrom(4096)

        print('{} : {}'.format(other_name,
                               message_in.decode(encoding='UTF-8')))


def main_client_loop():

    other_name = str(input('Enter name to connect: '))

    socket.sendto(bytes(other_name, encoding='UTF-8'), server_address)

    thread1 = threading.Thread(target=send_message, args=())
    thread2 = threading.Thread(target=receive_message, args=())

    thread1.start()
    thread2.start()


if __name__ == '__main__':
    main_client_loop()
