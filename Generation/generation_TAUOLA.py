#/usr/bin/env python3
# -*- coding: utf-8 -*-
# Descriptor: tau lnv sample (MC13)

#############################################################
# Steering file for Tauola production, Accelerator conditions 
# without beam background
#
# August 2019 - Belle II Collaboration  
###############################################################

import basf2 as b2
from ROOT import Belle2
import mdst as mdst
import glob as glob

# set database conditions (in addition to default)
b2.conditions.reset()
b2.conditions.prepend_globaltag("mc_production_MC13a_rev1")

#: number of events to generate, can be overriden with -n
num_events = 1000

# create path
main = b2.create_path()

# specify number of events to be generated
main.add_module("EventInfoSetter", expList=1003, runList=0, evtNumList=num_events)

# use KKMC to generated tau lnv events
kkgeninput = b2.register_module('KKGenInput')
kkgeninput.param('tauinputFile', Belle2.FileSystem.findFile('data/generators/kkmc/tau.input.dat'))
kkgeninput.param('KKdefaultFile', Belle2.FileSystem.findFile('data/generators/kkmc/KK2f_defaults.dat'))
kkgeninput.param('kkmcoutputfilename', 'LogFile/kkmc_tautau.tex')
kkgeninput.param('taudecaytableFile', 'Data/tau_pi2munu.dat')

# run
main.add_module("Progress")
main.add_module(kkgeninput)
mdst.add_mdst_output(main, filename="RootFiles/tau_pi2munu_generation.root")
#main.add_module("PrintTauTauMCParticles", onlyPrimaries=False)


# process events and print call statistics
b2.process(main)
print(b2.statistics)

