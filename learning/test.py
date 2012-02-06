#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from id3 import get_decision_tree, get_gain
from fileinput import input as Input
from csv import reader


def print_tree(tree, str=""):
    """
    imprime el árbol en formato digraph lista para pasarlo a dot
    """
    if str == "":
        print "digraph ID3{"
        str = ""

    if type(tree) == dict:
        for key, value in tree.iteritems():
            print_tree(value, str + '"%s" -> ' % key)
    else:
        print str + '"%s";' % tree

    if str == "":
        print "}"


if __name__ == "__main__":
    data = reader(Input())
    headers = data.next()
    target_attr = headers[-1]
    data = [{headers[pos]:row[pos] for pos in range(len(headers))}
        for row in data]
    tree = get_decision_tree(data, headers, target_attr, get_gain)
#    classification = classify(tree, data)
    print_tree(tree)
