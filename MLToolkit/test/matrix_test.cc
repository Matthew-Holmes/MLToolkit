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
    ASSERT_NO_THROW(empty.sum_elements());
    ASSERT_NO_THROW(empty.sum_of_squared_elements());
    
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
}



/*
TEST(MatrixConstructor, InitFuncConstructor) {

}

*/

