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
#include <stdlib.h>

#include "Misc.h"
#include "Query.h"
#include "Metric.h"
#include "SearchCommon.h"
#include "SPMTree.h"
#include "CMTree.h"
#include "BruteForceSearch.h"

#include "TestCommon.h"
#define DIM 50

void HelloWorld()
{
    using namespace std;
    std::cout << "Hello World" << std::endl;
}

std::tuple<std::vector<HMPoint>, std::vector<HMPoint>> //return value
generatePointsQD(unsigned int nPoints, unsigned int nQueries) {
		using namespace std;
		constexpr unsigned int dim = DIM; //string length
		
		std::vector<HMPoint> words;
		words.reserve(nPoints); //For vector

		std::vector<HMPoint> qWords;
		qWords.reserve(nPoints); //For vector
		int nQCount = 0;
		// 65-90

		char myStr[dim];
		for(int i=0; i<nPoints; i++)
		{
			for(int j=0; j<dim; j++)
			{
				myStr[j] = rand()%(90-65)+65;
			}
			string s = myStr;
			// string s = "aaaaaa";
			HMPoint* word = new HMPoint(s, s);
			words.push_back(*word);
			free(word);

		}
		int notInSet = rand()%(nPoints/50); // not 10 ()  not 10* xkoukun

		for(int i=0; i<nQueries-notInSet; i++)
		{
			// words.push_back(words[rand()%nPoints]);
			qWords.push_back(words[rand()%nPoints]); // this should qwords why not before? guaibudehenduoreeixnyuneyuneixnkunsuan chubuliaoexinku
			// qWords.push_back(words[rand()%nPoints]);
		}
		cout<<"notInSet: "<<notInSet<<endl;
		for(int i=0; i<notInSet; i++)
		{
			for(int j=0; j<dim; j++)
			{
				myStr[j] = rand()%(90-65)+65;
			}
			string s = myStr;
			// string s = "aaaaaa";
			HMPoint* word = new HMPoint(s, s);
			qWords.push_back(*word);
			free(word);
		}
		return { words, qWords };
}


void radiusSearchTestEM(const std::string& fileNamePrefix) {
	//Set the DB sizes and number of queries that we want to test
	//std::map<unsigned int, unsigned int> nofPoints = getTestSizes(2, 10,18,1, 10000) ;
	//std::map<unsigned int, unsigned int> nofPoints{ {1000,100}, {10000,1000 } ,{100000,1000 } ,{1000000,1000 } };
	std::map<unsigned int, unsigned int> nofPoints{  {20000,2000 }  };
	int dim = DIM;
	//std::vector<float> radii {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
	std::vector<float> radii {1.0f, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

	//std::vector<float> lcmt_npivs {0.25, 0.5, 1.0, 2.0, 3.0 };
	//std::vector<int> cmt_madis {1000, 1};

	// std::vector<float> lcmt_npivs ;
	std::vector<int> cmt_madis {10, 100, 200, 300, 400, 500};

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
					radiusSearchTest<HMPoint, HMMetric,CMTree<HMPoint, HMMetric>>
					(points, qPoints, dim, radii, pivType, partType, madi, fileNamePrefix, hflag);
					//fileNamePrefix -> output file
					hflag = false; //Dont print header after 1st time.
				}
			}
		}
	}
}