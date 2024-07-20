#! /bin/bash
#https://github.com/HBehrens/puncover

#https://github.com/jedrzejboczar/elf-size-analyze
#python -m elf_size_analyze -t arm-none-eabi- /project/h/arm/cortexm/bin/mps3-an547/felix.elf -

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
