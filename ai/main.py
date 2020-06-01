from server_link import ServerLink
import argparse


def take_args():
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("-p", help="is the port number")
    parser.add_argument("-n", help="is the name of the team")
    parser.add_argument("-h", help="is the name of the machine; localhost by default")
    parser.parse_args()
    args = parser.parse_args()
    return int(args.p), str(args.n), str(args.h)


def main():
    port = int()
    name = str()
    hostname = str()
    try:
        port, name, hostname = take_args()
    except (ValueError, TypeError):
        exit(84)
    if port is None or name is None or hostname is None:
        exit(84)
    newClient = ServerLink(hostname, port)


if __name__ == "__main__":
    main()
