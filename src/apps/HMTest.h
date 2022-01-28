#include <iostream>
// #include <random>
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
// #include <random>
#include <stdlib.h> 
#include <time.h>
#define DIM 50

void HelloWorld()
{
    using namespace std;
    std::cout << "Hello World" << std::endl;
}

std::tuple<std::vector<HMPoint>, std::vector<HMPoint>> //return value
generatePointsQD(unsigned int nPoints, unsigned int nQueries) {
		// srand(time(NULL));
		using namespace std;
		constexpr unsigned int dim = DIM; //string length
		
		std::vector<HMPoint> words;
		words.reserve(nPoints); //For vector

		std::vector<HMPoint> qWords;
		qWords.reserve(nPoints); //For vector
		int nQCount = 0;
		// 65-90

		char *myStr = (char*)malloc(dim * sizeof(char)); // For somereason, use array will cause additional char at the end
		for(int i=0; i<nPoints; i++)
		{
			for(int j=0; j<dim; j++)
			{
				myStr[j] = rand()%(90-65)+65;
				// cout<<myStr[j]<<endl;
			}
			string s = myStr;
			// cout<<s<<endl;
			// string s = "aaaaaa";
			HMPoint* word = new HMPoint(s, s);
			words.push_back(*word);
			free(word);

		}
		// int notInSet = nPoints; //rand()%(nPoints/50); // not 10 ()  not 10* xkoukun
		int notInSet = nQueries; //rand()%(nPoints/50); // not 10 ()  not 10* xkoukun
		cout<<"-----------"<<endl;
		for(int i=0; i<nQueries-notInSet; i++)
		{
			// words.push_back(words[rand()%nPoints]);
			qWords.push_back(words[rand()%nPoints]); // this should qwords why not before? guaibudehenduoreeixnyuneyuneixnkunsuan chubuliaoexinku yun kun zhongyuzhidao le ijiranshi qword why use nquaera meiyou shi nQ
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
			// cout<<s<<endl;
			HMPoint* word = new HMPoint(s, s);
			qWords.push_back(*word);
			free(word);
		}
		free(myStr);
		cout<<qWords.size()<<endl;
		return { words, qWords };
}


void radiusSearchTestEM(const std::string& fileNamePrefix) {
	//Set the DB sizes and number of queries that we want to test
	//std::map<unsigned int, unsigned int> nofPoints = getTestSizes(2, 10,18,1, 10000) ;
	//std::map<unsigned int, unsigned int> nofPoints{ {1000,100}, {10000,1000 } ,{100000,1000 } ,{1000000,1000 } };
	std::map<unsigned int, unsigned int> nofPoints{  {100,2 }  };
	int dim = DIM;
	//std::vector<float> radii {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
	std::vector<float> radii {1.0f};//, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

	//std::vector<float> lcmt_npivs {0.25, 0.5, 1.0, 2.0, 3.0 };
	//std::vector<int> cmt_madis {1000, 1};

	// std::vector<float> lcmt_npivs ;
	std::vector<int> cmt_madis {10, 100, 200, 300, 400, 500};

	std::set<PivotType> includePivotTypes{ PivotType::RAN};
	std::set<PartType>  includePartTypes{ PartType::BOM};
	bool hflag = true;
	std::vector<HMPoint> points, qPoints;
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


//@@@@

void radiusSearchCompareEM(unsigned int nPoints, const unsigned int nQueries, PivotType pivT, PartType partT, 
		const std::string& fileNamePrefix) {
	using namespace std;
	unsigned int bTime, sTime;
	using MetricType = HMMetric;
	MetricType met;
	unsigned int nqActual = 0;

	auto [points, qPoints] = generatePointsQD(nPoints, nQueries);

	auto start = std::clock();
	CMTree<HMPoint, MetricType> stree(points, met,pivT, partT, kxBalancedTreeHeight(1,points.size()));
	BruteForceSearch<HMPoint, MetricType> stree2(points, met); //This is not baseline
	// SPMTree<HMPoint, MetricType> stree2(points, met); //This is not baseline
	bTime = dTimeSeconds(start);
	cout << "radiusSearchTest btime=" << bTime << endl;

	std::set<unsigned int> depths;
	double radiusSum = stree.radiusSumAndDepths(depths);

	start = std::clock();
	unsigned int nFound = 0;
	unsigned int diffCount = 0;
	const unsigned int maxResults = 1000000;
	auto rad = 1.0;
	for (const auto& qp : qPoints) {
		/*if(nqActual == 2) {
			cout << "pq id="<<qp.getId() << endl;
			RadiusQuery<EuclidianPoint> rqt(qp, rad, maxResults);
			stree.search(rqt);
		}*/
		RadiusQuery<HMPoint> rq(qp, rad, maxResults);
		stree.search(rq);
	
		nFound += rq.getNeighbors().size();

		RadiusQuery<HMPoint> rq2(qp, rad, maxResults);
		stree2.search(rq2);

		if (!rq.hasSameNeighbors(rq2)) {
			diffCount++;
			
		}

	    nqActual++;
		if ((nqActual % 10000) == 0) { cout << "finished search i= " << nQueries << endl; }
	}
	sTime = dTimeSeconds(start);

	string runTimeFileName{ fileNamePrefix + "_rs_compare.csv"};
	ofstream theFileA(runTimeFileName, ios::app);
	theFileA << ";;TEST EMSC: " << currentDateTime()
		<< ";;[CLasses]:" << endl
		<< ";;[" << typeid(stree).name() << "]," << "[" << met << "]" << endl
		<< ";;[CLasses # 2]:" << endl
		<< ";;[" << typeid(stree2).name() << "]" << endl
		<< ";; Tree depths, min depth, max depth :" << depths.size() << ","
		<< *(std::min_element(depths.begin(), depths.end())) << "," << *(std::max_element(depths.begin(), depths.end())) << endl
		<< "dbSize,DiffCount,nQueries,nfound,radiusSu,Pivo,Partitio,<nodesVisited>,<numDistanceCalls>,btime,stime" << endl
		<< points.size() << "," << diffCount << "," << nqActual << "," << nFound << "," << radiusSum << ","
		<< stree.getPivotType() << "," << stree.getPartType() << ","
		<< (stree.getPerfStats().getNodesVisited() / nQueries) << ","
		<< (stree.getPerfStats().getDistanceCalls() / nQueries) << ","
		<< bTime << "," << sTime << endl;

	theFileA.close();
}




void radiusSearchCompareEM(const std::string& fileNamePrefix) {
	std::map<unsigned int, unsigned int> nofPoints{ {100,2}};
	// std::map<unsigned int, unsigned int> nofPoints{ {1000,100} };
	for (const auto& [np, nSkip] : nofPoints) {
		for (const auto& [pivType, pivVal] : pivotTypeMap) {
			for (const auto& [parType, parVal] : partTypeMap) {
				///cout << np << " " << pivType << " " << pivVal << endl; break;
				radiusSearchCompareEM(np, nSkip, pivType, parType, fileNamePrefix);
			}
		}
	}
}