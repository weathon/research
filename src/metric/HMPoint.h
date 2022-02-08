// #ifndef EUCLIDIAN_POINT_H
// #define EUCLIDIAN_POINT_H

#include <array>

/*
	Euclidian point class.
	Plase note the "using" statement right after the end of the class definition,
	which essentially fixes the dimention and data type for the project.
*/

const float trandomVector[100] = {0.35202980081921775,0.2565452896603836,0.8256526654677342,0.5437998085609582,0.16974419831215803,0.31839366013844117,0.1391038758219738,0.053401295043628894,0.0653416053037773,0.4276339087224843,0.787998401943023,0.9212523239615709,0.7357785898065013,0.5196397466561686,0.06091681872741317,0.9587295689187485,0.879293250248567,0.2009486995434281,0.35481641047974655,0.6325297052344451,0.47997260934578867,0.9915547055058769,0.6861527399368194,0.27885761987230895,0.6253107051801888,0.4184455508716842,0.5508999534904644,0.448980301449566,0.3295306564134075,0.8210276295165885,0.04588651081110462,0.970422490865354,0.449606571604543,0.412388318528794,0.451717409876073,0.646875523970307,0.5079779465232813,0.15600701895580993,0.23414164790750913,0.3172782301895858,0.8552981450782983,0.7365705894245383,0.9413355060331421,0.5332282355395468,0.0520907159797257,0.7315846252953253,0.6512668201039855,0.7930006025977471,0.9913885656128127,0.007480832266537951,0.5104870535544547,0.3040808952616313,0.1591526950880271,0.9237922190949522,0.3693998455763662,0.9352100695355452,0.5911068042997587,0.06413091193740739,0.3239994463738909,0.6450946417178662,0.22493950937833906,0.12729374770505741,0.122155342706744,0.8822645206974712,0.24022416004766678,0.43080766498143785,0.399222076905835,0.17560050208982914,0.7258453565866386,0.4841954241253661,0.8372529870568994,0.4329714960541188,0.9203043888990715,0.8735628706308832,0.19627914561992943,0.5932141304523726,0.06745997107441448,0.7026876256460113,0.6878024961446156,0.7628795800111705,0.1983806308518975,0.7041614233659694,0.4450962027484541,0.19016967202221857,0.039388165327124525,0.8797018859215987,0.13305544658655688,0.7482374819305774,0.11762620639535026,0.8553056824765662,0.7265398101039836,0.39118968955045896,0.6094503152198856,0.5511012317770213,0.7003336712738469,0.022192724911287875,0.24150824051356357,0.6787699345561387,0.23277260608711803,0.2686324137937185};


template <unsigned int DIM>
class HMPointG {
private:
	std::string point;
	std::string id;
public:
	HMPointG(const std::string ident, const std::string&  pData) 
	: id{ ident }
	 {
			id = ident;
			point= pData;//defined in std to overrite every member
	}
	std::string getId() const { return id; } //& vs no?
	std::string getValue() const { return point; }
	const unsigned int dim() { return DIM; }
	char operator[](const int i) const { return point[i]; }

	double distance(const HMPointG p) const {
		double ans = 0;
		for(int i=0; i<point.length(); i++)
		{
			// if(p.point[i] != p.point[i])
			if(p.point[i] != point[i]) // how it can accesss p.point?
			{
				ans+=trandomVector[i];
				// ans+=i/101;
			}
		}
		std::cout<<ans<<std::endl; //Nost of them are about 400 while the dim is 50 it is 500 on th otehr side tt huangxkou why some is 60?  DIM=100!! ok yunzhaghuxi meiyou de hua shi 50 yuou de hua shi 25 huxi zhuag 
		std::cout<<p.getValue()<<std::endl; 
		std::cout<<point<<std::endl;
		return ans;
	}

    //??? DIM = String Length?
	// bool isInsideBox(std::array<DIM> const& o, std::array<DIM>  const& p) {
	// 	for (int i = 0; i < DIM; i++) {
	// 		if ((point[i] < o[i]) || (point[i] > p[i])) {
	// 			return false;
	// 		}
	// 	}
	// 	return true;
	// }

	friend std::ostream& operator<<(std::ostream& os, HMPointG& n) {
		os << "(" << n.id << ":<";
		os << n.point[0];
		for (int i = 1; i < DIM; i++) {
			os << "," << n.point[i];
		}
		os << ">)";
		return os;
	}
};
// static const unsigned int EuclidianPointDim = 10;

// using EuclidianPointPointType = float;
using HMPoint = HMPointG<100>;//shangmianrandomcectorbugouda kunsuanduz


// #endif // !EUCLIDIAN_POINT_H