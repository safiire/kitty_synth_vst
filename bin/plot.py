#!/usr/bin/env python

from os import popen
from pylab import plot
from time import sleep


def getdata():
    p = popen('bin/test_envelope')
    str = p.read()
    ary = eval(str)
    plot(ary)
    p.close()

