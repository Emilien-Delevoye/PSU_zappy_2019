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
        self.thread_running = False
        self.thread = Thread()
        self.activeConnection = False
        self.buffers = {"read": str(), "write": bytes()}

    def read_write(self):
        while self.thread_running is True:
            read_sckt = [self.socket]
            write_sckt = []
            if len(self.buffers["write"]) != 0:
                write_sckt.append(self.socket)
            readable, writable, useless = select.select(read_sckt, write_sckt, [], 0)
            if len(readable) != 0:
                buf = str(readable[0].recv(1024), 'utf-8')
                if len(buf) == 0:
                    self.activeConnection = False
                    exit(0)
                self.buffers["read"] += buf
            if len(writable) != 0 and len(self.buffers["write"]) != 0:
                writable[0].send(bytes(self.buffers["write"]))
                self.buffers["write"] = bytes()

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
        self.activeConnection = True
        self.thread_running = True
        self.thread = Thread(target=self.read_write)
        self.thread.start()

    def write(self, string):
        data = bytes(string, 'utf-8')
        self.buffers["write"] += data

    def read(self):
        if len(self.buffers["read"]) > 0:
            output = ""
            for i in self.buffers["read"]:
                if i == '\n':
                    output += i
                    break
                output += i
            for i in output:
                if i == '\n':
                    self.buffers["read"] = self.buffers["read"][len(output):]
                    return output
            return None
        else:
            return None

    def disconnect(self):
        self.thread_running = False
        self.thread.join()
        self.socket.close()

    def is_alive(self):
        return self.activeConnection

    def ready_to_read(self):
        if len(self.buffers["read"]) > 0:
            return True
        else:
            return False
