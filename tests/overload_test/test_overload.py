#!/usr/bin/python3

import sys
from server_link import ServerLink


def main():
    if len(sys.argv) != 4:
        print(sys.argv[0], "port ip number")
        exit(84)
    port = int(sys.argv[1])
    ip = str(sys.argv[2])
    nb = int(sys.argv[3])
    list_link = []
    print(port, ip, nb)
    for i in range(nb):
        new = ServerLink(ip, port, "Team1")
        new.connect()
        list_link.append(new)
    for i in list_link:
        i.disconnect()


if __name__ == "__main__":
    main()