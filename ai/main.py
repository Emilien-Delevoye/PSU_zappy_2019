#!/usr/bin/python3.7

from IA import IA
from serverLink import ServerLink, Command
import argparse
from sys import stderr
import time


def take_args():
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("-p", help="is the port number")
    parser.add_argument("-n", help="is the name of the team")
    parser.add_argument("-h", help="is the name of the machine; localhost by default")
    parser.parse_args()
    args = parser.parse_args()
    if args.h is None:
        return int(args.p), str(args.n), str("localhost")
    else:
        return int(args.p), str(args.n), str(args.h)


def main():
    port = int()
    name = str()
    hostname = str()
    x, y = 0, 0

    try:
        port, name, hostname = take_args()
        if port is None or name is None or hostname is None:
            exit(84)
    except (ValueError, TypeError):
        exit(84)
    CSLink = ServerLink(hostname, port, name)
    try:
        x, y = CSLink.connect()
    except ConnectionRefusedError:
        print("Connection failed", file=stderr)
        exit(84)

    ia = IA(CSLink, name, x, y)
    while CSLink.isAlive() and ia.run():
        # print("AI is Alive", flush=True) # FIXME
        pass

    print("Exit.", flush=True)
    CSLink.disconnect()


if __name__ == "__main__":
    main()
