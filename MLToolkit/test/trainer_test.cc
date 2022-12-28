#include "test.h"

void makeCircleData() {
    // data file found in e.g.
   // MLTookit\MLToolkit\build\x64 - Debug\test
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
 /*
TEST(TrainerDoTraining, ToyNeuralNetwork) {
    makeCircleData();

    auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
    auto actn_func = [](double d) { return 1.0 / (1 + std::exp(-d)); };
    auto actn_grad = [actn_func](double d) { return actn_func(d) * (1 - actn_func(d)); };
    auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };

    mltoolkit::NeuralNetwork nnet(std::vector<int> {2, 10, 1}, actn_func, rand_getter);

    mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(nnet,
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")));

    trainer.set_it_limit(1000);
    trainer.do_training();
    trainer.evaluate();

    std::cout << nnet.predict(std::vector<double>{0, 0})[0] << std::endl; // should be 0
    std::cout << nnet.predict(std::vector<double>{-1, -1})[0];  // should be 1
}

*/