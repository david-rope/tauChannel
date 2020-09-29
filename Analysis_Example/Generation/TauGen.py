#!/usr/bin/env python3
# -*- coding: utf-8 -*-

########################################################
#
#
#  Generate 1000 generic BBbar events using EvtGen
#
#
########################################################

import os
import sys
from ROOT import Belle2

import basf2 as b2
import mdst as mdst
import generators as ge
import simulation as si
import reconstruction as re
import modularAnalysis as ma

# interpret the first input argument as decay file to facilitate testing of dec-files
dec_file = None
final_state = 'tau+tau-'
if len(sys.argv) > 1:
    dec_file = os.path.abspath(sys.argv[1])
    final_state = 'signal'
    print("using following decay file: "+ dec_file)

# main path
my_path = b2.create_path()

# event info setter
my_path.add_module("EventInfoSetter", expList=0, runList=1, evtNumList=10000)

# EvtGen
#ge.add_kkmc_generator(path=my_path, finalstate=final_state)
kkgeninput = b2.register_module('KKGenInput')
kkgeninput.param('tauinputFile', Belle2.FileSystem.findFile('data/generators/kkmc/tau.input.dat'))
kkgeninput.param('KKdefaultFile', Belle2.FileSystem.findFile('data/generators/kkmc/KK2f_defaults.dat'))                                  
kkgeninput.param('taudecaytableFile', Belle2.FileSystem.findFile('data/generators/kkmc/tau_decaytable.dat'))
kkgeninput.param('kkmcoutputfilename', 'LogFiles/kkmc_tautau_orig.txt')

my_path.add_module(kkgeninput)

# Simulation
si.add_simulation(path=my_path)

# Reconstruction
re.add_reconstruction(path=my_path)

# dump in MDST format
mdst.add_mdst_output(path=my_path, mc=True, filename='OutputFiles/taupair_upsilon4s.root')

#run
my_path.add_module("Progress")
# MC information
#my_path.add_module("PrintMCParticles", logLevel=b2.LogLevel.DEBUG, onlyPrimaries=False)

# generation events
b2.process(my_path)

# show call statistics
print(b2.statistics)
