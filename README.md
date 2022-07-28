<img src="mandelbrot.jpg"/>

# mandelbrot

A simple Mandelbrot fractal generator written in C++ using EasyBMP library

## Basic usage

### Compile

`make clean`<br>
`make`

### Run

`./mandelbrot <image_height> <image_width> <max_number_of_iterations> <x_min> <x_max> <y_min> <y_max> <filename>` <br>

In case an insufficient number of arguments is passed, the default ones are used.

## Generating zoom video

### Requirements

ffmpeg

### Example

`./generate_images` <br>
`./generate_video.sh` <br>
