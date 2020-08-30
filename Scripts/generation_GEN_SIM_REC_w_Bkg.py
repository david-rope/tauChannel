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
import background
#import os.path

# background (collision) files 
# location of the files is obtained from a shell variable - check first if it is set
#if 'BELLE2_BACKGROUND_DIR' not in os.environ:
#    b2.B2FATAL(
#        'BELLE2_BACKGROUND_DIR variable is not set. \n'
#        'Please export (setenv) the variable to the location of BG overlay sample. \n'
#        'Check https://confluence.desy.de/display/BI/Beam+background+samples to find them')  
# get list of files and check the list length
#bg = glob.glob(os.environ['BELLE2_BACKGROUND_DIR'] + '/*.root')
#if len(bg) == 0:
#    b2.B2FATAL('No files found in ', os.environ['BELLE2_BACKGROUND_DIR'])
# set database condition (in addition to default)
b2.conditions.reset()
b2.conditions.prepend_globaltag("mc_production_MC13a_rev1")

#: number of events to generate, can be overriden with -n
num_events = 1000
#: output filename, can be overriden with -o
output_filename = "RootFiles/tau_pi2munu_GEN_SIM_REC_5_Bkg.mdst.root"

# create path
main = b2.create_path()

# specify number of events to be generated
main.add_module("EventInfoSetter", expList=1003, runList=0, evtNumList=num_events)

# use KKMC to generated tau lnv events
kkgeninput = b2.register_module('KKGenInput')
kkgeninput.param('tauinputFile', Belle2.FileSystem.findFile('data/generators/kkmc/tau.input.dat'))
kkgeninput.param('KKdefaultFile', Belle2.FileSystem.findFile('data/generators/kkmc/KK2f_defaults.dat'))
kkgeninput.param('kkmcoutputfilename', 'LogFile/kkmc_tautau_GENSIMREC.tex')
kkgeninput.param('taudecaytableFile', 'Data/tau_pi2munu.dat')
main.add_module(kkgeninput)

# detector simulation
si.add_simulation(main, bkgfiles=background.get_background_files())

# trigger simulation
l1.add_tsim(main, Belle2Phase="Phase3")

# reconstruction 
re.add_reconstruction(main)

# Finally add mdst output
re.add_mdst_output(main, filename=output_filename)

# show progress of processing 
main.add_module('ProgressBar')

# process events and print call statistics
b2.process(main)
print(b2.statistics)

