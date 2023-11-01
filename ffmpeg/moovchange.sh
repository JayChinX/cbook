#!/bin/bash
# dat for /R %%v IN (*.mp4) do ( ffmpeg -i %%v -vcodec h264  "path\%%~nv.mp4")
if [ $# == 0 ]; then
    for item in *.mp4; do
        ffmpeg -i ${item} -movflags faststart -c copy ${item%%.*}_mv.mp4
        # echo ${item%%.*}.mp4
    done
else
    for item in "$@"; do
        ffmpeg -i ${item} -movflags faststart -c copy ${item%%.*}_mv.mp4
    done

fi
