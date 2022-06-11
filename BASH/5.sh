#!/bin/bash

ARRAY=()

for FILE in *; do
    ARRAY+=("$FILE")
done

for ((i=${#ARRAY[@]}-1;i>=0;i--)) do
    echo ${ARRAY[$i]}
done