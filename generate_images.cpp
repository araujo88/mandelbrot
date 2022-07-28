#include <iostream>
#include <sstream> // for ostringstream
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <string.h>

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[])
{
    unsigned int max_it;
    unsigned int resx;
    unsigned int resy;
    double aspect_radio;
    double x_max, x_min, y_max, y_min;
    double x_offset, y_offset, zoom_point_x, zoom_point_y;
    char filename[1024];
    char base_filename[512] = "";
    int num_files;
    double scale;

    std::cout << "Initiating program..." << std::endl;

    if (argc < 11)
    {
        std::cout << "Insufficient number of arguments provided. Using default values." << std::endl;

        resx = 600;
        resy = 400;
        max_it = 100;
        x_min = -3;
        x_max = 0;
        y_min = -1;
        y_max = 1;
        strcat(base_filename, "mandelbrot");
        num_files = 10000;
        scale = 1 / 1.001;
    }
    else
    {
        resx = atoi(argv[1]);
        resy = atoi(argv[2]);
        max_it = atoi(argv[3]);
        x_min = atof(argv[4]);
        x_max = atof(argv[5]);
        y_min = atof(argv[6]);
        y_max = atof(argv[7]);
        strcat(base_filename, argv[8]);
        num_files = atoi(argv[9]);
        scale = atof(argv[10]);
    }

    aspect_radio = resx / resy;
    zoom_point_x = -1.5;
    zoom_point_y = -1;
    x_offset = -(zoom_point_x * (scale - 1));
    y_offset = -(zoom_point_y * (scale - 1));

    for (int i = 1; i < num_files + 1; i++)
    {
        sprintf(filename, "%s-%d.bmp", base_filename, i);
        char command[2048];
        sprintf(command, "./mandelbrot %u %u %u %lf %lf %lf %lf %s", resx, resy, max_it, x_min, x_max, y_min, y_max, filename);
        std::cout << exec(command) << std::endl;
        std::cout << filename << std::endl;
        x_min = x_min - x_offset;
        x_max = x_max + x_offset;
        y_min = y_min - y_offset;
        y_max = y_max + y_offset;
        // scale = scale * scale;
        // x_offset = -(zoom_point_x * (scale - 1));
        // y_offset = -(zoom_point_y * (scale - 1));
    }

    return 0;
}
