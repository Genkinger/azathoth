#!/usr/bin/python3

from obj2aps2 import *



parser = OBJParser(sys.argv[1])
parser.parse()
parser.write_as_aps2(sys.argv[2])