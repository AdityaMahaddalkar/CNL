import socket
import threading
import sys

server_address = ('localhost', 10000)
socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket.bind(server_address)

chat_list = []


def initialize_chat(chat_list):
    peer_name1, address1 = socket.recvfrom(4096)
    peer_name2, address2 = socket.recvfrom(4096)
    chat_list.append((address1, address2))


def send_from_one_two(address_sender, address_receiver):

    while True:
        message1, _ = socket.recvfrom(4096)
        socket.sendto(message1, address_receiver)


def send_from_two_one(address_sender, address_receiver):

    while True:
        message2, _ = socket.recvfrom(4096)
        socket.sendto(message2, address_receiver)


def one_way_chat_loop():
    global chat_list
    initialize_chat(chat_list)

    thread1 = threading.Thread(target=send_from_two_one, args=(
        chat_list[0][0], chat_list[0][1]))
    thread2 = threading.Thread(target=send_from_one_two, args=(
        chat_list[0][1], chat_list[0][0]))

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
