''' Accepts an ip, verifies whether it
is valid and finds the subnet
'''
import ipaddress
classIp = 'A'


def inputIp():
    ''' Inputs the ip'''
    ip = str(input('Enter ip address'))
    return ipaddress.IPv4Address(ip)


def findClass(ip='0.0.0.0'):
    ''' Finds the class of ip'''
    octets = list(map(int, ip.split('.')))
    if octets[0] in range(0, 128):
        return 'A'
    elif octets[0] in range(128, 192):
        return 'B'
    elif octets[0] in range(192, 224):
        return 'C'
    elif octets[0] in range(224, 240):
        return 'D'
    elif octets[0] in range(240, 256):
        return 'E'
    return 'Invalid'
