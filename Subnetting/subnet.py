''' Class to demonstrate use of subnetting, changing ip of machine
    and changing subnet mask according to required number of subnets.
'''

import ipaddress
import os
from math import log2, ceil


class myIP:
    def __init__(self):
        self.ip = None
        self.net_id = None
        self.subnet_list = None

    def set_ip(self):
        '''
        Function used to set class parameters
        '''

        try:
            ip_string = str(input('Enter ip that you want to set: '))
            self.ip = ipaddress.IPv4Address(ip_string)
            list_octets = list(map(int, ip_string.split('.')))
            list_octets[-1] = 0
            temp_net_id = '.'.join(list_octets)

            netmask_map = {1: '255.0.0.0', 2: '255.255.0.0', 3: '255.255.255.0'}

            netmask = '0.0.0.0'
            if list_octets[0] in range(1, 128):
                netmask = netmask_map[1]
            elif list_octets[0] in range(128, 192):
                netmask = netmask_map[2]
            elif list_octets[0] in range(192, 224):
                netmask = netmask_map[3]
            else:
                raise Exception("Ip address not for commercial use")

            self.net_id = ipaddress.IPv4Network(temp_net_id + '/' + netmask)
            self.subnet_list = list(self.net_id.subnets())

        except Exception as e:
            print(e)
            exit()

    def change_machine_ip(self):
        ''' Input : ---
            Output : returns true if successfully set ip of machine,
                     else false
        '''
        try:

            ip_string = str(self.ip)
            interface = str(input('Enter interface: '))
            os.system('sudo ifconfig ' + interface + ' down')
            os.system('sudo ifconfig ' + interface + ' ' +
                      ip_string + ' netmask ' + str(self.net_id.netmask))
            os.system('sudo ifconfig ' + interface + ' up')
            print('Successfully set machine ip and default netmask')
            return True
        except Exception as e:
            print(str(e))
            return False

    def create_subnets(self):
        ''' Input : ---
            Output: Returns true is subnets created successfully, else false
        '''

        number_subnets = int(input('Enter how many subnets to create: '))
        print('Default netID {} and default subnet mask {}'.format(
            str(self.net_id.network_address), str(self.net_id.netmask)))

        prefix = int(list(self.net_id.split('/'))[-1])

        prefix += ceil(log2(number_subnets))

        if prefix > self.ip.max_prefixlen:
            print('Cannot create given number of subnets')
            return False
        else:
            new_net_id_string = str(self.net_id.network_address) + '/' + prefix
            try:
                new_net_id = ipaddress.IPv4Network(new_net_id_string)
                print('New netmask {}'.format(str(new_net_id.netmask)))
            except Exception as e:
                print(e)
                return False

        prefix_length = ceil(log2(number_subnets))
        self.subnet_list = list(self.net_id.subnets(prefix_length))
        return True

    def ping(self):
        ''' Input : ----
            Output : Shows ping output to required ip address
        '''

        other_ip = str(input('Enter other ip address'))

        try:
            _ = ipaddress.IPv4Address(other_ip)
        except Exception as e:
            print(e)

        # Find subnet in which our ip resides

        our_subnet = None

        for subnet_address in self.subnet_list:
            if self.ip in subnet_address:
                our_subnet = subnet_address
                break

        # Check whether other ip is in sam subnet

        if not ipaddress.IPv4Address(other_ip) in our_subnet:
            print('IP address is not in our subnet')
            return

        # If it is present

        output = -1
        try:
            output = os.system('ping ' + other_ip + ' -c 5')

        except Exception as e:
            print(e)

        if(output == 0):
            print('Successfully pinged, host is up')
        elif(output == -1):
            print('Error in pinging, try again')
        else:
            print('No route to host, host is down')
