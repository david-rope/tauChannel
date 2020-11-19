#!/usr/bin/env python3

import basf2 as b2
import modularAnalysis as ma
import variables.collections as vc
import variables.utils as vu
import stdCharged as stdc
from variables import variables

# create path
my_path = b2.create_path()

# load input ROOT file                              
ma.inputMdst('default', '../Generation/RootFiles/tau_3pipi0mu_GEN_SIM_REC_test.mdst.root', path=my_path)                                                 

# create "pi+:all" ParticleList (and c.c.)
ma.fillParticleList('pi-:all','', path=my_path)
ma.fillParticleList('gamma:all', '', path=my_path)
ma.fillParticleList('mu+:all', '', path=my_path)

# reconstruct multiple tag side
ma.reconstructDecay('tau+:tag -> mu+:all', '', path=my_path)
ma.matchMCTruth('tau+:tag', path=my_path)

# reconstruct signal side
ma.reconstructDecay('pi0:can -> gamma:all gamma:all', '', path=my_path)
ma.matchMCTruth('pi0:can', path=my_path)
ma.reconstructDecay('tau-:sig -> pi+:all pi-:all pi-:all pi0:can', '', path=my_path)
ma.matchMCTruth('tau-:sig', path=my_path)

# reconstruct tau pair
ma.reconstructDecay('Upsilon(4S) -> tau+:tag tau-:sig', '', path=my_path)
ma.matchMCTruth('Upsilon(4S)', path=my_path)

# remove true reconstructed decays
variables.addAlias('tag1', 'daughter(0, daughter(0, mcPDG))')
variables.addAlias('sig1', 'daughter(1, daughter(0, mcPDG))')
variables.addAlias('sig2', 'daughter(1, daughter(1, mcPDG))')
variables.addAlias('sig3', 'daughter(1, daughter(2, mcPDG))')
variables.addAlias('sig4', 'daughter(1, daughter(3, mcPDG))')
variables.addAlias('sig40', 'daughter(1, daughter(3, daughter(0, mcPDG)))')
variables.addAlias('sig41', 'daughter(1, daughter(3, daughter(1, mcPDG)))')
variables.addAlias('isDecay', 'passesCut(tag1 == -13 and sig1 == 211 and sig2 == -211 and sig3 == -211 and sig4 == 111 and sig40 == 22 and sig41 == 22)')

# save information about the decay
decayDictionary = {'isDecay': 'mcPDG'}
ma.variableToSignalSideExtraInfo('Upsilon(4S)', decayDictionary, path=my_path)

decay_vars = ['isDecay']

# Select variable to save
# vc.mc_truth
gamma_vars = vc.kinematics + vc.cluster 

# vc.mc_truth +
charged_vars = vc.kinematics + vc.momentum_uncertainty + \
    vc.track + vc.track_hits + vc.pid + \
    vc.event_level_tracking 

# vc.mc_truth + \
tag_vars = vu.create_aliases_for_selected(list_of_variables=charged_vars,
                                          decay_string='tau+ -> ^mu+')

# vc.mc_truth + \
sig_vars = vu.create_aliases_for_selected(list_of_variables=gamma_vars,
                                          decay_string='tau- -> pi+ pi- pi- [pi0 -> ^gamma ^gamma]') + \
           vu.create_aliases_for_selected(list_of_variables=charged_vars,
                                          decay_string='tau- -> ^pi+ ^pi- ^pi- pi0')

# vc.mc_truth +
u4s_vars = decay_vars + vc.reco_stats + vc.deltae_mbc + \
    vu.create_aliases_for_selected(list_of_variables=tag_vars,
                                   decay_string='Upsilon(4S) -> ^tau+ tau-') + \
    vu.create_aliases_for_selected(list_of_variables=sig_vars,
                                   decay_string='Upsilon(4S) -> tau+ ^tau-')
 
# Saving variables to ntuple
rootOutputFile = 'Ntuples/tau3pipi0mu-Reconstruction_test.root'
ma.variablesToNtuple(decayString='Upsilon(4S)',
                     variables=u4s_vars,
                     filename=rootOutputFile,
                     treename='tree',
                     path=my_path)

# Process the events
b2.process(my_path)

# print out the summary
print(b2.statistics)
