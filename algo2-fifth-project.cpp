/*
	ANIL KESKÝN - 150170801 - Q2
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
struct Point{
    int xCoordinate;
    int yCoordinate;
};
int cmpX(Point p1, Point p2)
{
	return (p1.xCoordinate < p2.xCoordinate);
}
	
int cmpY(Point p1, Point p2)
{
	return (p1.yCoordinate < p2.yCoordinate);
}
float dist(Point p1, Point p2) 
{
	return sqrt((p1.xCoordinate - p2.xCoordinate)*(p1.xCoordinate - p2.xCoordinate) + (p1.yCoordinate - p2.yCoordinate)*(p1.yCoordinate - p2.yCoordinate));
}
class PointSpace{
    int numberOfPoints;
    vector<Point> points;
public:
    void setNumberOfPoints(int n){
        numberOfPoints = n;
    }
    int getNumberOfPoints(){
        return numberOfPoints;
    }
    void addPoint(int x, int y){
        Point p = Point();
        p.xCoordinate = x;
        p.yCoordinate = y;  
        points.push_back(p);
    }
    void printNumberOfPoints(){
        cout << "Total number of points: " << getNumberOfPoints() << endl;
    }
    void printAllPoints(){
        cout << "Points coordinates (x y): " << endl;
        for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i){
            cout << i->xCoordinate << "\t" << i->yCoordinate << endl;
        }
    }
    float min(float x, float y) 
	{
		if(x < y)
			return x;
		else 
			return y;
	}
    float findMinDist(Point pts[], int n) 
	{
   		float min = 9999;
   		for (int i = 0; i < n; ++i)
      		for (int j = i+1; j < n; ++j)
         		if (dist(pts[i], pts[j]) < min)	min = dist(pts[i], pts[j]);
   		return min;
	}
	float stripClose(Point strip[], int size, float d) 
	{
   		float min = d;
   		for (int i = 0; i < size; ++i)
      		for (int j = i+1; j < size && (strip[j].yCoordinate - strip[i].yCoordinate) < min; ++j)
         		if (dist(strip[i],strip[j]) < min)	min = dist(strip[i], strip[j]);
   		return min;
	}
	float findClosest(Point xSorted[], Point ySorted[], int n)
	{
	   	if (n <= 3) return findMinDist(xSorted, n);
   		int mid = n/2;
   		Point midPoint = xSorted[mid];
   		Point ySortedLeft[mid+1];
   		Point ySortedRight[n-mid-1];
   		int leftIndex = 0, rightIndex = 0;
   		for (int i = 0; i < n; i++) 
		{ 
     		if (ySorted[i].xCoordinate <= midPoint.xCoordinate)
         		ySortedLeft[leftIndex++] = ySorted[i];
      		else
         		ySortedRight[rightIndex++] = ySorted[i];
   		}
   		float leftDist = findClosest(xSorted, ySortedLeft, mid);
   		float rightDist = findClosest(ySorted + mid, ySortedRight, n-mid);
   		float dist = min(leftDist, rightDist);
   		Point strip[n];
   		int j = 0;
   		for (int i = 0; i < n; i++)
   		{
      		if (abs(ySorted[i].xCoordinate - midPoint.xCoordinate) <dist)
			{
         		strip[j] = ySorted[i];
         		j++;
      		}
      	}
   		return min(dist, stripClose(strip, j, dist));
	}
    float FindClosestPairDistance()
	{
    	Point xSorted[numberOfPoints];
   		Point ySorted[numberOfPoints];
   		for (int i = 0; i < numberOfPoints; i++)
		{
      		xSorted[i] = points[i];
      		ySorted[i] = points[i];
   		}
   		sort(xSorted, xSorted+numberOfPoints, cmpX);
   		sort(ySorted, ySorted+numberOfPoints, cmpY);
   		return findClosest(xSorted, ySorted, numberOfPoints);
    }
};
int main(int argc, char* argv[]){
    PointSpace pointSpace;
    string inputFileName = argv[1];
    string line;
    ifstream infile(inputFileName);
    getline(infile, line);
    pointSpace.setNumberOfPoints(stoi(line));
    int x, y;
    while (infile >> x >> y){
       pointSpace.addPoint(x, y);
    }
    //pointSpace.printAllPoints();
    //pointSpace.printNumberOfPoints();
    double closestDistance = pointSpace.FindClosestPairDistance();
    cout << "Distance between the closest points: " << closestDistance << endl;
    return 0;
}



