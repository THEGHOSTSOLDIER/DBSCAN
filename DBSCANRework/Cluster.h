#pragma once

#include <vector>

class Cluster
{
private:
	int m_minPoints;
	double m_radius;
	bool m_isACluster;
	std::vector<double> m_data[2];

public:
	Cluster();
	~Cluster();
	int getMinPoints();
	void setMinPoints(int minPoints);
	double getRadius();
	void setRadius(double radius);
	bool getIsACluster();
	std::vector<double> *getData();
	double CalculateVectorMagnitude(double x1, double y1, double x2, double y2);
	void checkPoint(std::vector<double> *data);
	void pointAdjustment(std::vector<double>* data);
};

