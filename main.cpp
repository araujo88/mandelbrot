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
    const unsigned int max_it = 100;
    double diff;
    unsigned int resx = 8000;
    unsigned int resy = 8000;
    double x_max = 1, x_min = -2, y_max = 1.5, y_min = -1.5;
    double x0;
    double y0;
    double intensity;
    int color_r;
    int color_g;
    int color_b;
    Complex z_temp;

    std::cout << "Initiating program..." << std::endl;

    // R, G, B [0, 255]
    EasyBMP::RGBColor black(0, 0, 0);
    // sizeX, sizeY, FileName, BackgroundColor
    EasyBMP::Image img(resx, resy, "mandelbrot.bmp", black);

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