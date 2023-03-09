#!/bin/bash
# dat for /R %%v IN (*.mp4) do ( ffmpeg -i %%v -vcodec h264  "path\%%~nv.mp4")

for item in *.mp4; do
    ffmpeg -i ${item} -movflags faststart -c copy  ${item%%.*}_nv.mp4
    # echo ${item%%.*}.mp4
done

