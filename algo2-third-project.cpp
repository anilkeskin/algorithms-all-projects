/*

ANIL KESKÝN - 150170801

Test Case 2 - Main arguments are file names.

*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int ind;
double penalty = -5;
double findMax(double array[], int length)
{
	double max = array[0];
	ind = 0;

	for (int i = 1; i < length; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
			ind = i;
		}
	}
	return max;
}
double similarityScore(char a, char b)
{
	double result;
	if (a == b)
	{
		result = 1;
	}
	else
	{
		result = penalty;
	}
	return result;
}
int number;
int number_count;
string seqA ;
string seqB ;
int lengthSeqA;
int lengthSeqB;
vector<string> my_str_list;
int main(int argc, char** argv)
{
	//string fileInputName = "strings.txt";
	//string fileOutName = "output.txt";
	string fileInputName = argv[1];
	string fileOutName = argv[2];
	ifstream file(fileInputName);
	ofstream dosyaYaz(fileOutName);
	vector<string> str_array;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			str_array.push_back(line.c_str());
		}
		file.close();
	}
	unsigned int son_sayi = str_array.size();
	std::sort(str_array.begin(), str_array.end());
	for (unsigned int i = 0; i < str_array.size(); i++)
	{
		for (unsigned int j = i+1; j < str_array.size(); j++)
		{
			if (j != son_sayi)
			{
				seqA = str_array[i];
				seqB = str_array[j];
				lengthSeqA = seqA.length();
				lengthSeqB = seqB.length();

				double** matrix = new double* [lengthSeqA + 1];
				for (int i = 0; i < lengthSeqA + 1; i++)
				{
					matrix[i] = new double[lengthSeqB + 1];
				}
				for (int i = 0;i <= lengthSeqA;i++)
				{
					for (int j = 0;j <= lengthSeqB;j++)
					{
						matrix[i][j] = 0;
					}
				}
				double traceback[4];
				int** I_i = new int* [lengthSeqA + 1];
				int** I_j = new int* [lengthSeqA + 1];
				for (int i = 0; i < lengthSeqA + 1; i++)
				{
					I_i[i] = new int[lengthSeqB + 1];
					I_j[i] = new int[lengthSeqB + 1];
					for (int j = 0;j < lengthSeqB + 1;j++)
					{
							I_i[i][j] = 0;
							I_j[i][j] = 0;
							
					}
				}
				for (int i = 1;i <= lengthSeqA;i++)
				{
					for (int j = 1;j <= lengthSeqB;j++)
					{
						traceback[0] = matrix[i - 1][j - 1] + similarityScore(seqA[i-1], seqB[j-1]);
						traceback[1] = matrix[i - 1][j] + penalty;
						traceback[2] = matrix[i][j - 1] + penalty;
						traceback[3] = 0;
						matrix[i][j] = findMax(traceback, 4);
						switch (ind)
						{
						case 0:
							I_i[i][j] = i - 1;
							I_j[i][j] = j - 1;
							break;
						case 1:
							I_i[i][j] = i - 1;
							I_j[i][j] = j;
							break;
						case 2:
							I_i[i][j] = i;
							I_j[i][j] = j - 1;
							break;
						case 3:
							I_i[i][j] = i;
							I_j[i][j] = j;
							break;
						}
					}
				}

				double matrix_max = 0;
				int i_max = 0, j_max = 0;
				int i_max_array[100];
				int j_max_array[100];
				for (int i = 0;i < 100;i++)
				{
					i_max_array[i] = 0;
					j_max_array[i] = 0;
				}
				for (int i = 0;i <= lengthSeqA;i++)
				{
					for (int j = 0;j <= lengthSeqB;j++)
					{
						if (matrix[i][j] > matrix_max)
						{
							matrix_max = matrix[i][j];
							i_max = i;
							j_max = j;
						}
					}
				}
				i_max_array[0] = i_max;
				j_max_array[0] = j_max;
				number = 1;
				number_count = 1;
				int first = 0;
				for (int i = 0;i <= lengthSeqA;i++)
				{
					for (int j = 0;j <= lengthSeqB;j++)
					{
						if (matrix[i][j] == matrix_max)
						{
							if (first != 0)
							{
								i_max_array[number] = i;
								j_max_array[number] = j;
								number++;
								number_count++;
							}
							else
							{
								first = 1;
							}
							
						}
					}
				}
				number = 0;
				int sayi = 0;
				if (i_max_array[0] != 0 && j_max_array[0] != 0)
				{
					while (i_max_array[number] != 0 && j_max_array[number] != 0)
					{
						int current_i = i_max_array[number], current_j = j_max_array[number];
						int next_i = I_i[current_i][current_j];
						int next_j = I_j[current_i][current_j];
						int tick = 0;
						char* consensus_a = new char[lengthSeqA + lengthSeqB + 2], * consensus_b = new char[lengthSeqA + lengthSeqB + 2];

						while (((current_i != next_i) || (current_j != next_j)) && (next_i >= 0 && next_j >= 0))
						{

							if (next_i == current_i)
								consensus_a[tick] = '-';
							else
								consensus_a[tick] = seqA[current_i - 1];

							if (next_j == current_j)
								consensus_b[tick] = '-';
							else
								consensus_b[tick] = seqB[current_j - 1];

							current_i = next_i;
							current_j = next_j;
							next_i = I_i[current_i][current_j];
							next_j = I_j[current_i][current_j];
								tick++;
						}
						if (number_count == 1)
						{
							for (int i = 0;i < lengthSeqA;i++) { dosyaYaz << seqA[i]; }; dosyaYaz << " - ";
							for (int i = 0;i < lengthSeqB;i++) { dosyaYaz << seqB[i]; }; dosyaYaz << "\n";
							dosyaYaz << "Score: " << matrix_max << " ";
							dosyaYaz << "Sequence(s):";
							dosyaYaz << " \"";
							for (int j = matrix_max - 1;j >= 0;j--)
							{
								if(consensus_a[j]!='-') dosyaYaz << consensus_a[j];
							}
							dosyaYaz << "\"";
						}
						else
						{
							if (sayi == 0)
							{
								
								string temp = "";
								for (int i = 0;i < lengthSeqA;i++) { dosyaYaz << seqA[i]; }; dosyaYaz << " - ";
								for (int i = 0;i < lengthSeqB;i++) { dosyaYaz << seqB[i]; }; dosyaYaz << "\n";
								dosyaYaz << "Score: " << matrix_max << " ";
								dosyaYaz << "Sequence(s):";
								//cout << "\"";
								for (int j = matrix_max - 1;j >= 0;j--)
								{
									if (consensus_a[j] != '-')
									{
										//cout << consensus_a[j];
										temp += consensus_a[j];
									}
									
								}
								//cout << "\" ";
								sayi = 1;
								my_str_list.push_back(temp);
							
							}
							else
							{
								string first_seq = "";
								for (int j = matrix_max - 1;j >= 0;j--)
								{
									first_seq += consensus_a[j];
								}
								
								if (std::find(my_str_list.begin(), my_str_list.end(), first_seq) != my_str_list.end()) {
									//cout << "Found" << endl;
								}
								else
								{
									string temp = "";
									//cout << "\"";
									for (int j = matrix_max - 1;j >= 0;j--)
									{
										if (consensus_a[j] != '-')
										{
											//cout << consensus_a[j];
											temp += consensus_a[j];
										}
											
									}
									my_str_list.push_back(temp);
									//cout << "\" ";
								}
							}
						}
						number++;
						delete[] consensus_a;
						delete[] consensus_b;
					}
					std::sort(my_str_list.begin(), my_str_list.end());
					for (unsigned int i = 0; i < my_str_list.size(); i++)
					{
						dosyaYaz << " \"";
						dosyaYaz << my_str_list[i];
						dosyaYaz << "\"";
					}
					dosyaYaz << "\n";
					my_str_list.clear();
					delete[] matrix;
					delete[] I_i;
					delete[] I_j;
				}
				else
				{
					for (int i = 0;i < lengthSeqA;i++) { dosyaYaz << seqA[i]; }; dosyaYaz << " - ";
					for (int i = 0;i < lengthSeqB;i++) { dosyaYaz << seqB[i]; }; dosyaYaz << "\n";
					dosyaYaz << "Score: " << 0 << " ";
					dosyaYaz << "Sequence(s):";
					dosyaYaz << "\n";
				}
			}
		}
	}
	dosyaYaz.close();
	return 0;
}

