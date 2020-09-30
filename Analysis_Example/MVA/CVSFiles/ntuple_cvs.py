#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from basf2_mva_util import tree2dict
import numpy
import ROOT

rootchain = ROOT.TChain("tree")
rootchain.Add('train.root') 

variables = ['M', 'p', 'pz', 'pt', 'phi']

data = tree2dict(rootchain, variables, variables)

numpy.savetxt("foo.csv", data, delimiter=",")
