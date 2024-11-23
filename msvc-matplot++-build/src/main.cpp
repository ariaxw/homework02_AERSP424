#include <cmath>
#include <vector>
#include <matplot/matplot.h>

void plot()
{
    using namespace matplot;
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y = transform(x, [](auto x)
                                      { return sin(x); });

    plot(x, y, "-o");
    hold(on);
    plot(x, transform(y, [](auto y)
                      { return -y; }),
         "--xr");
    plot(x, transform(x, [](auto x)
                      { return x / pi - 1.; }),
         "-:gs");
    plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "-ok");

    // Formatting
    title("cool title");
    xlabel("x-var");
    ylabel("y-var");
    hold("off");

    show();
    save("figure", "jpeg");
}

int main()
{
    // checkout matplotplusplus for more examples!
    // https://github.com/alandefreitas/matplotplusplus/blob/master/examples.md
    plot();
    return 0;
}