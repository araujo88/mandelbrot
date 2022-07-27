#include <iostream>
#include "Complex/complex.hpp"
#include "EasyBMP/EasyBMP.hpp"

int min(int a, int b)
{
    return a < b ? a : b;
}

double scale(double val, double vmax, double vmin)
{
    return (val - vmin) / (vmax - vmin);
}

double fabs(double val)
{
    return val < 0 ? -val : val;
}

int main(int argc, char *argv[])
{
    unsigned int it;
    const unsigned int max_it = 300;
    double tol = 1e-3;
    double diff;
    unsigned int resx = 1000;
    unsigned int resy = 1000;
    double x_max = 0.47, x_min = -2.00, y_max = 1.12, y_min = -1.12;
    double x0;
    double y0;
    double intensity;
    int color_r;
    int color_g;
    int color_b;
    Complex z_temp;

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
                // std::cout << "diff: " << diff << std::endl;
            } while ((diff > tol) && (it < max_it));

            std::cout << "Iterations " << it << std::endl;

            intensity = (double)it / (double)max_it;
            color_r = int(255. * intensity / 2);
            color_g = int(255. * intensity);
            color_b = int(255. * 3 * intensity);

            // PositionX, PisitionY, Color
            img.SetPixel(x, y, EasyBMP::RGBColor(color_r, color_g, color_b));
        }
    }

    img.Write();

    return 0;
}