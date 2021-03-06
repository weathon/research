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
#define DIM 100
#define lessDifference false

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
		for(int j=0; j<dim; j++)
		{
			myStr[j] = rand()%(2)+65;
			// cout<<myStr[j]<<endl;
		}
		string s = myStr;
		HMPoint* word = new HMPoint(s, s);
		words.push_back(*word);
		free(word);
		for(int i=1; i<nPoints; i++)
		{
			if(lessDifference)
			// string lastString = qWords[i-1].getValue(); //shunxu xkou 
			{
				string lastString = words[i-1].getValue(); //shunxu xkou 
				lastString[rand()%DIM]=rand()%(2)+65;
				// cout<<lastString<<endl;
				// qWords.push_back(lastString); 
				// HMPoint* word = new HMPoint(lastString, lastString);
				HMPoint* word = new HMPoint(lastString, lastString);
				words.push_back(*word);
				free(word);
			}
			else
			{
				for(int j=0; j<dim; j++)
				{
					myStr[j] = rand()%2+65;
				}
				string s = myStr;
				// string s = "aaaaaa";
				// cout<<s<<endl;
				HMPoint* word = new HMPoint(s, s);
				words.push_back(*word);
				free(word);
			}

		}

		// int notInSet = nPoints; //rand()%(nPoints/50); // not 10 ()  not 10* xkoukun
		int notInSet = 0;rand()%(nQueries/50); // not 10 ()  not 10* xkoukun
		cout<<"-----------"<<endl;
		// qWords.push_back(words[rand()%nPoints]);
		for(int i=0; i<nQueries-notInSet; i++)
		{
			qWords.push_back(words[rand()%nPoints]);
		}
		cout<<"notInSet: "<<notInSet<<endl;
		for(int i=0; i<notInSet; i++)
		{
			for(int j=0; j<dim; j++)
			{
				myStr[j] = rand()%(2)+65;
			}
			string s = myStr;
			// string s = "aaaaaa";
			// cout<<s<<endl;
			HMPoint* word = new HMPoint(s, s);
			qWords.push_back(*word);
			free(word);
		}
		free(myStr);
		// cout<<qWords[0]<<endl;
		cout<<qWords.size()<<endl;
		return { words, qWords };
}


