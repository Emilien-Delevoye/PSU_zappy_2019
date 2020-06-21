
import sys


def dPrint(debug, *args):
    if debug and type(args[0]) is not str:
        print("[debug] ", args, file=sys.stdout, flush=True)
    if debug and type(args[0]) is str and len(args) == 1:
        print("[debug] " + args[0], flush=True)
    elif debug and type(args[0]) is str:
        print("[debug] " + args[0], args[1:], file=sys.stdout, flush=True)


class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    SMALL = '\033[2m'
    UNDERLINE = '\033[4m'
