#!/bin/bash

if [[ -f $1 ]];
    then
        rm $1
        make
    else
        make
fi