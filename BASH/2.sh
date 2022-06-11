#!/bin/bash

if [[ -e $1 ]]; then
    if [[ -f $1 ]]; then
        echo "file"
        else
        echo "cartella"
    fi
    else
    echo "?"
fi