#! /bin/bash

function main()
{    
    parm="$0"
    board=${parm##*_}
    boadr_str='board='${board%.*}
    echo $boadr_str
    make $boadr_str
}

main $@