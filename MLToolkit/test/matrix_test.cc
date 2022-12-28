#include "test.h"

// arrange --> act --> assert

TEST(MatrixConstructor, DefaultConstructor) {
    std::pair<int, int> default_size_pair(0,0);
    mltoolkit::Matrix emptyMat;
    EXPECT_EQ(emptyMat.size(), default_size_pair);
    // data is empty vector
    EXPECT_ANY_THROW(emptyMat.element_ij(0, 0));
}

void check_entries(mltoolkit::Matrix& mat,
    int rows, int cols, double fill) {
    int i = 0, j = 0; // so can use one incremented past allowed range
    for (/* empty */; i != rows; i++) {
        for (j = 0; j != cols; j++) {
            ASSERT_NEAR(mat.element_ij(i, j), fill, 0.00001);
        }
        ASSERT_ANY_THROW(mat.element_ij(i, j));
    }
    ASSERT_ANY_THROW(mat.element_ij(i, 0));
    EXPECT_ANY_THROW(mat.element_ij(i, j));
}

TEST(MatrixConstructor, SizeConstructor) {
    // expects 0.0 in every entry
    mltoolkit::Matrix empty(0, 0);
    mltoolkit::Matrix scalar(1, 1);
    mltoolkit::Matrix row(1, 10);
    mltoolkit::Matrix col(10, 1);
    mltoolkit::Matrix square(5, 5);
    mltoolkit::Matrix rectangle(3, 7); 
    mltoolkit::Matrix big(100, 200);
    
    // check every allowed entry is a 0.0
    // and trying to access anything else throws
    check_entries(empty, 0, 0, 0.0);
    check_entries(scalar, 1, 1, 0.0);
    check_entries(row, 1, 10, 0.0);
    check_entries(col, 10, 1, 0.0);
    check_entries(square, 5, 5, 0.0);
    check_entries(rectangle, 3, 7, 0.0);
    check_entries(big, 100, 200, 0.0);  
}

TEST(MatrixConstructor, SizeConstructorEdgeCases) {
    try {
        mltoolkit::Matrix negative_indices1(-5, 5);
        ADD_FAILURE() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices2(5, -5);
        ADD_FAILURE() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices3(-5, -5);
        ADD_FAILURE() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices4(-1, 0);
        ADD_FAILURE() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }


    try {
        mltoolkit::Matrix negative_indices5(0, -1);
        ADD_FAILURE() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }
    /*
    try
    {
        mltoolkit::Matrix float_indices1(2.5, 6.3);
        ADD_FAILURE() << "float indices allowed";
    }
    catch (...)
    {
        SUCCEED();
    }
    try
    {
        mltoolkit::Matrix float_indices2(2, 6.3);
        ADD_FAILURE() << "float indices allowed";
    }
    catch (...)
    {
        SUCCEED();
    }

    try
    {
        mltoolkit::Matrix float_indices3(2.5, 6, 0.4);
        ADD_FAILURE() << "float indices allowed";
    }
    catch (...)
    {
        SUCCEED();
    }
    */
}

TEST(MatrixConstructor, FillConstructor) {
    // expects 0.0 in every entry
    mltoolkit::Matrix empty(0, 0, 1.6);
    mltoolkit::Matrix scalar(1, 1, 1.0);
    mltoolkit::Matrix row(1, 10, -3.0);
    mltoolkit::Matrix col(10, 1, 5.6);
    mltoolkit::Matrix square(5, 5, 874.3456);
    mltoolkit::Matrix rectangle(3, 7, 37.373737);
    mltoolkit::Matrix big(100, 200, -10000);

    // check every allowed entry is a 0.0
    // and trying to access anything else throws
    check_entries(empty, 0, 0, 1.6);
    check_entries(scalar, 1, 1, 1.0);
    check_entries(row, 1, 10, -3.0);
    check_entries(col, 10, 1, 5.6);
    check_entries(square, 5, 5, 874.3456);
    check_entries(rectangle, 3, 7, 37.373737);
    check_entries(big, 100, 200, -10000);
}

TEST(MatrixConstructor, FillConstructorEdgeCases) {
    try {
        mltoolkit::Matrix negative_indices1(-5, 5, 1.0);
        FAIL() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices2(5, -5, -2.3);
        FAIL() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices3(-5, -5, 10);
        FAIL() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }

    try {
        mltoolkit::Matrix negative_indices4(-1, 0, -3.3);
        FAIL() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }


    try {
        mltoolkit::Matrix negative_indices5(0, -1, 100.001);
        FAIL() << "negative indices allowed";
    }
    catch (...) {
        SUCCEED();
    }
}

