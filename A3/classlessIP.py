''' Handling classless ip addresses'''

import ipaddress as ip
import os

def createNetwork():
    '''
    Creates a network
    '''
    net_ip = str(input('Enter class network ip: '))
    try:
        net_ip = ip.IPv4Network(net_ip)
    except Exception as e:
        print(str(e))
        return False, None
    
    return True, net_ip

def setMachineIp():
    ''' Sets machine ip 
        Returns True, custom network, machine ip if set successfully, else false
    '''

    _, custom_network = createNetwork()
    if not _ :
        print('Invalid')
        return False, None, None

    ip_in = str(input('Enter the ip of machine: '))
    try:
        ip_in = ip.IPv4Address(ip_in)
        if not ip_in in custom_network:
            raise Exception('IP not in the network')
    except Exception as e:
        print(str(e))
        return False, None, None

    interface = str(input('Enter the correct interface name: '))

    try:
        os.system('sudo ifconfig ' + interface + ' down')
        os.system('sudo ifconfig ' + interface + ' ' + str(ip_in) + ' netmask ' + str(custom_network.netmask))
        os.system('sudo ifconfig ' + interface + ' up')
    except Exception as e:
        print(str(e))
        return False, None, Noneimp

    print("Successful")
    return True, custom_network, ip_in

def pingMachine(networkId, thisIp):
	'''Returns true if successfully pinging else false'''

    other_ip = str(input('Enter ip address to be ping: '))

    try:
        other_ip = ip.IPv4Address(other_ip)
    except Exception as e:
        print(str(e))
        return False
    if not other_ip in networkId:
        print('Ip not in Network')
        return False

    try:
        if os.system('ping ' + other_ip.explode + ' -c 1') == 0:
            print('Successful, host is up')
        else:
            print('Host is down')
    except Exception as e:
        print(str(e))
        return False

    return True
    
    

