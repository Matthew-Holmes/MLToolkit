#include "test.h"


void mltoolkit::utility::makeCircleData() {
    // data file found in e.g.
    // MLTookit\MLToolkit\build\x64 - Debug\test
    std::ifstream infile("circle_data.txt");
    if (infile.good()) {
        // std::cout << "File already exists. Skipping generation." << std::endl;
        return;
    }

    std::mt19937 engine;
    engine.seed(std::random_device{}());

    // Create distributions for the x- and y-coordinates
    std::uniform_real_distribution<double> dist_x(-1.5, 1.5);
    std::uniform_real_distribution<double> dist_y(-1.5, 1.5);

    // Open the output file
    std::ofstream out_file("circle_data.txt");

    // Generate 1000 data points
    for (int i = 0; i < 1000; i++) {
        // Generate a random point in the 2D plane
        double x = dist_x(engine);
        double y = dist_y(engine);

        // Determine if the point is inside or outside the circle
        int c = (x * x + y * y <= 1) ? 0 : 1;

        // Write the data point to the file
        out_file << x << ' ' << y << ", " << c << '\n';
    }

    // Close the output file
    out_file.close();

}

