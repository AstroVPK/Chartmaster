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
	CelestialPoint<float> pt{ra, dec};
	if (abs(dec) >= 70.0) {
		Projector<float, Stereographic<float>> proj;
		PolarPoint pt_rtheta = proj.project(pt);
		cout << "r = " << pt_rtheta.r() << "; theta = " << pt_rtheta.theta() << endl;
	} else if ((abs(dec) < 70) && (abs(dec) >= 30)) {
		Projector<float, LambertConformal<float, 0.0F, 50.0F, 30.0F, 70.0F>> proj;
		CartesianPoint pt_xy = proj.project(pt);
		cout << "x = " << pt_xy.x() << "; y = " << pt_xy.y() << endl;		
	} else if (abs(dec) < 30) {
		Projector<float, Mercator<float, 0.0F>> proj;
		CartesianPoint pt_xy = proj.project(pt);
		cout << "x = " << pt_xy.x() << "; y = " << pt_xy.y() << endl;		
	}
}