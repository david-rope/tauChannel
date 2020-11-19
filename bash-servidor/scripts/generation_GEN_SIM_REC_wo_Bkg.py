#/usr/bin/env python3
# -*- coding: utf-8 -*-
# Descriptor: tau lnv tau- -> pi+ 2mu- nu (MC13)

#############################################################
# Steering file for official MC production of early phase 3
# 'tau lnv' samples without beam background
#
# August 2020 - Belle II Collaboration  
###############################################################

import basf2 as b2
import generators as ge
import simulation as si
import L1trigger as l1
import reconstruction as re
from ROOT import Belle2
import glob as glob

# background (collision) files
#bg = glob.glob('/group/belle2/users/jbennett/BG/early_phase3/prerelease-04-00-00a/overlay/phase31/BGx1/set0/*.root') # if you run at KEKCC
#bg = glob.glob('./bgoverlay*.root') # if you run at grid

# set database condition (in addition to default)
b2.conditions.reset()
b2.conditions.prepend_globaltag("mc_production_MC13a_rev1")

#: number of events to generate, can be overriden with -n
num_events = 50
#: output filename, can be overriden with -o
output_filename = "/home/david/BashBasf2/scripts/RootFiles/tau_3pipi0mu_GEN_SIM_REC_validation.mdst.root"

# create path
main = b2.create_path()

# specify number of events to be generated
main.add_module("EventInfoSetter", expList=1003, runList=0, evtNumList=num_events)

# use KKMC to generated tau lnv events
kkgeninput = b2.register_module('KKGenInput')
kkgeninput.param('tauinputFile', Belle2.FileSystem.findFile('data/generators/kkmc/tau.input.dat'))
kkgeninput.param('KKdefaultFile', Belle2.FileSystem.findFile('data/generators/kkmc/KK2f_defaults.dat'))
kkgeninput.param('kkmcoutputfilename', '/home/david/BashBasf2/scripts/LogFiles/kkmc_tau_3pipi0mu.tex')
kkgeninput.param('taudecaytableFile', '/home/david/BashBasf2/scripts/Data/tau_3pipi0mu.dat')
main.add_module(kkgeninput)

# detector simulation
si.add_simulation(main)

# trigger simulation
#l1.add_tsim(main, Belle2Phase="Phase3")

# reconstruction 
re.add_reconstruction(main)

# Finally add mdst output
re.add_mdst_output(main, filename=output_filename)

#main.add_module('ProgressBar')

# process events and print call statistics
b2.process(main)
print(b2.statistics)
