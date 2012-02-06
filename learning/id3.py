#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from collections import defaultdict
from math import log


def get_entropy(data, target_attr):
    frecuences = (float(value)
        for value in get_frecuences(data, target_attr).itervalues())
    entropy = sum(((-freq / len(data)) * log(freq / len(data), 2) 
        for freq in frecuences))
    return entropy
    
def get_gain(data, attr, target_attr):
    val_freq = {}
    subset_entropy = 0.0

    for record in data:
        if (val_freq.has_key(record[attr])):
            val_freq[record[attr]] += 1.0
        else:
            val_freq[record[attr]] = 1.0

    for val in val_freq.keys():
        val_prob = val_freq[val] / sum(val_freq.values())
        data_subset = [record for record in data if record[attr] == val]
        subset_entropy += val_prob * get_entropy(data_subset, target_attr)

    return (get_entropy(data, target_attr) - subset_entropy)
    

def get_majority_value(data, attr):
    frecuences = get_frecuences(data, attr)
    max_item = max(((frecuences[value], value) for value in frecuences))
    return max_item[1]


def get_frecuences(data, attr):
    """
    retuns dict {valor:frecuencia}
    """
    counter = defaultdict(int)
    for record in data:
        counter[record[attr]] += 1
    return counter


def get_values(data, attr):
    return {record[attr] for record in data}


def get_best_attribute(data, attributes, target_attr, fitness):
    """
    escoge el atributo que más reduce la entropía
    """
    best_pair = max(((fitness(data, attr, target_attr), attr)
        for attr in attributes if attr != target_attr))
    return best_pair[1]


def get_examples(data, attr, value):
    return [record for record in data if record[attr] == value]


def get_classification(record, tree):
    if isinstace(tree, basestring):
        return tree
    else:
        attr = tree.keys()[0]
        subtree = tree[attr][record[attr]]
        return get_classification(record, subtree)


def get_decision_tree(data, attributes, target_attr, fitness_func):
    values = get_values(data, target_attr)

    if not data or len(attributes) == 1:
        return get_majority_value(data, target_attr)
    if len(values) == 1:
        return values.pop()

    best_attr = get_best_attribute(data, attributes, target_attr, fitness_func)
    tree = {best_attr:{}}
    for value in get_values(data, best_attr):
        subdata = get_examples(data, best_attr, value)
        subtree = get_decision_tree(subdata,
            [attr for attr in attributes if attr != best_attr],
            target_attr,
            fitness_func)
        tree[best_attr][value] = subtree
    return tree
