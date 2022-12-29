#include "test.h"

namespace {
    auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
    auto actn_func = [](double d) { return 1.0 / (1 + std::exp(-d)); };
    auto actn_grad = [](double d) { return actn_func(d) * (1 - actn_func(d)); };
    auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };
}

using mltoolkit::utility::makeCircleData;
 
TEST(TrainerDoTraining, ToyNeuralNetwork) {
    makeCircleData();
    mltoolkit::NeuralNetwork nnet(std::vector<int> {2, 10, 10, 1}, actn_func, rand_getter);

    mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(nnet,
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")));

    trainer.set_it_limit(1000);
    trainer.do_training();
    // trainer.evaluate();

    double should_be_zero = nnet.predict(std::vector<double>{0, 0})[0];
    double should_be_one = nnet.predict(std::vector<double>{-1, -1})[0];
    double max_difference = 0.05;

    EXPECT_THAT(0.0, ::testing::DoubleNear(should_be_zero, max_difference))
        << "(0,0) should be class 0" << std::endl;

    EXPECT_THAT(0.0, ::testing::DoubleNear(should_be_zero, max_difference))
        << "(-1,-1) should be class 1" << std::endl;
}

