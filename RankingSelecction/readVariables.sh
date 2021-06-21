#!/bin/bash

# Script to create a rank list with respect with their separation
# Usage: 

# Which root script do I use? (Write name without extension. Check script/ directory)
SCRIPT=Classification

# R Root version
source /home/david/Software/Root/root-6.20.04/compile/bin/thisroot.sh

# Where am I?
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# root ${SCRIPT}_all.C > variables.txt

nline=$(grep -n IdTransformation variables.txt | cut -d : -f 1)

if [ ${nline} -lt  0 ]; then
    echo "Ranking variable list was not created."
    exit 1
fi

nline=$((nline+4))
nvar=1
mkdir VarScripts

var=$(sed -n ${nline}p variables.txt | grep 'Variable' | cut -d : -f 3 | sed -e 's/^[ \t]*//' | sed 's/ *$//g')

while [ -n "$var" ]; do
    echo ${var}
    sline=$(grep -n "\"${var}\"" ${SCRIPT}.C | cut -d : -f 1)
    sed -i -e ${sline}s#/##g ${SCRIPT}.C
    cp ${SCRIPT}.C ./VarScripts/${SCRIPT}_${nvar}.C
    sed -i s/Classification\(\)/Classification_${nvar}\(\)/ ./VarScripts/${SCRIPT}_${nvar}.C  
    nvar=$((nvar+1))
    nline=$((nline+1))
    var=$(sed -n ${nline}p variables.txt | grep 'Variable' | cut -d : -f 3 | sed -e 's/^[ \t]*//' | sed 's/ *$//g')
done

echo "All scripts were created."

pwd 
for f in $(ls ./VarScripts/*.C)
do 
    root -b -l -q ${f} > ${f}.txt
    sleep 1
done

cp Classification_r.C Classification.C

