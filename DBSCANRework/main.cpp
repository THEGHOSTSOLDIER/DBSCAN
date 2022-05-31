#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Cluster.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define RELEASE

#ifdef RELEASE
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
#endif // RELEASE

using namespace std;
//bug when counter != 149
//bug with radius
void fillColumns(vector<double> *data, ifstream& file) {
	uint16_t counter = 0;
	string line;
	getline(file, line, ',');
	//column1.push_back(stod(line));
	data[0].push_back(stod(line));
	getline(file, line, ',');
	data[1].push_back(stod(line));
	getline(file, line, ',');
	data[2].push_back(stod(line));
	getline(file, line, ',');
	data[3].push_back(stod(line));
	while (getline(file, line) && counter < 149) {
	//while (getline(file, line)) {
		getline(file, line, ',');
		data[0].push_back(stod(line));
		getline(file, line, ',');
		data[1].push_back(stod(line));
		getline(file, line, ',');
		data[2].push_back(stod(line));
		getline(file, line, ',');
		data[3].push_back(stod(line));
		//getline(file, line);
		counter++;
	}
}

void setOffsets(const vector<double> *data, vector<double>* offsets, int first, int second) {
	offsets[0] = data[first];
	offsets[1] = data[second];
}

double linspace	(double start, double end, int num) {
	double step = (end - start) / (num - 1);
	return step;
}

vector<double> linspaceArray (double start, double end, int num) {
	vector<double> result;
	double step = (end - start) / (num - 1);
	for (int i = 0; i < num; i++) {
		result.push_back(start + i * step);
	}
	return result;
}

//return a N-size array containing random numbers between 0 and 1
vector<double> randArray(int N) {
	vector<double> result;
	for (int i = 0; i < N; i++) {
		result.push_back(rand() / (double)RAND_MAX);
	}
	return result;
}

//return a N-size array containing cosinus
vector<double> cosArray(int N) {
	vector<double> result;
	for (int i = 0; i < N; i++) {
		result.push_back(cos(i * 2 * M_PI / N));
	}
	return result;
}

//return a N-size array containing sinus
vector<double> sinArray(int N) {
	vector<double> result;
	for (int i = 0; i < N; i++) {
		result.push_back(sin(i * 2 * M_PI / N));
	}
	return result;
}

int main() {
	double radius = 0.8;
	double minPoints = 3;
	vector<double> data[4];
	vector<double> offsets[2];
	vector<Cluster> clusterArray;
	int N = 300;
	double r1 = 0.5;
	double r2 = 5;
	auto lArray = linspaceArray(0, 2 * M_PI, N);
	auto rArray = randArray(N);
	auto cArray = cosArray(N);
	auto sArray = sinArray(N);
	
	vector<double> X;
	vector<double> Y;
	
	for (int i = 0; i < N; i++) {
		X.push_back(r1 * cos(lArray[i]) + rArray[i]);
		Y.push_back(r1 * sin(lArray[i]) + rArray[i]);
	}
	
	for (int i = 0; i < N; i++) {
		X.push_back(r2 * cos(lArray[i]) + rArray[i]);
		Y.push_back(r2 * sin(lArray[i]) + rArray[i]);
	}
	
	ifstream file("iris.data");
	
	if (file.is_open()) {
		//uncomment these 2 lines to fill the columns with data from the file fisher.data
		//fillColumns(data, file);
		//setOffsets(data, offsets, 0, 2);
		//do not forget to comment these 2 lines if you uncomment the previous ones
		offsets[0] = X;
		offsets[1] = Y;
		//plt::plot(offsets[0], offsets[1], "r+");
		file.close();
		
		int threshold = 0;
		while (offsets[0].size() > 0)
		//for (int i = 0; i < offsets[0].size(); i++)
		{
			Cluster A;
			//A.setRadius(0.2);
			//A.setMinPoints(3);
			//A.setRadius(0.9);
			//A.setMinPoints(3);
			A.setRadius(radius);
			A.setMinPoints(minPoints);
			//A.setRadius(0.3);
			//A.setMinPoints(3);
			A.checkPoint(offsets);
			if (offsets[0].size() == threshold)
				break;
			if (A.getIsACluster())
			{
				A.pointAdjustment(offsets);
				clusterArray.push_back(A);
			}
			threshold = offsets[0].size();
		}

		/*
		for (int i = 0; i < offsets[0].size(); i++)
		{
			for (int j = 0; j < clusterArray.size(); j++)
			{
				clusterArray[j].checkPoint(offsets);
			}
		}*/
		/*
		for (int j = 0; j < clusterArray.size(); j++)
		{
			clusterArray[j].checkPoint(offsets);
		}*/
		/*
		while (offsets[0].size() != 0 && offsets[1].size() != 0)
		{
			Cluster A;
			//A.setRadius(0.2);
			//A.setMinPoints(3);
			//A.setRadius(0.9);
			//A.setMinPoints(3);
			A.setRadius(radius);
			A.setMinPoints(minPoints);
			//A.setRadius(0.3);
			//A.setMinPoints(3);
			A.clusterAdjustment(offsets);
			if (offsets[0].size() == threshold)
				break;
			if (A.getIsACluster())
				clusterArray.push_back(A);
			threshold = offsets[0].size();
		}*/
		/*
		for (int i = 0; i < clusterArray.size(); i++)
		{
			clusterArray[i].pointAdjustment(offsets);
		}*/
		cout << "Number of clusters: " << clusterArray.size() << endl;
	}
	else {
		cout << "Unable to open file";
		return 1;
	}

#ifdef RELEASE
	plt::title("Database");
	char markers[] = { '*', '+', '.' };
	char colors[] = {'r', 'g', 'b'};
	string color;
	for (int i = 0; i < clusterArray.size(); i++) {
		//color.push_back(colors[i]);
		//color.push_back(markers[i]);
		plt::plot(clusterArray[i].getData()[0], clusterArray[i].getData()[1], ".");
		//color.clear();
	}
	plt::plot(offsets[0], offsets[1], "c*");
	//plt::plot(A.getData()[0], A.getData()[1], "r*");
	//plt::title("Bol de ramen 2.0");
	plt::show();
#endif // RELEASE
}