void radiusSearchTestEM(const std::string& fileNamePrefix) {
	//Set the DB sizes and number of queries that we want to test
	//std::map<unsigned int, unsigned int> nofPoints = getTestSizes(2, 10,18,1, 10000) ;
	//std::map<unsigned int, unsigned int> nofPoints{ {1000,100}, {10000,1000 } ,{100000,1000 } ,{1000000,1000 } };
	std::map<unsigned int, unsigned int> nofPoints{  {1000000,1000}  };
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
	const std::string& fileNamePrefix, float rad,  std::vector<HMPoint> points, std::vector<HMPoint> qPoints) {
	using namespace std;
	unsigned int bTime, sTime;
	using MetricType = HMMetric;
	MetricType met;
	unsigned int nqActual = 0;

	// auto [points, qPoints] = generatePointsQD(nPoints, nQueries);

	auto start = std::clock();
	CMTree<HMPoint, MetricType> stree(points, met,pivT, partT, kxBalancedTreeHeight(1,points.size()));
	// BruteForceSearch<HMPoint, MetricType> stree2(points, met); //This is not baseline weism huilaile xiamian de zhixian shi stree not 2
	SPMTree<HMPoint, MetricType> stree2(points, met, pivT, partT, kxBalancedTreeHeight(1,points.size()));  //Is that because I didn't put in enough arguments?
	bTime = dTimeSeconds(start);
	cout << "radiusSearchTest btime=" << bTime << endl;

	std::set<unsigned int> depths;
	double radiusSum = stree.radiusSumAndDepths(depths);

	start = std::clock();
	unsigned int nFound = 0;
	unsigned int diffCount = 0;
	const unsigned int maxResults = 100000;
	// auto rad = 1;
	for (const auto& qp : qPoints) {
		/*if(nqActual == 2) {
			cout << "pq id="<<qp.getId() << endl;
			RadiusQuery<EuclidianPoint> rqt(qp, rad, maxResults);
			stree.search(rqt);
		}*/
		RadiusQuery<HMPoint> rq(qp, rad, maxResults);
		stree.search(rq);
		// cout<<stree.getPerfStats().getNodesVisited()<<endl;
		nFound += rq.getNeighbors().size();

		// RadiusQuery<HMPoint> rq2(qp, rad, maxResults);
		// stree2.search(rq2);
		// cout<<stree2.getPerfStats().getNodesVisited()<<endl;
		// cout<<"----"<<endl;
		// if (!rq.hasSameNeighbors(rq2)) {
		// 	diffCount++;
			
		// }

	    nqActual++;
		if ((nqActual % 10000) == 0) { cout << "finished search i= " << nQueries << endl; }
	}
	sTime = dTimeSeconds(start);

	string runTimeFileName{ fileNamePrefix + "_rs_compare.csv"};
	ofstream theFileA(runTimeFileName, ios::app);
	theFileA 
		// << ";;TEST EMSC: " << currentDateTime()
		// << ";;[CLasses]:" << endl
		// << ";;[" << typeid(stree).name() << "]," << "[" << met << "]" << endl
		// << ";;[CLasses # 2]:" << endl
		// << ";;[" << typeid(stree2).name() << "]" << endl
		// << ";; Tree depths, min depth, max depth :" << depths.size() << ","
		// << *(std::min_element(depths.begin(), depths.end())) << "," << *(std::max_element(depths.begin(), depths.end())) << endl
		// << "rad,dbSize,DiffCount,nQueries,nfound,radiusSum,Pivo,Partitio,CMT<nodesVisited>, Baseline<nodesVisited>, CMT<numDistanceCalls>,Baseline<numDistanceCalls>,btime,stime" << endl
		<< rad << "," << points.size() << "," << diffCount << "," << nqActual << "," << nFound << "," << radiusSum << ","
		<< stree.getPivotType() << "," << stree.getPartType() << ","
		<< (stree.getPerfStats().getNodesVisited() / nQueries) << ","
		// << (stree2.getPerfStats().getNodesVisited() / nQueries) << "," //hui lai kan fa xian chu cuo shu le  dengdeng nQ meicuo a 
		<< (stree.getPerfStats().getDistanceCalls() / nQueries) << ","
		// << (stree2.getPerfStats().getDistanceCalls() / nQueries) << ","
		<< bTime << "," << sTime << endl;

	theFileA.close();	
}




void radiusSearchCompareEM(const std::string& fileNamePrefix) {
	std::map<unsigned int, unsigned int> nofPoints{  {2e5, 20} };
	std::vector<float> rads{5,10,15,20}; //0.1 will cause float error
	// std::map<unsigned int, unsigned int> nofPoints{ {1000,100} };
	for (const auto& [np, nSkip] : nofPoints) {
		auto [points, qPoints] = generatePointsQD(np, nSkip);

		for (const auto& [pivType, pivVal] : pivotTypeMap) {
			for (const auto& [parType, parVal] : partTypeMap) {
				for (float rad : rads) {
					///cout << np << " " << pivType << " " << pivVal << endl; break;
					// radiusSearchCompareEM(np, nSkip, pivType, parType, fileNamePrefix, rad, nPoints, nQueries);
					radiusSearchCompareEM(np, nSkip, pivType, parType, fileNamePrefix, rad, points, qPoints);

				}
			}
		}
	}
}


