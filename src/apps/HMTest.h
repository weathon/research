#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <numeric>
#include <unordered_map>
#include <array>
#include <string>
#include <map>

#include "Misc.h"
#include "Query.h"
#include "Metric.h"
#include "SearchCommon.h"
#include "SPMTree.h"
#include "CMTree.h"
#include "BruteForceSearch.h"

#include "TestCommon.h"


void HelloWorld()
{
    using namespace std;
    std::cout << "Hello World" << std::endl;
}

void collectSearchTestEMAutoRad(const std::string& fileNamePrefix, int nrad, float maxRadPct) {
	std::map<unsigned int, unsigned int> nofPoints{{10000,100 } ,{100000,100 } , {1000000,100 } , {10000000,100 }};
	//std::map<unsigned int, unsigned int> nofPoints{{10000,100 } ,{100000,100 } , {1000000,100 }};
	//std::map<unsigned int, unsigned int> nofPoints{{10000000,100 }};
    std::vector<float> radii;
	bool rangeSearchToo = true;
	

	std::set<PivotType> includePivotTypes{ PivotType::RAN}; 
	std::set<PartType>  includePartTypes{ PartType::BOM };

	std::vector<int> cmt_madis{1,1000}; // {1};
	std::vector<int> spmt_madis{0};// {0};


	bool hflag = true;
	std::vector<std::string> points, qPoints;
	for (const auto& [np, nQueries] : nofPoints) {
		auto [points, qPoints] = generatePointsQD(np, nQueries);
		std::array<EuclidianPointPointType, EuclidianPointDim> boxO,boxP;
		getDataBounds(points, boxO, boxP);
		EuclidianPoint pO("0", boxO);
		EuclidianPoint pP("P", boxP);
		auto maxDist = pO.distance(pP);
		maxDist *= maxRadPct;

		float delta = 3.0 / nrad;

		radii.clear();
		for (int i = 0; i <= nrad; i++){
			radii.push_back(i * delta * maxDist);
		}


		for (const auto& pivType  : includePivotTypes) {
			for (const auto& partType : includePartTypes) {
				for (const auto& madi : cmt_madis){
					collectSearchTest<std::string, HMMetric,CMTree<std::string, HMMetric>>
					(points, qPoints, , radii, false, pivType, partType, madi, fileNamePrefix, hflag, rangeSearchToo);
					if (hflag == true) {hflag = false;}
				}
				for (const auto& madi : spmt_madis){
					collectSearchTest<std::string, HMMetric,SPMTree<Euclidiastd::stringnPoint, HMMetric>>
					(points, qPoints, , radii, false, pivType, partType, madi, fileNamePrefix, hflag, rangeSearchToo);
					if (hflag == true) {hflag = false;}
				}
			}
		}
	}
}