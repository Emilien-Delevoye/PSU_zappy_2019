
from utils import dPrint, Colors
import numpy as np
from enum import Enum
from serverLink import ServerLink, Command
from termcolor import colored
from random import randrange


# TODO gérer les ejects
# TODO gérer les deaths
# TODO sécuriser les communications

# TODO Organiser les incantations
# TODO Faire attention à ce que la quantité d'objects sur l'incantation reste inchangé

# TODO Faire en sorte de se reproduire dans certains cas
# TODO Get info pour savoir combien il y a d'ia de quel niveau (pour se reproduire)


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


elevPlayers = {1: 1, 2: 2, 3: 2, 4: 4, 5: 4, 6: 6, 7: 6}

elevRqrmts = {
    1: {GameObj.Linemate: 1, GameObj.Deraumere: 0, GameObj.Sibur: 0, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0},  # FIXME
    2: {GameObj.Linemate: 1, GameObj.Deraumere: 1, GameObj.Sibur: 1, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0},
    3: {GameObj.Linemate: 2, GameObj.Deraumere: 0, GameObj.Sibur: 1, GameObj.Mendiane: 0, GameObj.Phiras: 2, GameObj.Thystame: 0},
    4: {GameObj.Linemate: 1, GameObj.Deraumere: 1, GameObj.Sibur: 2, GameObj.Mendiane: 0, GameObj.Phiras: 1, GameObj.Thystame: 0},
    5: {GameObj.Linemate: 1, GameObj.Deraumere: 2, GameObj.Sibur: 1, GameObj.Mendiane: 3, GameObj.Phiras: 0, GameObj.Thystame: 0},
    6: {GameObj.Linemate: 1, GameObj.Deraumere: 2, GameObj.Sibur: 3, GameObj.Mendiane: 0, GameObj.Phiras: 1, GameObj.Thystame: 0},
    7: {GameObj.Linemate: 2, GameObj.Deraumere: 2, GameObj.Sibur: 2, GameObj.Mendiane: 2, GameObj.Phiras: 2, GameObj.Thystame: 1}
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


class IA:
    def __init__(self, CSLink):
        self.id_ = randrange(0, 1000000)
        self.level_ = 1
        self.around_ = None
        self.currentPos_ = 0
        self.currentDir_ = Command.Forward
        self.CSLink_ = CSLink
        self.debug_ = True
        self.maxServCommands_ = 10
        self.inventory_ = {GameObj.Food: 10,
                           GameObj.Linemate: 0,
                           GameObj.Deraumere: 0,
                           GameObj.Sibur: 0,
                           GameObj.Mendiane: 0,
                           GameObj.Phiras: 0,
                           GameObj.Thystame: 0}
        self.maxFoodStage = 120
        self.foodStage_ = {self.maxFoodStage: "goHalfEat",
                           80: "goSlowEat",
                           50: "goFastEat"}
        self.pendingRqt_ = []
        self.updateFcts = {Command.Take: "updateTake",
                           Command.Inventory: "updateInv",
                           Command.Look: "updateLookAround",
                           Command.Forward: "noUpdateNeeded",
                           Command.Right: "noUpdateNeeded",
                           Command.Left: "noUpdateNeeded",
                           }
        self.maxLineRow = [int(sum([e for e in range(0, i * 2 + 1, 2)][:i]) + ([e for e in range(0, i * 2 + 1, 2)][i] / 2)) for i in range(0, 15, 1)]

        dPrint(self.debug_, "Random Id: {0}".format(self.id_))

        # ELEVATION
        self.lead_ = False
        self.elevation_ = False
        self.situation_ = "normalLife"

        """ LEAD """
        self.commingIDs_ = []
        self.itersBeforeCancel = 20  # FIXME ça doit dépendre d'autre chose comme la vitesse de réponse de la première IA (ou bien y'en a pas besoin et tout est reset quand on recommence)
        self.totalStones = {GameObj.Food: 0, GameObj.Linemate: 0, GameObj.Deraumere: 0, GameObj.Sibur: 0, GameObj.Mendiane: 0, GameObj.Phiras: 0, GameObj.Thystame: 0}

        """ NOT LEAD """
        self.elevDir = 0
        self.nbMoves = 10  # FIXME la quantité de mouvements pour se rapprocher doit dépendre de la taille de la map (Il réduit au fil du temps)

    """
        UPDATE FROM SERVER 
    """

    def rcvDead(self):
        if self.CSLink_.isDead() is True:
            dPrint(self.debug_, Colors.WARNING + "Dead." + Colors.ENDC)
            self.CSLink_.disconnect()
            exit(0)

    def rcvBroadCast(self):
        msg = self.CSLink_.getServerMsg()
        if 'message' in msg:
            pass  # FIXME
            return True
        return False

    def rcvEject(self):
        msg = self.CSLink_.getServerMsg()
        if 'eject' in msg:
            pass  # FIXME
            return True
        return False

    def updateDataFromServ(self):
        while self.CSLink_.msgReceived() is True:
            self.rcvDead()
            if self.rcvBroadCast() is True or self.rcvEject():
                self.CSLink_.clearServerMsg()
                continue
            getattr(self, self.updateFcts[self.pendingRqt_[0][0]])(self.CSLink_.getServerMsg(), self.pendingRqt_[0][1])
            self.pendingRqt_ = self.pendingRqt_[1:]
            self.CSLink_.clearServerMsg()

    def updateDataFromServBlock(self, com):
        while com in self.pendingRqt_:
            self.updateDataFromServ()

    def updateTake(self, msg, obj):
        """
        Update inv from taken objects
        """
        dPrint(self.debug_, Colors.HEADER + "Update Take" + Colors.ENDC, msg, obj, self.inventory_[obj])
        if msg != 'ko':
            self.inventory_[obj] += 1

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

    def inventory(self):
        self.waitForPlace()
        self.CSLink_.inventory()
        self.pendingRqt_ += [(Command.Inventory, None)]
        dPrint(self.debug_, colored("Need Inventory", "blue"))

    def lookAround(self):
        if self.currentDir_ == Command.Forward and self.currentPos_ == 0 and self.around_ is not None:
            return
        self.waitForPlace()
        self.CSLink_.look()
        self.pendingRqt_ += [(Command.Look, None)]
        dPrint(self.debug_, colored("Need Look", "blue"))
        self.updateDataFromServBlock((Command.Look, None))

    def takeNow(self, obj):
        self.waitForPlace()
        self.CSLink_.take(linksR[obj])
        self.pendingRqt_ += [(Command.Take, obj)]
        dPrint(self.debug_, colored("Need " + linksR[obj], "blue"))
        self.around_[self.currentPos_].remove(obj)

    def take(self, obj):
        if len(self.pendingRqt_) < self.maxServCommands_:
            self.CSLink_.take(linksR[obj])
            self.pendingRqt_ += [(Command.Take, obj)]
            dPrint(self.debug_, colored("Need " + linksR[obj], "blue"))
            self.around_[self.currentPos_].remove(obj)

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

    def getPosesInScope(self, obj):
        # FIXME poses returned are not sorted by proximity neitheir by amount of object present on it
        poses = []
        self.lookAround()
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
        # FIXME If the object is not found in scope then turn right and go forward
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
        for s in elevRqrmts[self.level_]:
            if self.inventory_[s] < elevRqrmts[self.level_][s]:
                if self.searchAndGoFor(s) is True:
                    self.takeNow(s)
                break

    """ ELEVATION """

    def haveGoodAmountOfStones(self):
        missing = 0

        for s in elevRqrmts[self.level_]:
            if self.inventory_[s] < elevRqrmts[self.level_][s]:
                missing += elevRqrmts[self.level_][s] - self.inventory_[s]
        if missing == 0 or missing < elevTotalStones[self.level_] / elevPlayers[self.level_]:
            return True
        return False

    """ COMMUNICATION """

    def lead(self):
        pass

    """ IA MAIN RUN """

    # TODO vérifier l'utilité des variables d'elevation

    def normalLife(self):
        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()
        self.getStones()

        # TODO Mettre le bordel dans les incantations des autres

        if self.haveGoodAmountOfStones():
            # FIXME SEND MESSAGE IF LEVEL > 1
            self.situation_ = "waitForAnswersLead"

    def waitForGoNoLead(self):
        """
        On attend de savoir si on doit se diriger vers une incantation ou si c'est cancel
        """
        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()
        self.getStones()

    def goToIncantationNoLead(self):
        """
        On se dirige vers l'incantation (en faisant en sorte d'avoir de la nourriture)
        """

        # Si je suis arrivé, je préviens. puis j'attend les instructions
        pass  # FIXME

    def waitForInstructions(self):
        """
        J'attend de savoir ce que je dois poser par terre
        / Je ne fais rien s'il n'y pas d'instructions (incantation en cours)
        """
        pass  # FIXME

    def waitForAnswersLead(self):
        """
        On attend que les autres répondent à notre requête
        Si trop de temps est écoulé on retourne au cas 1
        """
        getattr(self, self.foodStage_[min([va if self.inventory_[GameObj.Food] < va else self.maxFoodStage for va, v in self.foodStage_.items()])])()
        self.getStones()

        if len(self.commingIDs_) == elevPlayers[self.level_] - 1 and self.totalStones == elevRqrmts:  # FIXME en regardant s'il y a assez de stones
            # FIXME Communique quelles IAs viennent (attention à faire la sélection) IF LEVEL > 1
            self.situation_ = "waitForOthersCmgLead"
            pass

        # FIXME Si trop de temps est passé et que rien n'est concluant on envoie le cancel et on retourne au cas 1

    def waitForOthersCmgLead(self):
        """
        On attend que les autres viennent. Quand ils sont là, ils envoient un msg et leeur status passe à True dans comingsIDs_
        On envoie la position régulièrement
        """
        # FIXME Envoyer ma position régulièrement SI LEVEL > 1

        for i, j in self.commingIDs_:
            if j is False:
                return
        self.situation_ = "setOrganizationLead"
        pass

    def setOrganizationLead(self):
        """
        On communique à tout le monde que poser par terre,
        Dés qu'il y a la bonne quantité d'élément on incante.
        Puis on passe à la situation suivante
        """
        # FIXME

        # FIXME Si tout est posé on passe à la sécurisation
        self.situation_ = "serurizeElevationLead"

    def serurizeElevationLead(self):
        """
        On vérifie le bon fonctionnement de l'incantation
        """
        # Si un truc pop, on le prend, si un joueur est en trop on dégage tout
        # Si c'est fini on revient au cas 1
        pass

    def run(self):
        self.inventory()
        self.lookAround()
        self.updateDataFromServ()
        getattr(self, self.situation_)()

        return True

