//#define SA_USE_STATIC_DI

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <regex>

#include "HMTest.h"

#ifdef __WIN32
unsigned int DistanceIntervalSM<float>::used = 0;
std::vector< DistanceIntervalSM<float>> DistanceIntervalSM<float>::data;
#endif

int main(int argc, char* argv[]) {
    using namespace std;
    radiusSearchTestEM("HM_");
}