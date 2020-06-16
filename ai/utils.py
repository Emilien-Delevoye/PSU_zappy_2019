
import sys


def dPrint(debug, *args):
    if debug and args[0] is not str:
        print("[debug] ", args[:], file=sys.stdout, flush=True)
    if debug and args[0] is str:
        print("[debug] " + args[0], args[1:], file=sys.stdout, flush=True)
