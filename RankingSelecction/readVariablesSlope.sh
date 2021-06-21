#!/bin/bash

# Script to create a rank list with respect with their separation
# Usage: 

# Which root script do I use? (Write name without extension. Check script/ directory)
SCRIPT=Classification

# R Root version
source /home/david/Software/Root/root-6.20.04/compile/bin/thisroot.sh

# Where am I?
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# root ${SCRIPT}.C > variables.txt

filename=plotSlope.dat

if [ -s "${filename}" ]
then 
   echo "File exists and is not empty."
else
   echo "File does not exist, or is empty."
   exit 1
fi
mkdir VarScriptsSlope


nline=$(grep -n IdTransformation variables.txt | cut -d : -f 1)

if [ ${nline} -lt  0 ]; then
    echo "Ranking variable list was not created."
    exit 1
fi

nline=$((nline+3))


n=0
nranking=0

while read line; do
  nvar=$(echo ${line} | sed 's/[^0-9]*//g' )
  ranking=$((nline+nvar))
  var=$(sed -n ${ranking}p variables.txt | grep 'Variable' | cut -d : -f 3 | sed -e 's/^[ \t]*//' | sed 's/ *$//g')
  sline=$(grep -n "\"${var}\"" ${SCRIPT}.C | cut -d : -f 1)
  echo $sline
  sed -i -e ${sline}s#/##g ${SCRIPT}.C
  n=$((n+1))
done < $filename

sed -i s/Classification\(\)/Classification_${n}_slope\(\)/ ./${SCRIPT}.C  
cp ${SCRIPT}.C ./VarScriptsSlope/${SCRIPT}_${n}_slope.C
cp Classification_r.C Classification.C




