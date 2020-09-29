#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Thomas Keck 2016

# Use training in a basf2 path
# Run basics/*.py before

from basf2 import *
from modularAnalysis import *
import create_data_sample

if __name__ == "__main__":
    path = create_data_sample.reconstruction_path(['../../DST_Data/mdst.physics.0010.05154.HLT0.hlt_hadron.f00000.root'])
    path.add_module('MVAExpert', listNames=['D0'], extraInfoName='Test', identifier='weightfile.root')
    variablesToNtuple('D0', ['isSignal', 'extraInfo(Test)'], path=path)
    process(path)
