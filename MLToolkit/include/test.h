#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "matrix.h"
#include "trainer.h"
#include "neuralnetwork.h"
#include "neuralnetworkmutator.h"
#include "filedata.h"

#include <random>
#include <cmath>
#include <functional>
#include <random>
#include <fstream>
#include <vector>

namespace mltoolkit {
	namespace utility {
		void makeCircleData();
		void makeTwoInputData();
	}
}