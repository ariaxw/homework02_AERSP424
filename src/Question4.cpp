#include <matplot/matplot.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

class AerodynamicsPlot {
private:
    const double PI = 3.14159265358979323846;

    // Calculate lift coefficient
    double calculateCL(double alpha, double CLalpha = 2 * PI) {
        double alphaRad = alpha * PI / 180.0;
        return CLalpha * sin(alphaRad);
    }

public:
    void plot() {
        using namespace matplot;

        // Generate data points
        std::vector<double> alpha = linspace(-20, 20, 200);
        std::vector<double> cl;
        
        // Calculate CL for each angle of attack
        for (const auto& a : alpha) {
            cl.push_back(calculateCL(a));
        }

        // Create the plot
        figure();
        plot(alpha, cl)->line_width(2).color("blue");
        
        // Customize the plot
        title("Lift Coefficient vs Angle of Attack");
        xlabel("Angle of Attack (degrees)");
        ylabel("Lift Coefficient (CL)");
        grid(on);
        
        // Add a horizontal line at CL = 0
        auto h = horline(0);
        h->line_style("--").color({0.5, 0.5, 0.5});
        
        // Add a vertical line at alpha = 0
        auto v = verline(0);
        v->line_style("--").color({0.5, 0.5, 0.5});

        // Optional: Save the plot
        // save("lift_coefficient.png");
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
        // Skip header
        std::getline(file, line);

        // Read data
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

        // Extract x and y coordinates
        std::vector<double> x_coords;
        std::vector<double> y_coords;
        std::vector<double> times;

        for (const auto& point : data) {
            times.push_back(point.time);
            x_coords.push_back(point.x);
            y_coords.push_back(point.y);
        }

        // Create figure with subplots
        figure();
        subplot(2, 1, 1);
        
        // Plot trajectory (x vs y)
        plot(x_coords, y_coords)->line_width(2).color("red");
        title("2D Trajectory");
        xlabel("X Position");
        ylabel("Y Position");
        grid(on);

        // Plot time series
        subplot(2, 1, 2);
        auto p1 = plot(times, x_coords);
        hold(on);
        auto p2 = plot(times, y_coords);
        hold(off);
        
        p1->line_width(2).color("blue");
        p2->line_width(2).color("green");
        
        title("Position vs Time");
        xlabel("Time");
        ylabel("Position");
        grid(on);
        legend({"X Position", "Y Position"});

        // Optional: Save the plots
        // save("trajectory_plots.png");
    }
};

int main() {
    // Part 1: Plot aerodynamics equation
    AerodynamicsPlot aeroPlot;
    aeroPlot.plot();
    matplot::show(); // Display the plot

    // Part 2: Plot CSV data
    TrajectoryPlot trajPlot;
    if (trajPlot.loadCSV("trajectory_data.csv")) {
        trajPlot.plot();
        matplot::show(); // Display the plots
    }

    return 0;
}