TEST(MatrixCumulation, Sums) {
    mltoolkit::Matrix blank(5, 5);
    mltoolkit::Matrix empty(0, 0, 1.0);
    mltoolkit::Matrix scalar(1, 1, 5);
    mltoolkit::Matrix row(1, 10, 0.1);
    mltoolkit::Matrix col(5, 1, -3.0);
    mltoolkit::Matrix square(5, 5, 0.2);
    mltoolkit::Matrix rectangle(3, 7, 10.0);
    mltoolkit::Matrix big(100, 200, -0.001);
    double eps = 0.0001;
    ASSERT_NEAR(blank.sum_elements(), 0.0, eps);
    ASSERT_NEAR(empty.sum_elements(), 0.0, eps);
    ASSERT_NEAR(scalar.sum_elements(), 5.0, eps);
    ASSERT_NEAR(row.sum_elements(), 1.0, eps);
    ASSERT_NEAR(col.sum_elements(), -15.0, eps);
    ASSERT_NEAR(square.sum_elements(), 5.0, eps);
    ASSERT_NEAR(rectangle.sum_elements(), 210.0, eps);
    ASSERT_NEAR(big.sum_elements(), -20.0, eps);
    ASSERT_NEAR(blank.sum_of_squared_elements(), 0.0, eps);
    ASSERT_NEAR(empty.sum_of_squared_elements(), 0.0, eps);
    ASSERT_NEAR(scalar.sum_of_squared_elements(), 25.0, eps);
    ASSERT_NEAR(row.sum_of_squared_elements(), 0.1, eps);
    ASSERT_NEAR(col.sum_of_squared_elements(), 45.0, eps);
    ASSERT_NEAR(square.sum_of_squared_elements(), 1.0, eps);
    ASSERT_NEAR(rectangle.sum_of_squared_elements(), 2100.0, eps);
    ASSERT_NEAR(big.sum_of_squared_elements(), 0.02, eps);   

    square.element_ij(2, 3) = 10.2;
    ASSERT_NEAR(square.sum_of_squared_elements(), 105.0, eps);
    ASSERT_NEAR(square.sum_elements(),15.0, eps);
    

}

TEST(MatrixConstructor, InitFuncConstructor) {
    auto f = []() {return 1.0; };
    mltoolkit::Matrix empty(0, 0, f);
    mltoolkit::Matrix scalar(1, 1, f);
    mltoolkit::Matrix row(1, 10, f);
    mltoolkit::Matrix col(5, 1, f);
    mltoolkit::Matrix square(5, 5, f);
    mltoolkit::Matrix rectangle(3, 7, f);
    mltoolkit::Matrix big(100, 200, f);
    check_entries(empty, 0, 0, 1.0);
    check_entries(scalar, 1, 1, 1.0);
    check_entries(row, 1, 10, 1.0);
    check_entries(col, 5, 1, 1.0);
    check_entries(square, 5, 5, 1.0);
    check_entries(big, 100, 200, 1.0);

    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0, 1);
    auto rand = [&u, &e]() {return u(e); };
    mltoolkit::Matrix random_mat(100, 100, rand);
    double eps = 0.01; // reasonable proximity to asymptotic results given number of samples
    ASSERT_NEAR(random_mat.sum_elements() / double(100 * 100), 0.5, eps) << "mean outside expected";
    ASSERT_NEAR(random_mat.sum_of_squared_elements() / double(100 * 100)
        - pow(random_mat.sum_elements() / double(100 * 100), 2.0), 1.0 / 12.0, eps)
        << "variance outside expected";
}

// TODO 2nd initfunc constructor test

TEST(MatrixVecMultiply, BasicTests) {
    {
        // Create a 3x3 matrix of all ones
        mltoolkit::Matrix A(3, 3, 1.0);
        std::vector<double> x{ 1, 2, 3 };

        // Compute the matrix-vector product
        std::vector<double> y = A.vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 3);
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(y[i], 6.0);
        }
    }

    // Chat GPT wrote this test!
    for (int i = 0; i < 10; ++i) {
        // Generate a random matrix and vector
        std::mt19937 gen(i);  // Seed the generator with the test number
        std::uniform_real_distribution<double> dist(0, 1);
        std::function<double(void)> rand_func = [&gen, &dist]() {
            return dist(gen);
        };
        int m = gen() % 10 + 1;
        int n = gen() % 10 + 1;
        mltoolkit::Matrix A(m, n, rand_func);
        std::vector<double> x(n);
        for (int k = 0; k < n; ++k) {
            x[k] = rand_func();
        }

        // Compute the matrix-vector product
        std::vector<double> y = A.vec_mult(x);

        // Check the result
        for (int j = 0; j < m; ++j) {
            double expected = 0.0;
            for (int k = 0; k < n; ++k) {
                expected += A.element_ij(j, k) * x[k];
            }
            EXPECT_NEAR(y[j], expected, 1e-9);
        }
    }
}

