#! /bin/bash

function main()
{    
    ./clean.sh
    parm="$0"
    board=${parm##*_}
    boadr_str='board='${board%.*}
    echo $boadr_str
    make $boadr_str
}

main $@
