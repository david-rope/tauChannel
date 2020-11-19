#!/bin/bash

# Script to generate Montecarlo data with Basf2 in the batch system
# Usage: gen_mc <start_num> <num_jobs>

# (If you don't want to use batch, just run: basf2 bf2scripts/<script>)

# Which basf2 script do I use to generate? (Write name without extension. Check script/ directory)
#SCRIPT=gen_tau_etapipi0nu_tagLeptonic
SCRIPT=generation_GEN_SIM_REC_wo_Bkg

# How many events to generate per job?
NUM_GENERATED=1000

# Bkg files
#export BELLE2_BACKGROUND_DIR=/group/belle2/BGFile/OfficialBKG/15thCampaign/bgoverlay_phase3

# Command to send jobs
case $( hostname ) in
# Acaxees
acaxees)
    BATCH="qsub"
    BASF2_SET="cd /cvmfs/belle.cern.ch/sl6 && source tools/b2setup && b2setup release-05-01-05 && cd"
;;
# KEKCC
# cc.kek.jp)
#    BATCH="bsub -q l"
#    COMMAND="sh"
#    # The location of release depends of the user
#    BASF2_SET="echo Basf2 not started in script"
# ;;
*)
    echo "[ERROR] No batch queue specified."
    exit 1
;;
esac

if [ "$#" -ne  2  ]; then
    echo "Usage: gen_mc <start_num> <num_jobs>"
    exit 1
fi

# Where am I?
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

INITJOB=$1
NJOBS=$2

Run=$INITJOB

mkdir -p $DIR/batch/
while [ $(($Run - $INITJOB)) -lt $NJOBS ]
do
RunNum=$((Run))
FILE=${SCRIPT}-${RunNum}-of-${NJOBS}

cat >  $DIR/batch/$FILE.sh <<EOF
#!/usr/bin/env bash

export BELLE2_NO_TOOLS_CHECK=True

# Set basf2 enviroment
cd /cvmfs/belle.cern.ch
source tools/b2setup 
b2setup release-05-01-05 
cd

# ${BASF2_SET}

# Is basf2 working?
if [ ! -z \$BELLE2_RELEASE ]; then
    echo "[INFO] Basf2 is working"
    echo "[INFO] \$BELLE2_RELEASE"
else
    echo "[ERROR] Basf2 enviroment not set."
    exit 1
fi

mkdir -p $DIR/batch/$FILE && cd $DIR/batch/$FILE
cp $DIR/scripts/$SCRIPT.py .

basf2 -o ${FILE}.mdst.root -n ${NUM_GENERATED} ${SCRIPT}.py 

mv -v ${FILE}.mdst.root ../${SCRIPT}-${RunNum}-of-${NJOBS}.mdst.root

cd ../ && rm -rf $FILE

EOF

$BATCH -o ${DIR}/batch/ -e ${DIR}/batch/ ${COMMAND}  batch/${FILE}.sh
echo $BATCH ${DIR}/batch/${FILE}.sh
sleep .125
Run=$((Run+1))
done
