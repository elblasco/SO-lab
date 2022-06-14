#!/bin/bash

if [[ -f $1 ]]; then
    while read line; do
        echo $(( line ))
    done < $1
else
    echo "?"
fi