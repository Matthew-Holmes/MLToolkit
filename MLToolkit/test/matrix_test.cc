#include "matrix.h"
#include "gtest/gtest.h"

// arrange --> act --> assert

TEST(MatrixConstructor, DefaultConstructor) {
    std::pair<int, int> default_size_pair(0,0);
    mltoolkit::Matrix emptyMat;
    EXPECT_EQ(emptyMat.size(), default_size_pair);
    // data is empty vector
    EXPECT_ANY_THROW(emptyMat.element_ij(0, 0));
}


void check_entries(mltoolkit::Matrix& mat,
    int rows, int cols, int fill) {
    int i = 0, j = 0; // so can use one incremented past allowed range
    for (/* empty */; i != rows; i++) {
        for (j = 0; j != cols; j++) {
            EXPECT_NEAR(mat.element_ij(i, j), fill, 0.00001);
        }
        EXPECT_ANY_THROW(mat.element_ij(i, j));
    }
    EXPECT_ANY_THROW(mat.element_ij(i, 0));
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

}