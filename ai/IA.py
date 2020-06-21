
import itertools
from enum import Enum
from random import randrange

from termcolor import colored

from ai.serverLink import Command
from ai.utils import dPrint, Colors
import time

# TODO gérer les ejects

# FIXME retirer les assert à la fin

# TODO gérer si qqun attend une ia qui finnalement ne vient pas
# TODO vérifier qu'on clear bien les ids qu'on a trouvé au bon moment
# TODO considérer que tout peut fail si on se fait emmerder (A vérifier)

# TODO Brouiller les communications des autres


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


elevPlayers = {1: 1, 2: 2, 3: 2, 4: 4, 5: 4, 6: 6, 7: 6, 8: 1}

elevRqrmts = {
    1: {GameObj.Linemate: 1, GameObj.Deraumere: 0, GameObj.Sibur: 0, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0},
    2: {GameObj.Linemate: 1, GameObj.Deraumere: 1, GameObj.Sibur: 1, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0},
    3: {GameObj.Linemate: 2, GameObj.Deraumere: 0, GameObj.Sibur: 1, GameObj.Mendiane: 0, GameObj.Phiras: 2, GameObj.Thystame: 0},
    4: {GameObj.Linemate: 1, GameObj.Deraumere: 1, GameObj.Sibur: 2, GameObj.Mendiane: 0, GameObj.Phiras: 1, GameObj.Thystame: 0},
    5: {GameObj.Linemate: 1, GameObj.Deraumere: 2, GameObj.Sibur: 1, GameObj.Mendiane: 3, GameObj.Phiras: 0, GameObj.Thystame: 0},
    6: {GameObj.Linemate: 1, GameObj.Deraumere: 2, GameObj.Sibur: 3, GameObj.Mendiane: 0, GameObj.Phiras: 1, GameObj.Thystame: 0},
    7: {GameObj.Linemate: 2, GameObj.Deraumere: 2, GameObj.Sibur: 2, GameObj.Mendiane: 2, GameObj.Phiras: 2, GameObj.Thystame: 1},
    8: {GameObj.Linemate: 0, GameObj.Deraumere: 0, GameObj.Sibur: 0, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0}
}

keys = [i for i in range(1, 8)]
values = [sum([i for v, i in elevRqrmts[e].items()]) for e in keys]
elevTotalStones = dict(zip(keys, values))

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

linksR = {v: k for k, v in links.items()}


dirs = {
    1: [],
    2: [],
    8: [],
    3: ["left"],
    4: ["left"],
    7: ["right"],
    6: ["right"],
    5: ["right", "right"]
}


def setRequestToStr(invs):
    return '|'.join([str(i) + ':' + invToStr(j) for i, j in invs.items()])


def strToSetRequest(invs):
    return {int(i.split(':')[0]): strToinv(i.split(':')[1]) for i in invs.split('|')}


def invToStr(inv):
    return '-'.join([str(v)[len('GameObj.'):]+'='+str(val) for v, val in inv.items()])


def strToinv(inv):
    return {links[v.split('=')[0].lower()]: int(v.split('=')[1]) for v in inv.split('-')}


def lIDsToStr(l):
    return '+'.join([str(i) for i in l])


def strTolIDs(l):
    return [int(i) for i in l.split('+')]


def rand():
    return randrange(0, 1000000000)


