/********************************************************************
CSCI 566 - Assignment 2 - Semester(Spring-2015)

Programmer: Aravinda Krishnan V
Section:    3
TA:         Robert Durham
Date Due:  02/20/2015

Purpose:   This program takes the input from a file and calculates the
		   annual utility charges of gas,Electricity and water.

*********************************************************************/

//Header files

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>

const int nom=12;
using namespace std;
// Function Declaration

void buildArrays(double gas[], double electricity[], double water[]);
double high(double array[], int size);
double low(double array[], int size);
double sum(double array[], int size);
double mean(double array[], int size);
void printArray(string caption, double array[], int size);
void getSumArray(double gas[], double electricity[], double water[], double sums[]);
void printUtilityStat(string caption, double array[], int size);
void sort(double array[], int size);

//Defining functions
void buildArrays(double gas[], double electricity[], double water[])
{
	//Fills in the arrays with the input from the file.

	//creating the inputstream and reading from file.
	std::ifstream infile;
	infile.open("expenses.txt");
	std::string data;
	int gc =0, wc = 0, ec = 0,tmp=0;

	//print error and exit if the file doesn't exist.
	if (infile.fail())
        {
		cout << "File does not exist";
		exit(1);
	}

	//starting a loop to read from file
	while (!(infile.eof()))
	{
		infile>>data;

		if (data.compare("gas") == 0)
		{ 
			tmp = 1; 
		}
		else if (data.compare("electricity") == 0)
                {
			tmp = 2;
		}
		else if (data.compare("water") == 0)
                {
			tmp = 3;
		}
		else
                {
			switch (tmp)
			{
			case 1:
				(istringstream)data>>gas[gc];
				gc++;
				break;
			case 2:
				(istringstream)data >> electricity[gc];
				ec++;
				break;
			case 3:
				(istringstream)data >> water[gc];
				wc++;
				break;
			default:
				cout << "Enter a valid File.";
				exit(1);
				break;
			}			
		}
	}
	infile.close();
}

double high(double array[], int size)
{
	double max = *std::max_element(array,array+size);
	return max;
}

double low(double array[], int size)
{
	double min = *std::min_element(array, array + size);
	return min;
}

double sum(double array[], int size)
{
	int c = 0;
	double sum =0.0;
	while (c < size){
		sum = sum + array[c];
	}
	return sum;
}

double mean(double array[], int size)
{
	double mean = (sum(array, size))/size;
	return mean;
}

void printArray(string caption, double array[], int size)
{
	int c = 0;
	cout << "\n" << caption;
	while (c < size)
        {
		cout << "\n$" << array[c];
		c++;
	}
}

void getSumArray(double gas[], double electricity[], double water[], double sums[])
{
	int c = 0;
	while (c < nom)
        {
		sums[c] = gas[c] + electricity[c] + water[c];
	}
}

void printUtilityStat(string caption, double array[], int size) 
{
	cout << "\n\t\t\t\t***" << caption << "***";
	cout << "\nsum over 12 months:  $" << sum(array, size);
	cout << "\nHighest cost:  $" << high(array, size);
	cout << "\nLowest cost:  $" << low(array, size);
	cout << "\nAverage cost:  $" << mean(array, size);
}

void sort(double array[], int size) 
{
	// declaring local objects     
	int m;    double temp;

	// implement selection sort algorithm     
	for (int k = 0; k <= size - 2; ++k)     
            {
		// find position of smallest value in array         
		// begining at k         
		m = k;
		for (int j = k + 1; j <= size - 1; ++j)
		{
			if (array[j]<array[m])
				m = j;
                }
		temp = array[m];
		array[m] = array[k];
		array[k] = temp;
	     }
}

int main()
{
	double gas[nom];
	double electricity[nom];
	double water[nom];
	double sums[nom];
	buildArrays(gas, electricity, water);
	printUtilityStat("gas", gas, nom);
	printUtilityStat("electricity", electricity, nom);
	printUtilityStat("water", water, nom);
	getSumArray(gas, electricity, water, sums);
	printArray("***Monthly total***",sums,nom);
	sort(sums, nom);
	printArray("***Sorted Monthly total***", sums, nom);
	cout << "\nThe highest monthly expense is $" << sums[11];
	cout << "\nThe lowest monthly expense is $" << sums[0];
	cout << "\nThe average monthly expense is $" << mean(sums,nom);
	getchar();
}



