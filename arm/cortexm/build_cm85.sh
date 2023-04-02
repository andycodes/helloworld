#! /bin/bash

function main()
{    
    #build_cm85.sh board=cm85
    #make $1

    #build_cm85.sh
    parm="$0"
    board=${parm#*_}
    boadr_str='board='${board%.*}
    echo $boadr_str
    make $boadr_str
}

main $@