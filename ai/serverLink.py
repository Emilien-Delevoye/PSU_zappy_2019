
import socket
from threading import Thread
import select
import sys
from enum import Enum
from utils import dPrint
from termcolor import colored


class Command(Enum):
    Forward = 0,
    Right = 1,
    Left = 2,
    Look = 3,
    Inventory = 4,
    Broadcast = 5,
    Connect_nbr = 6,
    Fork = 7,
    Eject = 8,
    Take = 9,
    Set = 10,
    Incantation = 11


class ServerLink:
    def __init__(self, hostname, port, team_name):
        self.hostname = hostname
        self.port = port
        self.teamName = team_name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(True)
        self.thread_running = False
        self.thread = Thread()
        self.activeConnection = False
        self.buffers = {"read": str(), "write": bytes()}
        self.serverMsg = None
        self.debug_ = False

    def readWrite(self):
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
                dPrint(self.debug_, colored("send \"" + str(self.buffers["write"]) + "\" to server", "green"))
                tmp = self.buffers["write"]
                writable[0].send(bytes(tmp))
                self.buffers["write"] = self.buffers["write"][len(tmp):]

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
            raise ConnectionRefusedError("Wrong team name")
        self.activeConnection = True
        self.thread_running = True
        self.thread = Thread(target=self.readWrite)
        self.thread.start()

    def write(self, string):
        data = bytes(string, 'utf-8')
        self.buffers["write"] += data

    def read(self):
        if not len(self.buffers["read"]) > 0:
            return None
        if self.buffers["read"].find('\n') == -1:
            return None
        out, self.buffers["read"] = self.buffers["read"][:self.buffers["read"].find('\n')], self.buffers["read"][self.buffers["read"].find('\n') + 1:]
        return out if out != "" else None

    def disconnect(self):
        self.thread_running = False
        self.thread.join()
        self.socket.close()

    def isAlive(self):
        return self.activeConnection

    def readyToRead(self):
        if len(self.buffers["read"]) > 0:
            return True
        else:
            return False

    def sendAction(self, command, argument=""):
        str_commands = {Command.Forward: "Forward", Command.Right: "Right", Command.Left: "Left", Command.Look: "Look",
                        Command.Inventory: "Inventory", Command.Broadcast: "Broadcast",
                        Command.Connect_nbr: "Connect_nbr", Command.Fork: "Fork", Command.Eject: "Eject",
                        Command.Take: "Take", Command.Set: "Set", Command.Incantation: "Incantation"}
        if command not in Command:
            return False
        if command is not Command.Broadcast:
            self.buffers["write"] += bytes(str_commands[command] + "\n", 'utf-8')
        else:
            self.buffers["write"] += bytes(str_commands[command] + " " + argument + "\n", 'utf-8')

    def forward(self):
        self.buffers["write"] += bytes("Forward\n", 'utf-8')

    def right(self):
        self.buffers["write"] += bytes("Right\n", 'utf-8')

    def left(self):
        self.buffers["write"] += bytes("Left\n", 'utf-8')

    def look(self):
        self.buffers["write"] += bytes("Look\n", 'utf-8')

    def inventory(self):
        self.buffers["write"] += bytes("Inventory\n", 'utf-8')

    def broadcast(self, input_str):
        self.buffers["write"] += bytes("Broadcast " + input_str + "\n", 'utf-8')

    def connectNbr(self):
        self.buffers["write"] += bytes("Connect_nbr\n", 'utf-8')

    def fork(self):
        self.buffers["write"] += bytes("Fork\n", 'utf-8')

    def eject(self):
        self.buffers["write"] += bytes("Eject\n", 'utf-8')

    def eat(self):
        self.take("food")

    def take(self, obj):
        self.buffers["write"] += bytes("Take " + obj + "\n", 'utf-8')

    def set(self, obj):
        self.buffers["write"] += bytes("Set " + obj + "\n", 'utf-8')

    def incantation(self):
        self.buffers["write"] += bytes("Incantation\n", 'utf-8')

    def msgReceived(self):
        self.serverMsg = self.read()
        if self.serverMsg is None:
            return False
        dPrint(self.debug_, colored("Message Received: " + self.serverMsg, "red"))
        return True

    def isOk(self):
        assert self.serverMsg is not None, "isOk: No message received"
        if self.serverMsg == 'ok':
            return True
        return False

    def isKo(self):
        assert self.serverMsg is not None, "isKo: No message received"
        if self.serverMsg == 'ko':
            return True
        return False

    def getServerMsg(self):
        return self.serverMsg

    def clearServerMsg(self):
        assert self.serverMsg is not None, "clear: No message to clear"
        self.serverMsg = None

    def isDead(self):
        if self.serverMsg == "dead":
            return True
        return False
