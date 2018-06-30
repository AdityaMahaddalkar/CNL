#import pyping
import ipaddress
from findSubnet import *

network = None


def createSubnets(network, number=1):
    '''Returns list of objects
    ipaddress.IPv4Network
    '''
    try:
        return list(network.subnets(number))
    except Exception as e:
        print(str(e))


def createNetwork():
    global network
    netString = str(input('Enter network id: '))
    try:
        network = ipaddress.IPv4Network(netString)
    except Exception as e:
        print(str(e))


def main():
    global ip, network

    # get your ip address
    inputIp()

    # validate ip address
    validateIP(ip, findClass(ip))

    # create ipv4 object
    try:
        ip = ipaddress.IPv4Address(ip)
    except Exception as e:
        print(str(e))

    # Setup network address
    createNetwork()

    # Create subnets
    subnet_list = createSubnets(network=network, number=int(input('Enter of subnets to create:')))
    print(subnet_list)
    # find the n th subnet in which your ip resides
    number = 0
    for net in subnet_list:
        if ip in net:
            print('Your ip is in {} subnet'.format(number+1))
            break
        number += 1
    print(number)
    # try pinging an ip
    other_ip = str(input('Enter an ip address'))
    try:
        if not ipaddress.IPv4Address(other_ip) in subnet_list[number]:
            print('IP address is not valid in given subnet')
        else:
            os.system('ping ' + other_ip + ' -c 1')

    except Exception as e:
        print(str(e))


if __name__ == '__main__':
    main()
