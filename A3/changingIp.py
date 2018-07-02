'''
Used to change ip and netmask of the machine.
Functions:
    -> To find the correct interface
    -> Validate the ip and netmask
    -> Change the ip address of the machine
'''

import os
import subnetting as sn
import ipaddress


def findInterface():
    '''
    Displays all the interfaces
    Returns string of interface
    '''
    os.system('ifconfig')
    print('\n\n\n')
    interface = str(input('Enter the interface you want to select: '))
    return interface


def validateIp(ip, subnet_mask):
    '''
    Validates if ip is in the subnet
    Creates and returns list of subnet objects
    '''
    temp_ip = None
    try:
        temp_ip = ipaddress.IPv4Address(ip)
    except Exception as e:
        print("Invalid IP address")
        return False, None

    # Create network address from ip and subnet_mask
    list_octets = list(map(int, ip.split('.')))
    list_octets[-1] = 0
    network_address = str('.'.join(list_octets))
    try:
        network_address = ipaddress.IPv4Network(
            '{}/{}'.format(network_address, subnet_mask))
    except Exception as e:
        print(str(e))
        return False, None

    # Create given number of subnets
    number = int(input('Enter number of subnets to be created: '))
    try:
        subnet_list = subnetting.createSubnets(
            network=network_address, number=number)
    except Exception as e:
        print(str(e))
        return False, None

    # Find which subnet your ip lies
    iterator = 1
    for subnet in subnet_list:
        if temp_ip in subnet:
            print('IP in subnet {} number {}'.format(subnet.explode, iterator))
            return True, subnet_list, subnet

    return False, None


def setInterface():
    # Get the interface from system
    interface = findInterface()

    # Input the ip address and netmask from user and validate
    ip, netmask = map(str, input('Enter ip and subnetmask:').split())
    if(not validateIp(ip, netmask)[0]):
        print('IP not acceptable')
        return False

    _, subnet_list, subnet = validateIp(ip, netmask)

    # If ip and netmask is valid, set the same on the machine
    try:
        os.system('sudo ifconfig ' + interface + ' down')
        os.system('sudo ifconfig ' + interface + ' ' + ip + ' ' + netmask)
        os.system('sudo ifconfig ' + interface + ' up')
    except Exception as e:
        print(str(e))

    # Try pinging any machine in same subnet

    other_ip = str(input('Enter the ip you want to ping: '))

    # Validate if that ip is in the subnet

    if other_ip not in subnet:
        print('This IP is not in your subnet')
        return False

    try:
        output = os.system('ping ' + other_ip)
    except Exception as e:
        print(str(e))

    if output == 0:
        print('\n\n\nHost is up')
        return True
    print('\n\n\nHost is down')
