#!/usr/bin/env bash

ROOT_DIR=../..

# ${ROOT_DIR}/llvm-build/bin/llvm-objdump -d --reloc ./doomgeneric.postrisc > doomgeneric.postrisc.s

# sudo perf stat -a --
# QT_QPA_PLATFORM=xcb

${ROOT_DIR}/postrisc_release/bin/qtpostrisc \
    --log-file "../../postrisc/docs/doom-log.html" \
    --profiling \
    --env "LS_COLORS=ow=1;105;30:di=1;34" \
    --env USER=user \
    --env LOGNAME=user \
    --env HOME=/home/user \
    --env NAME=DESKTOP \
    --env "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \
    --env HOSTTYPE=postrisc \
    --exeapp \
    -- \
    doomgeneric.postrisc

# console
# ${ROOT_DIR}/postrisc_release/bin/postrisc \
#    --log-file "doom-log.txt" \
#    --exeapp \
#    -- \
#    doomgeneric.postrisc
