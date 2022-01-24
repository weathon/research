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

std::tuple<std::vector<HMPoint>, std::vector<HMPoint>>
generatePointsQD(unsigned int nPoints, unsigned int nQueries, const double density = 1.0f) {
		using namespace std;
		constexpr unsigned int dim = 100; //string length
		auto width = ceil(pow((nPoints / density), 1.0 / dim));

		std::array< EuclidianPointPointType, dim> boxO;
		std::array< EuclidianPointPointType, dim> boxP;
	
		auto frac = 0.01;
		
		for (int i = 0; i < dim; i++) {
			boxO[i] = 0.0f + width * frac;
			boxP[i] = (1.0 - frac) * width ;
		}

		std::clock_t start = std::clock();
		std::vector<EuclidianPoint> dbPoints =
			genEuclidianPointsUniform<dim, EuclidianPointPointType>(nPoints, 0.0f, width);
		std::cout << "dataGenTime=" << dTimeSeconds(start) << std::endl;

		//And the query points ...
		auto qPoints = getInteriorPoints<float, dim>(dbPoints, boxO, boxP);
		qPoints = getSubsetRandom(qPoints, nQueries);

		//TODO: verify we dont need std::move usage.
		return { dbPoints, qPoints };
}


void radiusSearchTestEM(const std::string& fileNamePrefix) {
	//Set the DB sizes and number of queries that we want to test
	//std::map<unsigned int, unsigned int> nofPoints = getTestSizes(2, 10,18,1, 10000) ;
	//std::map<unsigned int, unsigned int> nofPoints{ {1000,100}, {10000,1000 } ,{100000,1000 } ,{1000000,1000 } };
	std::map<unsigned int, unsigned int> nofPoints{  {10000,1000 }  };

	//std::vector<float> radii {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
	std::vector<float> radii {1.0f};

	//std::vector<float> lcmt_npivs {0.25, 0.5, 1.0, 2.0, 3.0 };
	//std::vector<int> cmt_madis {1000, 1};

	// std::vector<float> lcmt_npivs ;
	std::vector<int> cmt_madis {1000};

	std::set<PivotType> includePivotTypes{ PivotType::RAN};
	std::set<PartType>  includePartTypes{ PartType::BOM};

	bool hflag = true;
	std::vector<EuclidianPoint> points, qPoints;
	for (const auto& [np, nQueries] : nofPoints) {
		auto [points, qPoints] = generatePointsQD(np, nQueries); 
		//auto [points, qPoints] = generatePointsQDClustered(nClusters ,nPointsPer, nQueries);
		for (const auto& pivType  : includePivotTypes) {
			for (const auto& partType : includePartTypes) {
				for (const auto& madi : cmt_madis){
					radiusSearchTest<EuclidianPoint, EuclidianMetric,CMTree<EuclidianPoint, EuclidianMetric>>
					(points, qPoints, EuclidianPointDim, radii, pivType, partType, madi, fileNamePrefix, hflag);
					//fileNamePrefix -> output file
					hflag = false; //Dont print header after 1st time.
				}
			}
		}
	}
}