#!/usr/bin/python3

from obj2aps2 import *
from mtl2ams import *



objparser = OBJParser(sys.argv[1])
objparser.parse()
objparser.write_as_aps2(sys.argv[2])