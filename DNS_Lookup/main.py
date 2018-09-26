
import socket


class DNS:

    def __init__(self):
        pass

    def ip_to_url(self, ip):
        try:
            output = socket.gethostbyaddr(ip)
            print('URL: {}'.format(output[0]))
            print('Alias list: {}'.format(output[1]))
        except Exception as e:
            print(e)

    def url_to_ip(self, url):
        try:
            output = socket.gethostbyname(url)
            print('IP associated : {}'.format(output))
        except Exception as e:
            print(e)


if __name__ == '__main__':
    dns = DNS()
    c = 'y'
    while c.lower() != 'n':
        print('1. IP -> URL\n2. URL -> IP')
        option = int(input('>'))
        if option == 1:
            dns.ip_to_url(input('IP:'))
        elif option == 2:
            dns.url_to_ip(input('URL:'))
        else:
            print('Invalid')
        c = input('Repeat(y/n):')