void kNNSearchCompareEM(unsigned int nPoints, unsigned int nQueries,
	PivotType pivT, PartType partT, unsigned int nofResults,
	const std::string& fileNamePrefix, bool csvh = true) {
	using namespace std;

	unsigned int bTime, sTime;
	using MetricType = HMMetric;
	MetricType met; //beifuhidesxkoukunxou xkou zhan

	constexpr unsigned int dim = DIM;
	
	//auto [points, qPoints] = generatePointsQD(nPoints, nQueries);
	auto [points, qPoints] = generatePointsQD(nPoints, nQueries);


	std::clock_t start = std::clock();
	CMTree<HMPoint, MetricType> stree(points, met, pivT, partT, kxBalancedTreeHeight(1, points.size()));
	SPMTree<HMPoint, MetricType> stree2(points, met, pivT, partT, kxBalancedTreeHeight(1, points.size()));

	bTime = dTimeSeconds(start);
	cout << "firstkSearchTest btime=" << bTime << endl;

	start = std::clock();
	unsigned int diffCount = 0;
	unsigned int nFound = 0;
	unsigned int nqActual = 0;
	// auto rad{ std::numeric_limits<float>::max() };
	// auto rad = 200;
	auto rad{ std::numeric_limits<float>::max() }; //rad vs max rusult? yahci hlong meiyou make zqq zhongyuchirwanlehaihuanfangxiang 
	for ( auto& qp : qPoints) {
		NearestKQuery<HMPoint> rq(qp,  nofResults, rad);
		stree.search(rq);
		nqActual++;
		nFound += rq.getNeighbors().size();

		NearestKQuery<HMPoint> rq2(qp,  nofResults, rad); //yahaiwyiweishizhli 
		stree2.search(rq2);

		if (!rq.hasSameNeighbors(rq2)) {
			diffCount++;
		}

		if ((nqActual % 1000) == 0) { cout << "Finished search i= " << nqActual << endl; }
	}
	sTime = dTimeSeconds(start);

	//AND the CSV file:
	ofstream csvFile(fileNamePrefix + ".csv", ios::app);
	if (csvh == true) {
		csvFile << ";;TEST NEARK_COMPARE_EM: " << currentDateTime()
			<< ";;[CLasses]:" << endl
			<< ";;[" << typeid(stree).name() << "]," << "[" << met << "]" << endl
			<< "DiffCnt,MADI,dim,dbSize,nQueries,maxResults,nfound,aveNfound,Pivot,Partition,CMT.nodesVisited,Baseline.nodesVisited,CMT.numDistCalls,Baseline.numDistCalls" << endl;
		csvh = false;
	}
	csvFile << diffCount << ","  << stree.getMADIorK() <<"," << dim << "," << points.size() << "," << nqActual << "," << nofResults << ","
		<< nFound << "," << ((nFound * 1.0f) / nqActual) << ","
		<< stree.getPivotType() << "," << stree.getPartType() << ","
		<< (1.0f * stree.getPerfStats().getNodesVisited()) / (1.0f * nqActual) << ","
		<< (1.0f * stree2.getPerfStats().getNodesVisited()) / (1.0f * nqActual) << ","
		// << static_cast<float>(stree.getPerfStats().getDistanceCalls()) / nqActual << ","//zhegeshism? chaojkunyunyachiduzihuangxkou zayun 
		<< (1.0f * stree.getPerfStats().getDistanceCalls()) / (1.0f * nFound)  << ","
		<< (1.0f * stree2.getPerfStats().getDistanceCalls()) / (1.0f * nFound) <<  endl;
	csvFile.close();
}

void kNNSearchCompareEM(const std::string& fileNamePrefix) {
	//std::map<unsigned int, unsigned int> nofPoints{ {100,1},{1000,10}, {10000,10}, {1000000,100} };
	std::map<unsigned int, unsigned int> nofPoints{ {1000,100} };
	std::vector<unsigned int> maxResults{1,2,3,4,5,6,7,8,9,10};
	//
	for (const auto& [np, nQueries] : nofPoints) {
		for (const auto& [pivType, pivVal] : pivotTypeMap) {
			for (const auto& [parType, parVal] : partTypeMap) {
				for (const auto& mr : maxResults) {
					kNNSearchCompareEM(np, nQueries, pivType, parType, mr, fileNamePrefix );
				}
			}
		}
	}
}

		//qqshuowogeitachongshangle ma daduanguaibude xkou zheli meiyou dong hao  shiqing qq shuokaobuzhu fhenfanyachi  xkouhenhuangxianzaideneng duzikunweismzxianzaizhemekuai tt 