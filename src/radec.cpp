#include <cmath>
#include <iostream>

#include "point.hpp"
#include "projection.hpp"


using namespace std;

int main() {
	float ra, dec;
	cout << "ra: ";
	cin >> ra;
	cout << "dec: ";
	cin >> dec;
	if (abs(dec) >= 70.0) {
		CelestialPoint<float, Stereographic<float>> pt{ra, dec};
		PolarPoint<float> pt_rtheta = pt.project();
		cout << "r = " << pt_rtheta.r() << "; theta = " << pt_rtheta.theta() << endl;
	}/* else if ((abs(dec) < 70) && (abs(dec) >= 30)) {
		CelestialPoint<float, LambertConformal<float, 0.0F, 50.0F, 30.0F, 70.0F>> pt{ra, dec};
		CartesianPoint<float> pt_xy = pt.project(pt);
		cout << "x = " << pt_xy.x() << "; y = " << pt_xy.y() << endl;		
	} else if (abs(dec) < 30) {
		CelestialPoint<float, Mercator<float, 0.0F>> pt{ra, dec};
		CartesianPoint<float> pt_xy = pt.project(pt);
		cout << "x = " << pt_xy.x() << "; y = " << pt_xy.y() << endl;		
	}*/
}
