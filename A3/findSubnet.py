''' Accepts an ip, verifies whether it
is valid and finds the subnet
'''
ip = '0.0.0.0'
classIp = 'A'
subnets = {'A': '255.0.0.0', 'B': '255.255.0.0',
           'C': '255.255.255.0', 'D': '255.255.255.255', 'E': 'Invalid'}


def validateIP(ip='0.0.0.0', classIP='A'):
    ''' Validates ip range as well as class'''
    octets = list(map(int, ip.split('.')))
    for number in octets:
        if not number in range(0, 256):
            return False

    if not octets[0] in range(0, 128) and classIP == 'A':
        return False

    if not octets[0] in range(128, 192) and classIP == 'B':
        return False

    if not octets[0] in range(192, 224) and classIP == 'C':
        return False

    if not octets[0] in range(224, 240) and classIP == 'D':
        return False

    if not octets[0] in range(240, 256) and classIP == 'E':
        return False

    return True


def inputIp():
    ''' Inputs the ip'''
    global ip
    ip = str(input('Enter the ip: '))
    global classIp
    classIp = findClass(ip)
    if classIp == 'Invalid':
        print('Invalid ip address')
        return
    if not validateIP(ip, classIp):
        print('Invalid ip address')
        return
    else:
        print('Valid ip')
    return


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
