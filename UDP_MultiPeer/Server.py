import socket
import threading
import sys

address_list = [('Aditya', '127.0.0.1')]
server_address = ('localhost', 10000)
socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket.bind(server_address)

address_client_1, address_client_2 = None, None


def get_peer_name():
    global address_client_1, address_client_2
    peer, address = socket.recvfrom(4096)
    peer = peer.decode(encoding='UTF-8')
    print(address)
    name, other_address = None, None
    for tuples in address_list:
        if tuples[1] == address:
            name = tuples[0]

    for tuples in address_list:
        if tuples[0] == peer:
            other_address = tuples[1]

    socket.sendto(bytes('{} wants to talk to you'.format(
        name), encoding='UTF-8'), other_address)
    socket.sendto(bytes('Connected', encoding='UTF-8'), address)
    address_client_1 = address
    address_client_2 = other_address


def send_from_one_two(address_sender, address_receiver):

    while True:
        message1, _ = socket.recvfrom(4096)
        socket.sendto(message1, address_receiver)


def send_from_two_one(address_sender, address_receiver):

    while True:
        message2, _ = socket.recvfrom(4096)
        socket.sendto(message2, address_receiver)


def one_way_chat_loop():

    get_peer_name()

    thread1 = threading.Thread(target=send_from_two_one, args=(
        address_client_2, address_client_1))
    thread2 = threading.Thread(target=send_from_one_two, args=(
        address_client_1, address_client_2))

    thread1.start()
    thread2.start()


def main_server_loop():

    number_of_chats = int(input('Enter number of chats to setup: '))

    main_thread_list = [threading.Thread(
        target=one_way_chat_loop, args=()) for i in range(number_of_chats)]

    for each_thread in main_thread_list:
        each_thread.start()


if __name__ == '__main__':
    main_server_loop()
