#!/bin/bash

ffmpeg -i mandelbrot-%d.bmp -r 20 -c:v libx264 -preset slow -crf 21 output.mp4