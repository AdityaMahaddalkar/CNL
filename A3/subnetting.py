'''
Used to simulate subnetwork and their creation,
and to ping to a remote machine.
Functions:
    -> To create given number of subnetworks
    -> To create the original network providing a network address
    -> To ping to a specific machine
'''
import ipaddress
from math import log
from findSubnet import *
import os

network = None


def createSubnets(network, number=1):
    '''Returns list of objects
    ipaddress.IPv4Network
    '''
    try:
        return list(network.subnets(int(log(number)/log(2))))
    except Exception as e:
        print(str(e))


def createNetwork():
    global network
    netString = str(input('Enter network id: '))
    try:
        network = ipaddress.IPv4Network(netString)
    except Exception as e:
        print(str(e))


def ping():
    global ip, network

    # get your ip address
    ip = inputIp()

    # validate ip address

    # create ipv4 object
    try:
        ip = ipaddress.IPv4Address(ip)
    except Exception as e:
        print(str(e))

    print(ip)
    # Setup network address
    createNetwork()

    # Create subnets
    subnet_list = createSubnets(network=network, number=int(
        input('Enter of subnets to create:')))

    # Print first and last address in each subnet
    for iter, subnet in enumerate(subnet_list):
        print('\nSubnet {}'.format(iter))
        print('First address = {}'.format(subnet[0]))
        print('Last address = {}'.format(subnet[-1]))

    # find the n th subnet in which your ip resides
    number = 0
    for net in subnet_list:
        # print(net[0])
        if ip in net:
            print('Your ip is in {} subnet'.format(number+1))
            break
        number += 1
    print(number)
    # try pinging an ip
    other_ip = str(input('Enter an ip address'))
    out = -1
    try:
        if not ipaddress.IPv4Address(other_ip) in subnet_list[number]:
            print('IP address is not valid in given subnet')
        else:
            out = os.system('ping ' + other_ip)
    except Exception as e:
        print(str(e))

    # Find the output
    if out == 0:
        print('Host is up')
    else:
        print('Host is down')
