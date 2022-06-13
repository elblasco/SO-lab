#!/bin/bash

if [[ $# -ge 3 ]] || [[ $# -lt 2 ]];
  then
    echo "Troppi argomenti o troppo pochi"
  else
    rm $1
    make
    ./program $1 $2
    cat $1
fi