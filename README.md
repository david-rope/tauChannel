# Tau Channel

Here, we present the study of the tau- -> pi+ mu- mu- nu_tau channel in Belle II using different multivariate algorithms (included in TMVA for ROOT).

But before starting the algorithms training we need to generate our samples. This is done, first with the configuration for tau- -> pi+ mu- mu- nu_tau channel that will be used for the KKMC simulator.  This configuration files (other channels can be included) is in the folder Data.

The number of events to generate, the database conditions for the detector and trigger conditions are set in the Generation folder's scripts. Please see documentation to observe the three different options. 

Then, a preselection should be done because the Belle II experiment generated not only our channel. It can produce pairs of c quarks (ccbar),  pairs of s quarks (ssbar), pairs of b quarks (bbbar), pairs of muon leptons (mupair), pairs of electron leptons (bhabha), pairs of tau leptons (taupair - here it is our channel), ect. And all of these pairs can decay in different ways but with some common characteristics. Which means we may not be able to run (Belle II requirements) our analysis (application of the trained algorithms) over all data. We have to preselect the taupair sample with global variables or main features of our channel. These scripts will be in the Preselection folder.

With the preselection done, we can use all  variables (kinematics, deposited energy, pid,...) for each particle (pi, electron, muon,...) as well as global/event variables (thrust, total deposited energy, total electric charged, missed  energy,...) to train the algorithms availables in TMVA, compare them,...
Also, basf2 offers other options of multivariate analysis that can be used or try different software not included in basf2.


   
    
 

