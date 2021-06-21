for f in $(ls ./VarScripts/*.txt)
do 
    nline=$(grep -n ROC-integ $f | cut -d : -f 1)
    nline=$((nline+1))
    var=$(sed -n ${nline}p $f | grep 'RGLM' | cut -d : -f 3 | sed -e 's/^[ \t]*//' | sed 's/ *$//g')
    nvar=$(echo $f | sed 's/[^0-9]*//g' )
    echo $nvar $var >> plot.dat
done

