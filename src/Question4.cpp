#include <matplot/matplot.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

class AerodynamicsPlot {
private:
    static constexpr double PI = 3.14159265358979323846;

    // Calculate lift coefficient
    double calculateCL(double alpha, double CLalpha = 6.28318530718) {
        double alphaRad = alpha * PI / 180.0;
        return CLalpha * sin(alphaRad);
    }

public:
    void plot() {
        using namespace matplot;

        // Generate data points
        std::vector<double> alpha = linspace(-20, 20, 200);
        std::vector<double> cl;

        for (const auto& a : alpha) {
            cl.push_back(calculateCL(a));
        }

        // Create plot
        matplot::plot(alpha, cl)->line_width(2).color("blue");
        matplot::title("Lift Coefficient vs Angle of Attack");
        matplot::xlabel("Angle of Attack (degrees)");
        matplot::ylabel("Lift Coefficient (CL)");
        matplot::grid(true);

        // Add lines
        matplot::plot(std::vector<double>{-20, 20}, std::vector<double>{0, 0}, "--")->color({0.5, 0.5, 0.5});
        matplot::plot(std::vector<double>{0, 0}, std::vector<double>{-1, 1}, "--")->color({0.5, 0.5, 0.5});
    }
};

class TrajectoryPlot {
private:
    struct DataPoint {
        double time;
        double x;
        double y;
    };
    std::vector<DataPoint> data;

public:
    bool loadCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            DataPoint point;

            std::getline(ss, value, ',');
            point.time = std::stod(value);
            std::getline(ss, value, ',');
            point.x = std::stod(value);
            std::getline(ss, value, ',');
            point.y = std::stod(value);

            data.push_back(point);
        }

        return true;
    }

    void plot() {
        using namespace matplot;

        if (data.empty()) {
            std::cerr << "No data to plot!" << std::endl;
            return;
        }

        std::vector<double> x_coords;
        std::vector<double> y_coords;
        std::vector<double> times;

        for (const auto& point : data) {
            times.push_back(point.time);
            x_coords.push_back(point.x);
            y_coords.push_back(point.y);
        }

        // Subplot 1
        matplot::subplot(2, 1, 1);
        matplot::plot(x_coords, y_coords)->line_width(2).color("red");
        matplot::title("2D Trajectory");
        matplot::xlabel("X Position");
        matplot::ylabel("Y Position");
        matplot::grid(true);

        // Subplot 2
        matplot::subplot(2, 1, 2);
        matplot::plot(times, x_coords)->line_width(2).color("blue");
        matplot::plot(times, y_coords)->line_width(2).color("green");
        matplot::title("Position vs Time");
        matplot::xlabel("Time");
        matplot::ylabel("Position");
        matplot::grid(true);
        matplot::legend(std::vector<std::string>{"X Position", "Y Position"});
    }
};

int main() {
    AerodynamicsPlot aeroPlot;
    aeroPlot.plot();
    matplot::show();

    TrajectoryPlot trajPlot;
    if (trajPlot.loadCSV("trajectory_data.csv")) {
        trajPlot.plot();
        matplot::show();
    }

    return 0;
}

