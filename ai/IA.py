
from utils import dPrint
import numpy as np
from enum import Enum


class GameObj(Enum):
    Empty = 1 << 0,
    Player = 1 << 1,
    Food = 1 << 2,
    Linemate = 1 << 3,
    Deraumere = 1 << 4,
    Sibur = 1 << 5,
    Mendiane = 1 << 6,
    Phiras = 1 << 7,
    Thystame = 1 << 8,


links = {
    'empty': GameObj.Empty,
    'player': GameObj.Player,
    'food': GameObj.Food,
    'linemate': GameObj.Linemate,
    'deraumere': GameObj.Deraumere,
    'sibur': GameObj.Sibur,
    'mendiane': GameObj.Mendiane,
    'phiras': GameObj.Phiras,
    'thystame': GameObj.Thystame
}


class IA:
    def __init__(self, CSLink):
        self.level_ = 1
        self.around_ = np.array([np.nan])
        self.CSLink_ = CSLink
        self.debug_ = True
        self.inventory_ = {GameObj.Food: 10,
                           GameObj.Linemate: 0,
                           GameObj.Deraumere: 0,
                           GameObj.Sibur: 0,
                           GameObj.Mendiane: 0,
                           GameObj.Phiras: 0,
                           GameObj.Thystame: 0}

    def lookAround(self):
        self.CSLink_.look()
        while self.CSLink_.msgReceived() is False:
            pass
        msg = self.CSLink_.getServerMsg()
        self.CSLink_.clearServerMsg()
        # Parse Look Around
        self.around_ = [[links[e] for e in list(filter(lambda x: True if x.replace(' ', '') is not None and x.replace(' ', '') != '' else False, i.split(' ')))] for i in msg.replace('[', '').replace(']', '').split(',')]
        dPrint(self.debug_, self.around_)

    def updateInv(self):
        self.CSLink_.inventory()
        while self.CSLink_.msgReceived() is False:
            pass
        msg = self.CSLink_.getServerMsg()
        self.CSLink_.clearServerMsg()
        # Parse Inventory
        self.inventory_ = {links[v[0]]: int(v[1]) for v in [list(filter(lambda x: True if x != '' and x != ' ' else False, i.split(' '))) for i in msg.replace('[', '').replace(']', '').split(',')]}

        dPrint(self.debug_, msg)
        dPrint(self.inventory_, self.inventory_)

    def run(self):
        self.updateInv()
        return True
