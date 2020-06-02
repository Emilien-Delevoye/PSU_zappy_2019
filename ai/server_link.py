import socket
from threading import Thread
import select
import sys


class ServerLink:
    def __init__(self, hostname, port, team_name):
        print("This is the initialisation for %s and %d" % (hostname, port))
        self.hostname = hostname
        self.port = port
        self.teamName = team_name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(True)
        self.test_val = 0
        self.thread_running = False
        self.thread = Thread()
        self.buffers = {"read": [], "write": []}

    def read_write(self):
        while self.thread_running is True:
            read_sckt = [self.socket]
            write_sckt = []
            if len(self.buffers["write"]) != 0:
                write_sckt.append(self.socket)
            readable, writable, useless = select.select(read_sckt, write_sckt, [], 0)
            if len(readable) != 0:
                self.buffers["read"].append(str(readable[0].recv(1024), 'utf-8'))
            if len(writable) != 0:
                writable.send(bytes(self.buffers["write"][0]))

    def connect(self):
        self.socket.connect((self.hostname, self.port))
        print("Connected to " + self.hostname + ":" + str(self.port))
        coReturn = str(self.socket.recv(1024), 'utf-8')
        if coReturn != "WELCOME\n":
            exit(84)
        self.socket.send(bytes(self.teamName + "\n", 'utf-8'))
        coReturn = str(self.socket.recv(1024), 'utf-8')
        if coReturn == "ko\n":
            print("Wrong Team name", file=sys.stderr)
            exit(84)
        else:
            print(coReturn)
        self.thread_running = True
        self.thread = Thread(target=self.read_write)
        self.thread.start()

    def write(self):
        data = bytes("Pouet", 'utf-8')
        assert self.socket.send(data)

    def read(self):
        try:
            output = self.buffers["read"][0]
            del self.buffers["read"][0]
        except IndexError:
            output = None
        return output

    def disconnect(self):
        self.thread_running = False
        self.thread.join()
        self.socket.close()
