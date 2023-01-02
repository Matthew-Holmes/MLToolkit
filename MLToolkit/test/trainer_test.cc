#include "test.h"

namespace {
    auto rand_getter = []() { return (double)rand() / (double)RAND_MAX * 2 - 1; };
    auto actn_func = [](double d) { return 1.0 / (1 + std::exp(-d)); };
    auto actn_grad = [](double d) { return actn_func(d) * (1 - actn_func(d)); };
    auto errr_grad = [](double d1, double d2) { return 2 * (d1 - d2); };
}

using mltoolkit::utility::makeCircleData;
using mltoolkit::utility::makeTwoInputData;
using mltoolkit::utility::makeOneDimensionalData;

TEST(TrainerDoTraining, OverfitsTwoData) {
    makeTwoInputData();
    mltoolkit::NeuralNetwork nnet(std::vector<int> {3, 5, 10, 5, 2}, actn_func, rand_getter);
    //mltoolkit::NeuralNetworkMutator nnet_mut;

    mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(nnet,
        std::unique_ptr<mltoolkit::NeuralNetworkMutator>(new mltoolkit::NeuralNetworkMutator()),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("two_inputs_data.txt")),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("two_inputs_data.txt")));


    std::vector<double> invec1{ 0.2, 0.9, 0.2 };
    std::vector<double> outvec1{ 0.0, 1.0 };

    std::vector<double> invec2{ 0.9, 0.5, 0.05 };
    std::vector<double> outvec2{ 1.0, 0.0 };

    // check neural network isn't already predicting
    // TODO handle and exception and reroll nnet?

    double max_difference = 0.0001;

    std::vector<double> actual1 = nnet.predict(invec1);
    for (int i = 0; i != 2; i++)
        EXPECT_THAT(actual1[i], ::testing::Not(::testing::DoubleNear(outvec1[i], max_difference)));

    std::vector<double> actual2 = nnet.predict(invec2);
    for (int i = 0; i != 2; i++)
        EXPECT_THAT(actual2[i], ::testing::Not(::testing::DoubleNear(outvec2[i], max_difference)));

    trainer.set_it_limit(10000);
    trainer.do_training();
    trainer.evaluate();

    actual1 = nnet.predict(invec1);
    actual2 = nnet.predict(invec2);
    max_difference = 0.05;

    // check that now it predicts them correctly
    for (int i = 0; i != 2; i++) {
        EXPECT_THAT(actual1[i], ::testing::DoubleNear(outvec1[i], max_difference))
            << "datum 1 entry: " << i << " not fitted for" << std::endl;
        EXPECT_THAT(actual2[i], ::testing::DoubleNear(outvec2[i], max_difference))
            << "datum 2 entry: " << i << " not fitted for" << std::endl;
    }

}
 
TEST(TrainerDoTraining, LearnsOneDimensionalSeparator) {
    makeOneDimensionalData();
    mltoolkit::NeuralNetwork nnet(std::vector<int> {1, 3, 1}, actn_func, rand_getter);
    //mltoolkit::NeuralNetworkMutator nnet_mut;

    mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(nnet,
        std::unique_ptr<mltoolkit::NeuralNetworkMutator>(new mltoolkit::NeuralNetworkMutator()),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("one_dimensional_data.txt")),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("one_dimensional_data.txt")));

    std::vector<double> invec1{ -0.75 };
    std::vector<double> outvec1{ 0.0 };

    std::vector<double> invec2{ 0.75 };
    std::vector<double> outvec2{ 1.0 };

    // check neural network isn't already predicting
    // TODO handle and exception and reroll nnet?

    double max_difference = 0.0001;

    std::vector<double> actual1 = nnet.predict(invec1);
    EXPECT_THAT(actual1[0], ::testing::Not(::testing::DoubleNear(outvec1[0], max_difference)));

    std::vector<double> actual2 = nnet.predict(invec2);
    EXPECT_THAT(actual2[0], ::testing::Not(::testing::DoubleNear(outvec2[0], max_difference)));

    trainer.set_it_limit(10000);
    trainer.do_training();
    trainer.evaluate();

    actual1 = nnet.predict(invec1);
    actual2 = nnet.predict(invec2);
    max_difference = 0.05;

    // check that now it predicts them correctly

    EXPECT_THAT(actual1[0], ::testing::DoubleNear(outvec1[0], max_difference))
        << "datum 1 entry: not fitted for" << std::endl;
    EXPECT_THAT(actual2[0], ::testing::DoubleNear(outvec2[0], max_difference))
        << "datum 2 entry: not fitted for" << std::endl;
}

// TODO two dimensional linear separator

TEST(TrainerDoTraining, ToyNeuralNetwork) {
    makeCircleData();
    mltoolkit::NeuralNetwork nnet(std::vector<int> {2, 100, 2}, actn_func, rand_getter);
    //mltoolkit::NeuralNetworkMutator nnet_mut;

    mltoolkit::Trainer<mltoolkit::NeuralNetwork> trainer(nnet,
        std::unique_ptr<mltoolkit::NeuralNetworkMutator>(new mltoolkit::NeuralNetworkMutator()),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")),
        std::unique_ptr<mltoolkit::Data>(new mltoolkit::FileData("circle_data.txt")));


    trainer.set_it_limit(10000);
    trainer.do_training();
    trainer.evaluate();

    // TODO some sort of annealing process for learning rate - right now just getting useles models


    std::vector<double> vec1{ 0.0, 0.0 };
    std::vector<double> vec2{ -1.0, -1.0 };
    auto outvec1 = nnet.predict(vec1);
    auto outvec2 = nnet.predict(vec2);
    double should_be_zero = outvec1[0];
    double should_be_one = outvec2[0];
    double max_difference = 0.05;

    EXPECT_THAT(0.0, ::testing::DoubleNear(should_be_zero, max_difference))
        << "\n(0,0) should be class 0, in fact was:" << should_be_zero << std::endl;

    EXPECT_THAT(1.0, ::testing::DoubleNear(should_be_one, max_difference))
        << "\n(-1,-1) should be class 1, in fact was:" << should_be_one << std::endl;
}

