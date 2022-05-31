#include "Cluster.h"

//constructor
Cluster::Cluster()
{
	m_minPoints = 0;
	m_radius = 0.0;
	m_data[0].clear();
	m_data[1].clear();
	m_isACluster = false;
}

//destructor
Cluster::~Cluster()
{
	//delete the cluster
	m_data[0].clear();
	m_data[1].clear();
}

//m_minPoints accessor
int Cluster::getMinPoints()
{
	return m_minPoints;
}

//m_minPoints editor
void Cluster::setMinPoints(int minPoints)
{
	m_minPoints = minPoints;
}

//m_radius accessor
double Cluster::getRadius()
{
	return m_radius;
}

//m_radius editor
void Cluster::setRadius(double radius)
{
	m_radius = radius;
}

//m_isACluster accessor
bool Cluster::getIsACluster()
{
	/*
	if (m_data[0].size() >= m_minPoints)
	{
		m_isACluster = true;
	}
	else
	{
		m_isACluster = false;
	}*/
	return m_isACluster;
}

//m_data accessor
std::vector<double> *Cluster::getData()
{
	return m_data;
}

double Cluster::CalculateVectorMagnitude(double x1, double y1, double x2, double y2)
{
	double magnitude = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return magnitude;
}

void Cluster::checkPoint(std::vector<double> *data)
{
	std::vector<double> tempData[2];
	tempData[0] = data[0];
	tempData[1] = data[1];
	//check if the point is in the cluster
	if (m_data[0].size() == 0)
	{
		uint16_t counter;
		for (int i = 0; i < tempData[0].size(); i++)
		{
			counter = 1;
			for (int j = 0; j < tempData[0].size() && counter < m_minPoints; j++)
			{
				if (CalculateVectorMagnitude(tempData[0][j], tempData[1][j], tempData[0][i], tempData[1][i]) <= m_radius && j != i)
				{
					counter++;
				}
			}
			if (counter == m_minPoints)
			{
				m_data[0].push_back(tempData[0][i]);
				tempData[0].erase(tempData[0].begin() + i);
				m_data[1].push_back(tempData[1][i]);
				tempData[1].erase(tempData[1].begin() + i);
				break;
			}
		}
	}
	
	if (m_data[0].size() > 0)
	{
		uint16_t counter;
		uint16_t minPointsRequired;
		for (int i = 0; i < tempData[0].size(); i++)
		{
			//need to check if the point is in the cluster in the second part
			counter = 1;
			minPointsRequired = 0;
			bool isInCluster = false;
			for (int j = 0; j < m_data[0].size() && counter < m_minPoints; j++)
			{
				if (CalculateVectorMagnitude(m_data[0][j], m_data[1][j], tempData[0][i], tempData[1][i]) <= m_radius && j != i)
				{
					if (isInCluster == false)
					{
						if (m_data[0].size() < m_minPoints)
						{
							isInCluster = true;
						}
						else
						{
							minPointsRequired++;
						}
						//isInCluster = true;
					}
					counter++;
				}
			}
			
			if (minPointsRequired >= m_minPoints - 1)
			{
				isInCluster = true;
			}

			if (isInCluster)
			{
				for (int j = 0; j < tempData[0].size() && counter < m_minPoints; j++)
				{
					if (CalculateVectorMagnitude(tempData[0][j], tempData[1][j], tempData[0][i], tempData[1][i]) <= m_radius && j != i)
					{
						counter++;
					}
				}
			}

			if (counter >= m_minPoints && isInCluster)
			{
				m_data[0].push_back(tempData[0][i]);
				tempData[0].erase(tempData[0].begin() + i);
				m_data[1].push_back(tempData[1][i]);
				tempData[1].erase(tempData[1].begin() + i);
				i=0;
			}
		}
	}
	
	if (m_data[0].size() >= m_minPoints)
		m_isACluster = true;
	else
		m_isACluster = false;
	
	
	//if (getIsACluster())
	if (m_isACluster)
	{
		data[0] = tempData[0];
		data[1] = tempData[1];
	}
}

void Cluster::pointAdjustment(std::vector<double>* data)
{
	std::vector<double> tempData[2];
	tempData[0].clear();
	tempData[1].clear();
	for (int i = 0; i < data[0].size() && data[0].size() != 0; i++)
	{
		for (int j = 0; j < m_data[0].size() && data[0].size() != 0; j++)
		{
			if (CalculateVectorMagnitude(m_data[0][j], m_data[1][j], data[0][i], data[1][i]) <= m_radius && j != i)
			{
				tempData[0].push_back(data[0][i]);
				//m_data[0].push_back(data[0][i]);
				data[0].erase(data[0].begin() + i);				
				tempData[1].push_back(data[1][i]);
				//m_data[1].push_back(data[1][i]);
				data[1].erase(data[1].begin() + i);
				i = 0;
				j = 0;
			}
		}
	}
	
	if (tempData[0].size() != 0)
	{
		for (int i = 0; i < tempData[0].size(); i++)
		{
			m_data[0].push_back(tempData[0][i]);
			m_data[1].push_back(tempData[1][i]);
		}
	}
}