class IA:
    def __init__(self, CSLink, team_name, id, x, y):
        self.id_ = rand()
        self.teamName_ = team_name
        self.comNbs = [0]
        self.pendingRqt_ = []
        self.maxServCommands_ = 9
        self.CSLink_ = CSLink

        self.mapSize = (x, y)
        self.level_ = 1
        self.around_ = None
        self.currentPos_ = 0
        self.currentDir_ = Command.Forward
        self.debug_ = False
        self.debugInv_ = True
        self.reverse = True if randrange(1, 3) == 1 else False
        self.inventory_ = {GameObj.Food: 10,
                           GameObj.Linemate: 0,
                           GameObj.Deraumere: 0,
                           GameObj.Sibur: 0,
                           GameObj.Mendiane: 0,
                           GameObj.Phiras: 0,
                           GameObj.Thystame: 0}
        self.maxFoodStage = 120
        self.foodStage_ = {self.maxFoodStage: "goHalfEat",  # FIXME ça doit dépendre de la durée d'un tour ou un truc comme ça ...
                           100: "goSlowEat",
                           40 + max(x, y): "goFastEat"}
        self.foodStageForElev_ = {self.maxFoodStage: "goHalfEat",
                                  30 + max(x, y): "goSlowEat",
                                  20: "goFastEat"}
        self.updateFcts = {Command.Take: "updateTake",
                           Command.Inventory: "updateInv",
                           Command.Look: "updateLookAround",
                           Command.Forward: "noUpdateNeeded",
                           Command.Right: "noUpdateNeeded",
                           Command.Left: "noUpdateNeeded",
                           Command.Broadcast: "noUpdateNeeded",
                           Command.Set: "updateSet",
                           Command.Incantation: "updateIncantation",
                           Command.Eject: "noUpdateNeeded",
                           Command.Connect_nbr: "updateConnectNbr",
                           Command.Fork: 'noUpdateNeeded'
                           }
        """"""
        self.broadcast(' '.join([str(self.newNb()), 'GET_INFO', str(self.id_)]))
        """"""
        self.maxLineRow = [int(sum([e for e in range(0, i * 2 + 1, 2)][:i]) + ([e for e in range(0, i * 2 + 1, 2)][i] / 2)) for i in range(0, 15, 1)]

        dPrint(self.debugInv_, "Random Id: {0}".format(self.id_))

        self.coolDown = 4
        self.countCoolDown = self.coolDown

        # ELEVATION
        self.situation_ = "normalLife"

        """ LEAD """
        self.myIncNb_ = 0
        self.sameLvlIDs_ = {}  # On stocke l'id (int), s'il est là (bool), son inventaire (dict)
        self.itersBeforeCancel = 30  # FIXME ça doit dépendre d'autre chose comme la vitesse de réponse de la première IA (ou bien y'en a pas besoin et tout est reset quand on recommence)
        self.limit_ = 18
        self.countLimit_ = self.limit_
        self.countItersBeforeCancel = self.itersBeforeCancel

        """ NOT LEAD """
        self.leadID = -1
        self.elevDir = 0
        self.othIncNb_ = 0
        self.nbMoves = int(x / 5) if int(x / 5) >= 1 else 1
        self.countNbMoves = self.nbMoves

        """ CREATE EGGS FOR OTHERS """
        self.helpedIds = []
        self.first = True
        self.matesNb = 0
        self.places = 1
        self.eggCreated = False
        self.startTime = time.time()
        self.connectNbr()

    """
    EMERGENCY

    """

    def emergency(self):
        if self.inventory_[GameObj.Food] <= 7:
            self.broadcast(' '.join([str(self.newNb()), "ALERT", str(self.id_)]))
            dPrint(self.debugInv_, Colors.OKGREEN + "ALLLLLLLLLLLLLLLLLERRRRRRRRRTTT" + Colors.ENDC)
            for i in range(15):
                self.lookAroundNow()
                self.goFastEat()
            self.countLimit_ = self.limit_
            self.countItersBeforeCancel = self.itersBeforeCancel
            self.countCoolDown = 10
            self.sameLvlIDs_.clear()
            self.situation_ = 'normalLife'

    """
        UPDATE FROM SERVER
    """

    def newNb(self):
        r = rand()
        self.comNbs.append(r)
        return str(r) + ' ' + self.teamName_

    def rcvDead(self):
        if self.CSLink_.isDead() is True:
            dPrint(self.debug_ or self.debugInv_, Colors.WARNING + "Dead." + Colors.ENDC)
            self.CSLink_.disconnect()
            exit(0)

    def rcvBroadCast(self):
        msg = self.CSLink_.getServerMsg()
        if 'message' in msg:
            self.CSLink_.clearServerMsg()
            msg = msg[len('message '):]
            dirC = int(msg.split(',')[0])
            msg = msg.split(',')[1][1:]
            dPrint(self.debugInv_, "Broadcast Received: " + msg + " " + self.situation_)
            getattr(self, self.situation_ + "Msg")(dirC, msg)
            return True
        if ('Elevation underway' in msg or 'Current level:' in msg) and (len(self.pendingRqt_) == 0 or self.pendingRqt_[0][0] != Command.Incantation):
            self.CSLink_.clearServerMsg()
            self.updateIncantation(msg)
            return True
        return False

    def rcvEject(self):
        msg = self.CSLink_.getServerMsg()
        if 'eject' in msg:
            self.CSLink_.clearServerMsg()
            self.lookAroundNow()
            return True
        return False

    def updateDataFromServ(self):
        if self.CSLink_.isAlive() is False:
            exit(0)
        while self.CSLink_.msgReceived() is True:
            self.rcvDead()
            if self.rcvBroadCast() is True or self.rcvEject() is True:
                continue
            getattr(self, self.updateFcts[self.pendingRqt_[0][0]])(self.CSLink_.getServerMsg(), self.pendingRqt_[0][1])
            self.pendingRqt_ = self.pendingRqt_[1:]
            self.CSLink_.clearServerMsg()

    def updateDataFromServForce(self):
        while len(self.pendingRqt_) > 0:
            self.updateDataFromServ()

    def updateDataFromServBlock(self, com):
        while com in self.pendingRqt_:
            self.updateDataFromServ()

    def updateIncantation(self, msg, moment=None):
        if moment is not None:
            dPrint(self.debugInv_, Colors.FAIL + "Update Incantation " + moment + " \"" + msg + "\"" + Colors.ENDC)
        else:
            dPrint(self.debugInv_, Colors.FAIL + "Update Incantation " + " \"" + msg + "\"" + Colors.ENDC)

        if moment is not None:
            if 'Current level' in msg:
                self.level_ += 1
                self.situation_ = 'normalLife'
            if 'ko' in msg:
                self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
                self.situation_ = "normalLife"
            self.sameLvlIDs_.clear()

        if moment is None:
            if "ko" in msg:
                self.situation_ = 'normalLife'
            if 'Current level' in msg:
                self.level_ += 1
                self.situation_ = 'normalLife'

    def updateConnectNbr(self, msg, obj):
        self.places = int(msg)
        if self.first is True and self.matesNb < 8 and self.places < 1 and time.time() - self.startTime > 20:
            self.fork()
            self.forward()

    def updateSet(self, msg, obj):
        """
        check
        """
        dPrint(self.debug_, Colors.HEADER + "Update Set" + Colors.ENDC, msg, obj, self.inventory_[obj])
        assert msg == 'ok', "Set can't fail " + obj

    def updateTake(self, msg, obj):
        """
        Update inv from taken objects
        """
        dPrint(self.debug_, Colors.HEADER + "Update Take" + Colors.ENDC, msg, obj, self.inventory_[obj])
        # try:
        #     assert msg == 'ok', "Take failed " + obj
        # except AssertionError:
        #     dPrint("Take ko " + obj)

    def updateLookAround(self, msg, _):
        """
        Parse Look Around
        """
        dPrint(self.debug_, Colors.HEADER + "Look Around" + Colors.ENDC, msg, self.around_)
        self.around_ = [[links[e] for e in list(filter(lambda x: True if x.replace(' ', '') is not None and x.replace(' ', '') != '' else False, i.split(' ')))] for i in msg.replace('[', '').replace(']', '').split(',')]
        self.currentPos_ = 0
        self.currentDir_ = Command.Forward

    def updateInv(self, msg, _):
        """
        Parse Inventory
        """
        dPrint(self.debug_, Colors.HEADER + "Update Inventory" + Colors.ENDC, msg, self.inventory_)
        self.inventory_ = {links[v[0]]: int(v[1]) for v in [list(filter(lambda x: True if x != '' and x != ' ' else False, i.split(' '))) for i in msg.replace('[', '').replace(']', '').split(',')]}

    def noUpdateNeeded(self, msg, _):
        pass

    """
        COMMANDS
    """

    def waitForPlace(self):
        while not len(self.pendingRqt_) < self.maxServCommands_:
            self.updateDataFromServ()

    def eject(self):
        self.waitForPlace()
        self.CSLink_.eject()
        self.pendingRqt_ += [(Command.Eject, None)]
        dPrint(self.debugInv_, Colors.BOLD + "Eject " + Colors.ENDC)

    def broadcast(self, msg):
        self.waitForPlace()
        self.CSLink_.broadcast(msg)
        self.pendingRqt_ += [(Command.Broadcast, None)]
        dPrint(self.debugInv_ or self.debug_, Colors.BOLD + "Broadcast " + Colors.ENDC + msg)

    def inventory(self):
        self.waitForPlace()
        self.CSLink_.inventory()
        self.pendingRqt_ += [(Command.Inventory, None)]
        dPrint(self.debug_, colored("Inventory", "blue"))

    def lookAroundNow(self):
        self.waitForPlace()
        self.CSLink_.look()
        self.pendingRqt_ += [(Command.Look, None)]
        dPrint(self.debug_, colored("Look", "blue"))
        self.updateDataFromServBlock((Command.Look, None))

    def lookAround(self):
        if self.currentDir_ == Command.Forward and self.currentPos_ == 0 and self.around_ is not None:
            return
        self.lookAroundNow()

    def takeNow(self, obj):
        if obj == GameObj.Player:
            return
        self.waitForPlace()
        self.CSLink_.take(linksR[obj])
        self.pendingRqt_ += [(Command.Take, obj)]
        dPrint(self.debug_, colored("Take " + linksR[obj], "blue"))

    def take(self, obj):
        if obj == GameObj.Player:
            return
        if len(self.pendingRqt_) < self.maxServCommands_:
            self.CSLink_.take(linksR[obj])
            self.pendingRqt_ += [(Command.Take, obj)]
            dPrint(self.debug_, colored("Take " + linksR[obj], "blue"))

    def set(self, obj):
        self.waitForPlace()
        self.CSLink_.set(linksR[obj])
        self.pendingRqt_ += [(Command.Set, obj)]
        dPrint(self.debug_, colored("Set " + linksR[obj], "blue"))
        assert self.inventory_[obj] >= 0, "Invalid set"

    def eat(self):
        self.take(GameObj.Food)

    def eatNow(self):
        self.takeNow(GameObj.Food)

    def forward(self):
        self.waitForPlace()
        self.CSLink_.forward()
        self.currentPos_ = self.getPosForward(self.currentPos_)
        self.pendingRqt_ += [(Command.Forward, None)]
        dPrint(self.debug_, colored("Go forward", "blue"))

    def right(self):
        self.waitForPlace()
        self.CSLink_.right()
        self.currentDir_ = Command.Right
        self.pendingRqt_ += [(Command.Right, None)]
        dPrint(self.debug_, colored("Turn Right", "blue"))

    def left(self):
        self.waitForPlace()
        self.CSLink_.left()
        self.currentDir_ = Command.Left
        self.pendingRqt_ += [(Command.Left, None)]
        dPrint(self.debug_, colored("Turn Left", "blue"))

    def incantation(self):
        self.waitForPlace()
        self.CSLink_.incantation()
        self.pendingRqt_ += [(Command.Incantation, "Start")]
        self.pendingRqt_ += [(Command.Incantation, "End")]
        dPrint(self.debugInv_, Colors.UNDERLINE + "ELEVATION" + Colors.ENDC)

    def connectNbr(self):
        pass
        # self.waitForPlace()
        # self.CSLink_.connectNbr()
        # self.pendingRqt_ += [(Command.Connect_nbr, None)]
        # dPrint(self.debugInv_, Colors.UNDERLINE + "Connect nbr" + Colors.ENDC)

    def fork(self):
        pass
        # self.waitForPlace()
        # self.CSLink_.fork()
        # self.pendingRqt_ += [(Command.Fork, None)]
        # dPrint(self.debugInv_, Colors.UNDERLINE + "Fork" + Colors.ENDC)

    """
        IA
    """

    """ MOVEMENTS """

    def getPosForward(self, pos):
        if self.currentDir_ == Command.Forward:
            return (max(([i if self.maxLineRow[int(i)] <= pos < self.maxLineRow[int(i + 1)] else -1 for i in range(len(self.maxLineRow))])) + 1) * 2 + pos
        if self.currentDir_ == Command.Right:
            return pos + 1
        return pos - 1

    def getPosRow(self, pos):
        return max(([i if self.maxLineRow[int(i)] <= pos < self.maxLineRow[int(i + 1)] else -1 for i in range(len(self.maxLineRow))]))

    def getPosCol(self, pos, row):
        return pos - self.maxLineRow[row]

    def getDistToCrossForward(self, dest):
        return self.getPosRow(dest) - self.getPosRow(self.currentPos_)

    def getDistToCrossSide(self, dest, row):
        return self.getPosCol(dest, row) - self.getPosCol(self.currentPos_, row)

    def goTo(self, dest):
        steps = self.getDistToCrossForward(dest)
        assert steps >= 0, "Go to: Can't go back"
        for i in range(steps):
            self.forward()
        assert self.getPosRow(dest) == self.getPosRow(self.currentPos_), "Go to: Invalid pos Y"
        steps = self.getDistToCrossSide(dest, self.getPosRow(dest))
        if steps > 0:
            self.right()
        elif steps < 0:
            self.left()
            steps *= -1
        for i in range(steps):
            self.forward()

    def goToDir(self, d, moves):
        for i in dirs[d]:
            getattr(self, i)()
        for i in range(moves):
            self.forward()

    def getPosesInScope(self, obj):
        # FIXME poses returned are not sorted by proximity neitheir by amount of object present on it
        poses = []
        self.lookAroundNow()
        self.updateDataFromServBlock((Command.Look, None))
        for i in range(0, len(self.around_)):
            if self.around_[i].count(obj) > 0:
                poses += [i]
        return poses

    def searchAndGoFor(self, obj):
        poses = self.getPosesInScope(obj)
        if len(poses) != 0:
            self.goTo(poses[0])
            return True
        self.right()
        r = randrange(1, self.maxServCommands_)
        for i in range(r):
            self.forward()
        self.lookAround()
        self.updateDataFromServBlock((Command.Look, None))
        return False

    """ FOOD """

    def goFastEat(self):
        for i in range(self.around_[self.currentPos_].count(GameObj.Food)):
            self.eatNow()
        if self.searchAndGoFor(GameObj.Food) is False:
            return
        for i in range(self.around_[self.currentPos_].count(GameObj.Food)):
            self.eatNow()

    def goSlowEat(self):
        for i in range(self.around_[self.currentPos_].count(GameObj.Food)):
            self.eat()

    def goHalfEat(self):
        for i in range(int(self.around_[self.currentPos_].count(GameObj.Food) / 2)):
            self.eat()

    """ STONES """

    def getStones(self):
        if self.reverse is True:
            for s in elevRqrmts[self.level_]:
                if self.inventory_[s] < elevRqrmts[self.level_][s] and self.searchAndGoFor(s) is True:
                    self.takeNow(s)
                    break
        else:
            for s in list(list(elevRqrmts[self.level_].keys()).__reversed__()):
                if self.inventory_[s] < elevRqrmts[self.level_][s] and self.searchAndGoFor(s) is True:
                    self.takeNow(s)
                    break

    """ ELEVATION """

    def setUpElevLead(self):
        missing = elevRqrmts[self.level_].copy()
        msg = {}

        dPrint(self.debugInv_, Colors.UNDERLINE + "Setup Elevation" + Colors.ENDC)
        self.inventory()
        self.lookAroundNow()
        for i in self.around_[self.currentPos_]:  # Make elevation place empty
            self.takeNow(i)
        dPrint(self.debugInv_, Colors.UNDERLINE + "SET WHAT S NEEDED" + Colors.ENDC)
        for i, j in missing.items():  # Pour chaque item
            for e in range(min(self.inventory_[i], j)):  # On en set le nombre min entre l'inventaire et ce qu'il manque
                self.set(i)
                missing[i] -= 1
            assert missing[i] >= 0
            if missing[i] == 0:
                continue
            for p, pv in self.sameLvlIDs_.items():  # Pour chaque player
                if p not in msg.keys():
                    msg[p] = {i: 0 for i in self.inventory_}
                msg[p][i] = min(pv[1][i], missing[i])
                missing[i] -= msg[p][i]
                dPrint(self.debugInv_, "MIN ", min(self.inventory_[i], j))
                dPrint(self.debugInv_, "INV ", msg[p][i])
        dPrint(self.debugInv_, Colors.UNDERLINE + "END SETUP ELEVATION" + Colors.ENDC)
        if len(list(msg.keys())) > 0:
            self.broadcast(' '.join([str(self.newNb()), 'SET', str(self.id_), setRequestToStr(msg)]))

    def placeIsReadyToElevLead(self):
        self.lookAroundNow()
        for i, j in elevRqrmts[self.level_].items():
            if self.around_[self.currentPos_].count(i) != j:
                dPrint(self.debugInv_, 'Invalid ', self.around_[self.currentPos_].count(i), j, i)
                return False
        if self.around_[self.currentPos_].count(GameObj.Player) != elevPlayers[self.level_]:
            dPrint(self.debugInv_, colored("MISSING there is " + str(self.around_[self.currentPos_].count(GameObj.Player)) + ' need: ' + str(elevPlayers[self.level_]), "red"))
            return False
        if self.around_[self.currentPos_].count(GameObj.Food) != 0:
            return False
        return True

    def removeItemThatShouldntBeThereSecondLead(self):
        self.lookAroundNow()
        for i, j in elevRqrmts[self.level_].items():
            for _ in range(0, self.around_[self.currentPos_].count(i) - j):
                self.takeNow(i)
                dPrint(self.debugInv_, Colors.OKGREEN + "TAKE " + Colors.ENDC, i)
        for _ in range(0, self.around_[self.currentPos_].count(GameObj.Food)):
            self.takeNow(GameObj.Food)

    def idsTohaveEnoughStones(self):
        possibilities = list(itertools.combinations(list(self.sameLvlIDs_.keys()), elevPlayers[self.level_] - 1))

        dPrint(self.debugInv_, colored("recherche des combinaisons ", "red"), possibilities)
        for p in possibilities:
            others = [self.sameLvlIDs_[i][1] for i in p]
            dPrint(self.debugInv_, "OTHERS INVS ", others)
            others = {key: sum(e[key] for e in others) for key in others[0].keys()}
            dPrint(self.debugInv_, "OTHERS INVS 2 ", others)
            for s in elevRqrmts[self.level_]:
                if self.inventory_[s] + others[s] < elevRqrmts[self.level_][s]:
                    others = None
                    break
            if others is not None:
                return p
        return None

    def haveGoodAmountOfStones(self):
        missing = 0

        for s in elevRqrmts[self.level_]:
            if self.inventory_[s] < elevRqrmts[self.level_][s]:
                missing += elevRqrmts[self.level_][s] - self.inventory_[s]
        if missing == 0 or int(elevTotalStones[self.level_] - (elevTotalStones[self.level_] / elevPlayers[self.level_])) - missing >= 0:
            return True
        return False

    """ MANAGE RECEIVED MESSAGES DEPENGING OF SITUATION """

    def updateComNbs(self, msg):
        save = msg
        try:
            msg = msg.split(' ')
            if int(msg[0]) in self.comNbs or msg[1] != self.teamName_:
                return None
            self.comNbs.append(int(msg[0]))
        except:
            if randrange(1, 7) == 1:
                self.broadcast(save)
            return None
        if msg[2] == 'GET_INFO':
            self.broadcast(' '.join([str(self.newNb()), 'NEW_INFO', msg[3], str(self.id_), '-'.join([str(i) for i in self.comNbs])]))
            self.matesNb += 1
            self.helpedIds.append(int(msg[3]))
            return None
        return msg[2:]

    def normalLifeMsg(self, dirC, msg):
        """
        AI go for stone and food
        [Gestion Des messages]
        """

        msg = self.updateComNbs(msg)
        if msg is None:
            return

        if msg[0] == 'LEAD' and self.level_ == int(msg[1]) and self.inventory_[GameObj.Food] > 30 + max(self.mapSize[0], self.mapSize[1]) and self.level_ < 8:
            dPrint(self.debugInv_, colored("CO FOUND", "red"))
            self.leadID = int(msg[2])
            self.othIncNb_ = int(msg[3])
            self.situation_ = "waitForGoNoLead"
            self.broadcast(' '.join([str(self.newNb()), 'OK', str(self.leadID), str(self.othIncNb_), str(self.id_), invToStr(self.inventory_)]))
            return

        if msg[0] == 'NEW_INFO' and int(msg[1]) == self.id_:
            self.comNbs += msg[3].split('-')
            self.comNbs = list(dict.fromkeys(self.comNbs))
            self.matesNb += 1
            if int(msg[2]) not in self.helpedIds or int(msg[2]) > self.id_:
                self.first = False

    def waitForGoNoLeadMsg(self, dirC, msg):
        """
        On attend de savoir si on doit se diriger vers une incantation ou si c'est cancel
        [Gestion Des messages]
        Il a accepté, il a attend le go ou un cancel
        """
        msg = self.updateComNbs(msg)
        if msg is None:
            return

        if msg[0] == 'GO' and int(msg[1]) == self.leadID and int(msg[2]) == self.othIncNb_ and self.id_ in strTolIDs(msg[3]):
            self.elevDir = dirC
            self.situation_ = 'goToIncantationNoLead'
            self.countNbMoves = self.nbMoves
            self.updateDataFromServForce()
            return
        if msg[0] == 'CANCEL' and int(msg[1]) == self.leadID and self.othIncNb_ == int(msg[2]) and self.id_ in strTolIDs(msg[3]):
            self.situation_ = 'normalLife'
            self.leadID = -1
            return
        if msg[0] == 'CANCELALL' and int(msg[1]) == self.leadID and self.othIncNb_ == int(msg[2]):
            self.situation_ = 'normalLife'
            self.leadID = -1
            return
        if msg[0] == 'ALERT' and int(msg[1]) == self.leadID:
            self.situation_ = 'normalLife'
            self.leadID = -1
            return

    def goToIncantationNoLeadMsg(self, dirC, msg):
        """
        On se dirige vers l'incantation (en faisant en sorte d'avoir de la nourriture)
        [Gestion Des messages]
        """
        msg = self.updateComNbs(msg)
        if msg is None:
            return

        if msg[0] == 'UPDATE' and int(msg[1]) == self.leadID and self.id_ == int(msg[2]):
            self.elevDir = dirC
            if self.elevDir == 0:
                self.broadcast(' '.join([str(self.newNb()), 'PLACED', str(self.leadID), str(self.id_)]))
                dPrint(self.debugInv_, colored("ASKIP JE SUIS PLACED", "yellow"))
                self.situation_ = 'waitForInstructions'
            return

        if msg[0] == 'CANCELALL' and int(msg[1]) == self.leadID and self.othIncNb_ == int(msg[2]):
            self.situation_ = 'normalLife'
            self.leadID = -1
            return

        if msg[0] == 'ALERT' and int(msg[1]) == self.leadID:
            self.elevDir = -1
            self.leadID = -1
            self.situation_ = 'normalLife'
            return

    def waitForInstructionsMsg(self, dirC, msg):
        """
        J'attend de savoir ce que je dois poser par terre
        / Je ne fais rien s'il n'y pas d'instructions (incantation en cours)
        [Gestion Des messages]
        """
        msg = self.updateComNbs(msg)
        if msg is None:
            return

        if msg[0] == 'SET' and int(msg[1]) == self.leadID:
            d = strToSetRequest(msg[2])
            for i in d[self.id_]:
                for e in range(d[self.id_][i]):
                    self.set(i)
            return

        if msg[0] == 'CANCELALL' and int(msg[1]) == self.leadID and self.othIncNb_ == int(msg[2]):
            self.situation_ = "normalLife"
            self.leadID = -1
            return

        if msg[0] == 'ALERT' and int(msg[1]) == self.leadID:
            self.elevDir = -1
            self.leadID = -1
            self.situation_ = "normalLife"
            return

    def waitForAnswersLeadMsg(self, dirC, msg):
        """
        On attend que les autres répondent à notre requête
        Si trop de temps est écoulé on retourne au cas 1
        [Gestion Des messages]
        """
        msg = self.updateComNbs(msg)
        if msg is None:
            return

        if msg[0] == 'OK' and int(msg[1]) == self.id_ and int(msg[2]) == self.myIncNb_:
            self.sameLvlIDs_[int(msg[3])] = [False, strToinv(msg[4])]
            return

        if msg[0] == 'LEAD' and self.level_ == int(msg[1]) and int(msg[2]) > self.id_:
            dPrint(self.debugInv_, colored("CO FOUND REPLACE", "red"))
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            self.leadID = int(msg[2])
            self.othIncNb_ = int(msg[3])
            self.situation_ = "waitForGoNoLead"
            self.sameLvlIDs_.clear()
            self.broadcast(' '.join([str(self.newNb()), 'OK', str(self.leadID), str(self.othIncNb_), str(self.id_), invToStr(self.inventory_)]))
            return

        if msg[0] == 'ALERT' and int(msg[1]) in list(self.sameLvlIDs_.keys()):
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            self.sameLvlIDs_.clear()
            self.situation_ = 'normalLife'
            return

    def waitForOthersCmgLeadMsg(self, dirC, msg):
        """
        On attend que les autres viennent. Quand ils sont là, ils envoient un msg et leur status passe à True dans comingsIDs_
        On envoie la position régulièrement
        [Gestion Des messages]
        """
        msg = self.updateComNbs(msg)
        if msg is None:
            return

        # On enregistre ceux qui sont placés
        if msg[0] == 'PLACED' and int(msg[1]) == self.id_:
            self.sameLvlIDs_[int(msg[2])] = [True, self.sameLvlIDs_[int(msg[2])][1]]
            self.lookAroundNow()
            return

        # On envoie des messages à ceux qui viennent quand ils veulent
        if msg[0] == 'ASKED' and int(msg[1]) == self.id_:
            self.updateDataFromServForce()
            self.broadcast(' '.join([str(self.newNb()), 'UPDATE', str(self.id_), str(msg[2])]))

        # On cancel ceux qui arrivent en retard
        if msg[0] == 'OK' and int(msg[1]) == self.id_ and int(msg[2]) == self.myIncNb_:
            self.broadcast(' '.join([str(self.newNb()), 'CANCEL', str(self.id_), str(self.myIncNb_), lIDsToStr([int(msg[3])])]))
            return

        if msg[0] == 'ALERT' and int(msg[1]) in list(self.sameLvlIDs_.keys()):
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            self.sameLvlIDs_.clear()
            self.situation_ = 'normalLife'
            return

    def setOrganizationLeadMsg(self, dirC, msg):
        """
        Dés qu'il y a la bonne quantité d'élément on incante.
        Puis on passe à la situation suivante
        [Gestion Des messages]
        """
        if msg[0] == 'ALERT' and int(msg[1]) in list(self.sameLvlIDs_.keys()):
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            self.sameLvlIDs_.clear()
            self.situation_ = 'normalLife'
            return
        pass

    def secureElevationSecondLeadMsg(self, dirC, msg):
        """
        On vérifie le bon fonctionnement de l'incantation
        [Gestion Des messages]
        """
        if msg[0] == 'ALERT' and int(msg[1]) in list(self.sameLvlIDs_.keys()):
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            self.sameLvlIDs_.clear()
            self.situation_ = 'normalLife'
            return
        pass

    """ IA MAIN RUN """

    def normalLife(self):
        dPrint(self.debugInv_, Colors.SMALL + "Normal Life" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()
        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()
        self.getStones()

        # dPrint(self.debugInv_, self.eggCreated, self.places, self.first, self.inventory_[GameObj.Food])
        if self.eggCreated is False and self.places < 8 and self.first is True and self.inventory_[GameObj.Food] > 30 and time.time() - self.startTime > 4:
            while self.places < 8:
                self.fork()
                self.forward()
                self.places += 1
            self.eggCreated = True

        if randrange(1, 40) == 1:
            self.connectNbr()
        self.countCoolDown -= 1
        # TODO Mettre le bordel dans les incantations des autres

        if self.haveGoodAmountOfStones() and self.situation_ == 'normalLife' and self.inventory_[GameObj.Food] > 38 + max(self.mapSize[0], self.mapSize[1]) and self.countCoolDown <= 0 and self.level_ < 8:
            self.countLimit_ = self.limit_
            self.countCoolDown = self.coolDown
            self.countItersBeforeCancel = self.itersBeforeCancel
            if self.level_ > 1:
                self.sameLvlIDs_.clear()
                self.countLimit_ = self.limit_
                self.situation_ = "waitForAnswersLead"
                self.myIncNb_ += 1
            else:
                self.setUpElevLead()
                self.situation_ = "setOrganizationLead"

    def waitForGoNoLead(self):
        """
        On attend de savoir si on doit se diriger vers une incantation ou si c'est cancel
        """
        dPrint(self.debugInv_, Colors.SMALL + "waitForGoNoLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()
        self.getStones()

    def goToIncantationNoLead(self):
        """
        On se dirige vers l'incantation (en faisant en sorte d'avoir de la nourriture)
        """

        dPrint(self.debugInv_, Colors.SMALL + "goToIncantationNoLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        # getattr(self, self.foodStageForElev_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStageForElev_.items()])])()
        self.goSlowEat()  # FIXME ?

        self.updateDataFromServForce()
        if self.elevDir is not None and self.elevDir != 0 and self.situation_ == 'goToIncantationNoLead':
            self.goToDir(self.elevDir, self.countNbMoves)
            self.updateDataFromServForce()
            self.broadcast(' '.join([str(self.newNb()), 'ASKED', str(self.leadID), str(self.id_)]))

            if self.countNbMoves > 1:
                self.countNbMoves -= 1
            self.elevDir = None

        if self.elevDir == 0 and self.situation_ == 'goToIncantationNoLead':
            self.updateDataFromServForce()
            self.broadcast(' '.join([str(self.newNb()), 'ASKED', str(self.leadID), str(self.id_)]))

    def waitForInstructions(self):
        """
        J'attend de savoir ce que je dois poser par terre
        / Je ne fais rien s'il n'y pas d'instructions (incantation en cours)
        """
        dPrint(self.debugInv_, Colors.SMALL + "waitForInstructions" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        pass  # FIXME

    def waitForAnswersLead(self):
        """
        On attend que les autres répondent à notre requête
        Si trop de temps est écoulé on retourne au cas 1
        """
        dPrint(self.debugInv_, Colors.SMALL + "waitForAnswersLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()

        dPrint(self.debugInv_, Colors.WARNING + str(len(self.sameLvlIDs_)) + ' ' + str(elevPlayers[self.level_] - 1) + Colors.ENDC)
        if self.countItersBeforeCancel == self.itersBeforeCancel or (self.itersBeforeCancel - self.countItersBeforeCancel) % 2 == 0:
            self.broadcast(' '.join([str(self.newNb()), 'LEAD', str(self.level_), str(self.id_), str(self.myIncNb_)]))
        if len(self.sameLvlIDs_) >= elevPlayers[self.level_] - 1:
            dPrint(self.debugInv_, colored("check", "red"))
            ids = self.idsTohaveEnoughStones()
            if ids is not None:
                self.situation_ = "waitForOthersCmgLead"
                # Cancel for other ids
                dPrint(self.debugInv_, colored("On a assez de resources pour start " + ids.__str__(), "red"))
                CanceledIds = set(list(self.sameLvlIDs_.keys())) - set(ids)
                if len(CanceledIds) > 0:
                    self.broadcast(' '.join([str(self.newNb()), 'CANCEL', str(self.id_), str(self.myIncNb_), lIDsToStr(CanceledIds)]))

                self.broadcast(' '.join([str(self.newNb()), 'GO', str(self.id_), str(self.myIncNb_), lIDsToStr(ids)]))
                self.sameLvlIDs_ = {i: self.sameLvlIDs_[i] for i in ids}

                self.updateDataFromServForce()
                return

        self.countItersBeforeCancel -= 1
        if self.countItersBeforeCancel <= 0 and self.situation_ == 'waitForAnswersLead':
            self.countItersBeforeCancel = self.itersBeforeCancel
            self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
            dPrint(self.debugInv_, colored("pas assez de gens ou de ressources : cancel"))
            self.situation_ = "normalLife"
            self.sameLvlIDs_.clear()

    def waitForOthersCmgLead(self):
        """
        On attend que les autres viennent. Quand ils sont là, ils envoient un msg et leur status passe à True dans comingsIDs_
        On envoie la position régulièrement
        """
        dPrint(self.debugInv_, Colors.SMALL + "waitForOthersCmgLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        for i, j in self.sameLvlIDs_.items():
            if j[0] is False:
                return
        self.setUpElevLead()
        self.situation_ = "setOrganizationLead"

    def setOrganizationLead(self):
        """
        Dés qu'il y a la bonne quantité d'élément on incante.
        Puis on passe à la situation suivante
        """
        dPrint(self.debugInv_, Colors.SMALL + "setOrganizationLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        if self.placeIsReadyToElevLead() is False:
            dPrint(self.debugInv_, "Place is not ready")
            self.removeItemThatShouldntBeThereSecondLead()
            self.countLimit_ -= 1
            if self.countLimit_ <= 0:
                self.broadcast(' '.join([str(self.newNb()), 'CANCELALL', str(self.id_), str(self.myIncNb_)]))
                self.situation_ = 'normalLife'
                self.eject()
                self.sameLvlIDs_.clear()
                self.countLimit_ = self.limit_
            return

        if self.level_ > 1:
            pass  # Définir un second leader
        self.lookAroundNow()
        dPrint(self.debugInv_, "INCANTATION PLACE", self.around_[self.currentPos_])
        self.incantation()
        self.updateDataFromServBlock((Command.Incantation, "End"))

    def secureElevationSecondLead(self):
        """
        On vérifie le bon fonctionnement de l'incantation
        """
        dPrint(self.debugInv_, Colors.SMALL + "secureElevationSecondLead" + Colors.ENDC, self.id_, self.leadID)
        self.emergency()

        # Si un truc pop, on le prend, si un joueur est en trop on dégage tout TODO
        # Si c'est fini on revient au cas 1
        pass

    def run(self):
        self.inventory()
        self.lookAroundNow()
        self.updateDataFromServ()
        getattr(self, self.situation_)()

        return True
