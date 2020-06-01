import socket
import select


class ServerLink:
    def __init__(self, hostname, port):
        print("This is the initialisation for %s and %d" % (hostname, port))
        self.hostname = hostname
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(True)
        self.read_list = [self.socket]
        self.write_list = []

    def connect(self):
        self.socket.connect((self.hostname, self.port))

    def write(self):
        data = bytes("Pouet", 'utf-8')
        assert self.socket.send(data)

    def read(self):
        data = self.socket.recv(1024)
        print(str(data.decode('utf-8')))

    def disconnect(self):
        self.socket.close()
