#!/bin/bash

# Script to run an input script with batch system.
# It takes a script and runs it in all the files of a directory

# Which script do you want to run (at scritps)?
SCRIPT=reconstruct_tau_3pipi0.py
#SCRIPT=$1

# Input dir - you need to move all files created by gen_mc.sh
# to rootFiles (rootFiles also needs to be created)
INPUTDIR=/home/david/BashBasf2/batch/rootFiles/
#INPUTDIR=$2

OUTNAME=tau_3pipi0

# Command to send jobs
case $( hostname ) in
# Jaguar
acaxees)
    BATCH="qsub"
    BASF2_SET="cd /cvmfs/belle.cern.ch/sl6 && source tools/b2setup && b2setup release-05-01-05 && cd"
;;
# KEKCC
cc.kek.jp)
    BATCH="bsub -q l"
    COMMAND="bash"
    # The location of release depends of the user
    BASF2_SET="cd /cvmfs/belle.cern.ch/sl6 && source tools/b2setup && cd releases/release-02-00-02 && b2setup && cd"
;;
*)
    echo "[ERROR] No batch queue specified."
    exit 1
;;
esac

# Where am I?
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

INITJOB=1
NJOBS=$(ls $INPUTDIR | wc -l)

echo "Num of jobs: " $NJOBS

Run=0

mkdir -p $DIR/batchN/
for f in $(ls $INPUTDIR/*.root)
do
RunNum=$((Run))
FILE=${OUTNAME}-${RunNum}-of-${NJOBS}

cat >  $DIR/batchN/$FILE.sh <<EOF
#!/usr/bin/env bash

export BELLE2_NO_TOOLS_CHECK=True

# Set basf2 enviroment
${BASF2_SET}

# Is basf2 working?
if [ ! -z \$BELLE2_RELEASE ]; then
    echo "[INFO] Basf2 is working"
    echo "[INFO] \$BELLE2_RELEASE"
else
    echo "[ERROR] Basf2 enviroment not set."
    exit 1
fi

mkdir -p $DIR/batchN/$FILE && cd $DIR/batchN/$FILE
cp $DIR/scripts/$SCRIPT .

mkdir Ntuples

basf2 -i ${f} ${SCRIPT}

mv -v Ntuples/*.root ../${SCRIPT}-${RunNum}-of-${NJOBS}.mdst.root

cd ../ && rm -rf $FILE

EOF
$BATCH -o ${DIR}/batchN/ -e ${DIR}/batchN/ ${COMMAND} batchN/${FILE}.sh
echo $BATCH ${DIR}/batchN/${FILE}.sh
sleep 0.1
Run=$((Run+1))
done
