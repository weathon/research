// #ifndef EUCLIDIAN_POINT_H
// #define EUCLIDIAN_POINT_H

#include <array>

/*
	Euclidian point class.
	Plase note the "using" statement right after the end of the class definition,
	which essentially fixes the dimention and data type for the project.
*/


template <unsigned int DIM>
class HMPointG {
private:
	std::string point;
	std::string id;
public:
	HMPointG(const std::string ident, const std::string&  pData) : id{ ident } {
			id = ident;
			point= pData;//defined in std to overrite every member
	}
	const std::string& getId() const { return id; }
	const std::string& getValue() { return point; }
	const unsigned int dim() { return DIM; }
	char operator[](const int i) const { return point[i]; }

	double distance(const HMPointG& p) const {
		int ans = 0;
		for(int i=0; i<p.point.length(); i++)
		{
			// if(p.point[i] != p.point[i])
			if(p.point[i] != point[i])
			{
				ans++;
			}
		}
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
using HMPoint = HMPointG<500>;


// #endif // !EUCLIDIAN_POINT_H