TEST(MatrixVecMultiply, ShapeEdgeCases) {
    // Test with a zero matrix
    {
        // Create a zero-sized matrix
        mltoolkit::Matrix A(0, 0);
        std::vector<double> x(0);

        // Compute the matrix-vector product
        std::vector<double> y = A.vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 0);
    }

    // Test the vec_mult method with a row matrix
    {
        // Create a row matrix
        mltoolkit::Matrix A(1, 5, 1.0);
        std::vector<double> x(5, 2.0);

        // Compute the matrix-vector product
        std::vector<double> y = A.vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 1);
        EXPECT_EQ(y[0], 10.0);
    }

    // Test the vec_mult method with a column matrix
    {
        // Create a column matrix
        mltoolkit::Matrix A(5, 1, 1.0);
        std::vector<double> x(1, 2.0);

        // Compute the matrix-vector product
        std::vector<double> y = A.vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 5);
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(y[i], 2.0);
        }
    }
}

TEST(MatrixTransposeVecMultiply, BasicTests) {
    {
        // Create a 3x3 matrix of all ones
        mltoolkit::Matrix A(3, 3, 1.0);
        std::vector<double> x{ 1, 2, 3 };

        // Compute the matrix-vector product
        std::vector<double> y = A.transpose_vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 3);
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(y[i], 6.0);
        }
    }

    for (int i = 0; i < 10; ++i) {
        // Generate a random matrix and vector
        std::mt19937 gen(i);  // Seed the generator with the test number
        std::uniform_real_distribution<double> dist(0, 1);
        std::function<double(void)> rand_func = [&gen, &dist]() {
            return dist(gen);
        };
        int m = gen() % 10 + 1;
        int n = gen() % 10 + 1;
        mltoolkit::Matrix A(m, n, rand_func);
        std::vector<double> x(m);
        for (int k = 0; k < m; ++k) {
            x[k] = rand_func();
        }

        // Compute the matrix-vector product
        std::vector<double> y = A.transpose_vec_mult(x);

        // Check the result
        for (int j = 0; j < n; ++j) {
            double expected = 0.0;
            for (int k = 0; k < m; ++k) {
                expected += A.element_ij(k, j) * x[k];
            }
            EXPECT_NEAR(y[j], expected, 1e-9);
        }
    }
}

TEST(MatrixTransposeVecMultiply, ShapeEdgeCases) {
    {
        // Create a zero-sized matrix
        mltoolkit::Matrix A(0, 0);
        std::vector<double> x(0);

        // Compute the transpose matrix-vector product
        std::vector<double> y = A.transpose_vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 0);
    }

    // Test the transpose_vec_mult method with a row matrix
    {
        // Create a row matrix
        mltoolkit::Matrix A(1, 5, 1.0);
        std::vector<double> x(1, 2.0);

        // Compute the matrix-vector product
        std::vector<double> y = A.transpose_vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 5);
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(y[i], 2.0);
        }
    }

    // Test the transpose_vec_mult method with a column matrix
    {
        // Create a column matrix
        mltoolkit::Matrix A(5, 1, 1.0);
        std::vector<double> x(5, 2.0);

        // Compute the matrix-vector product
        std::vector<double> y = A.transpose_vec_mult(x);

        // Check the result
        EXPECT_EQ(y.size(), 1);
        EXPECT_EQ(y[0], 10.0);
    }
}

TEST(MatrixVecMultiply, MismatchShapesThrow) {
    // Test the vec_mult method with an incompatible vector
    {
        // Create a matrix
        mltoolkit::Matrix A(2, 3, 1.0);
        std::vector<double> x(4, 2.0);

        // Check that the vec_mult method throws an exception
        EXPECT_THROW(A.vec_mult(x), std::invalid_argument);
    }

    {
        // Create a matrix
        mltoolkit::Matrix A(4, 2, 1.0);
        std::vector<double> x(4, 2.0);

        // Check that the vec_mult method throws an exception
        EXPECT_THROW(A.vec_mult(x), std::invalid_argument);
    }
}

TEST(MatrixTransposeVecMultiply, MismatchShapesThrow) {
    // Test the transpose_vec_mult method with an incompatible vector
    {
        // Create a matrix
        mltoolkit::Matrix A(2, 3, 1.0);
        std::vector<double> x(4, 2.0);

        // Check that the transpose_vec_mult method throws an exception
        EXPECT_THROW(A.transpose_vec_mult(x), std::invalid_argument);
    }

    {
        // Create a matrix
        mltoolkit::Matrix A(3, 4, 1.0);
        std::vector<double> x(4, 2.0);

        // Check that the transpose_vec_mult method throws an exception
        EXPECT_THROW(A.transpose_vec_mult(x), std::invalid_argument);
    }
}