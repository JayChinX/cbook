#!/bin/bash

myArray=(1 2 3 4)

#
for j in "${myArray[*]}"; do
    echo "${j}"
done

echo "${myArray[*]}"

for j in "${myArray[@]}"; do
    echo "${j}"
done
echo "${myArray[@]}"

echo "${#myArray[@]}"
echo "${#myArray[*]}"