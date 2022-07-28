#include <iostream>
#include "Complex/complex.hpp"
#include "EasyBMP/EasyBMP.hpp"

double scale(double val, double vmax, double vmin)
{
    return (val - vmin) / (vmax - vmin);
}

int main(int argc, char *argv[])
{
    unsigned int it;
    unsigned int max_it;
    unsigned int resx;
    unsigned int resy;
    double x_max, x_min, y_max, y_min;
    std::string filename;
    double diff;
    double x0;
    double y0;
    double intensity;
    int color_r;
    int color_g;
    int color_b;
    Complex z_temp;

    std::cout << "Initiating program..." << std::endl;

    if (argc < 9)
    {
        std::cout << "Insufficient number of arguments provided. Using default values." << std::endl;

        resx = 1000;
        resy = 1000;
        max_it = 100;
        x_min = -2.;
        x_max = 1.;
        y_min = -1.5;
        y_max = 1.5;
        filename = "mandelbrot.bmp";
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
        filename = argv[8];
    }

    std::cout << "Image width: " << resx << std::endl;
    std::cout << "Image height: " << resy << std::endl;
    std::cout << "Maximum number of iterations: " << max_it << std::endl;
    std::cout << "X min: " << x_min << std::endl;
    std::cout << "X max: " << x_max << std::endl;
    std::cout << "Y min: " << y_min << std::endl;
    std::cout << "Y max: " << y_max << std::endl;
    std::cout << "File name: " << filename << std::endl;

    // R, G, B [0, 255]
    EasyBMP::RGBColor black(0, 0, 0);
    // sizeX, sizeY, FileName, BackgroundColor
    EasyBMP::Image img(resx, resy, filename, black);

    for (unsigned int y = 0; y < resy; ++y)
    {
        for (unsigned int x = 0; x < resx; ++x)
        {
            it = 0;
            x0 = x_min + (x_max - x_min) * scale(x, resx, 0);
            y0 = y_min + (y_max - y_min) * scale(y, resy, 0);

            Complex c(x0, y0);
            Complex z(0, 0);

            do
            {
                z_temp = z;
                z = z * z + c;
                it++;
                diff = (z - z_temp).abs();
            } while ((isnanl(diff) == 0) && (it < max_it));

            intensity = 1 - (double)(it) / (double)max_it;

            color_r = int(520 / intensity);
            color_g = int(230 / intensity);
            color_b = int(310 / intensity);

            // PositionX, PisitionY, Color
            img.SetPixel(x, y, EasyBMP::RGBColor(color_r, color_g, color_b));
        }
    }

    img.Write();

    std::cout << "Image generated!" << std::endl;

    return 0;
}