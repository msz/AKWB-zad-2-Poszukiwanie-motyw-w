// Projekt_1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>


using namespace std;

vector < vector <char> >sequences;
vector < vector <int> >quality;
vector < vector <string> >vertexes;
//vector < vector <string> >vertex_quality;


int i, j, n, m, p;

void Read_sequences()
{
	char dziubek = '>';
	string row;
	int iter = -1;

	fstream file;
	fstream id;
	file.open("C:\\Users\\Agata\\Desktop\\fasta1.txt", ios::in);

	vector < vector <string> >help_vector;

	while (!file.eof())
	{
		getline(file, row);
		row = row.c_str();

		if (dziubek == row[0])
		{
			sequences.push_back(vector<char>());
			iter++;
		}
		else
		{
			for (i = 0; i < row.size(); i++)
			{
				sequences[iter].push_back(row[i]);
			}
			cout << endl;
		}
	}
	file.close();
}
void Show_sequences()
{
	cout << "Sekwencje: " << endl;
	cout << "sequences.size(): " << sequences.size() << endl;

	for (i = 0; i < sequences.size(); i++)
	{
		cout << "sequences[i].size()" << sequences[i].size() << endl;
		for (j = 0; j < sequences[i].size(); j++)
		{
			cout << sequences[i][j] << " ";
		}
		cout << endl << endl;
	}
}

void Read_qualities()
{
	char dziubek = '>';
	string line;
	int iter = -1;


	fstream file;
	string qual, id;
	file.open("C:\\Users\\Agata\\Desktop\\qual1.txt", ios::in);

	if (file.is_open())
	{
		for (i = 0; i < 8; i++)
		{
			quality.push_back(vector<int>());
			getline(file, line);
			getline(file, line);
			istringstream ss(line);
			int num;
			while (ss >> num)
			{
				quality[i].push_back(num);
			}

		}
	}
	else
	{
		cout << "BLAD ODCZYTU" << endl;
		exit(0);
	}
}
void Show_qualities()
{
	cout << endl << "jakosci: " << endl;
	for (int i = 0; i < quality.size(); i++)
	{
		cout << "quality[i].size(): " << quality[i].size() << endl;
		for (int j = 0; j < quality[i].size(); j++)
		{
			cout << quality[i][j] << " ";
		}
		cout << endl << endl;
	}
}

class Vertex
{
public:

	string seq_del;
	string seq;
	string positions;
	int nr_seq;
	string qualities;
	int nr_vertex;

	Vertex() {};
	Vertex(string sekw, string sekw_del, string pozycje, string jakosci, int nr_sekw, int nr_wierzch) 
	{
		seq = sekw;
		seq_del = sekw_del;
		positions = pozycje;
		qualities = jakosci;
		nr_seq = nr_sekw;
		nr_vertex = nr_wierzch;

	}
	~Vertex();


};

void Create_vertexes(int k, int p, vector<Vertex>& newMyVertex)
{
	
	string sekw, sekw_del, pozycje, poz, qual, q;
	int nr_sekw;
	int ile_x = 0;
	int nr_wierzch = 0;
	bool finish = false;

	for (i = 0; i < sequences.size(); i++)
	{

		vertexes.push_back(vector<string>());
		nr_sekw = i;
		//cout << endl << endl << "Numer sekwencji: " << nr_sekw << endl;

		for (m = 0; m < sequences[i].size(); m++)
		{

			for (j = m; j < (m + k); j++)
			{
				finish = false;
				if ((m + k) > sequences[i].size())
				{
					finish = true;
					break;
				}
				else
				{
					sekw += sequences[i][j];
					poz = to_string(j + 1);
					pozycje += (poz + " ");


					if (quality[i][j] < p)
					{
						ile_x++;
						q = to_string(quality[i][j]);


						if (k == 4 || k == 5)
						{
							if (ile_x == 1)
							{
								q = "X";
								sekw_del += q;
							}
							else
							{
								sekw_del += sequences[i][j];
							}
						}
						if (k == 6 || k == 7)
						{
							if (ile_x < 3)
							{
								q = "X";
								sekw_del += q;
							}
							else
							{
								sekw_del += sequences[i][j];
							}
						}
					}
					else
					{
						q = to_string(quality[i][j]);
						sekw_del += sequences[i][j];
					}

					qual += (q + " ");
				}

			}
			if (finish == true)
			{
				sekw.clear();
				sekw_del.clear();
				pozycje.clear();
				qual.clear();
				break;
			}
			else
			{
				vertexes[i].push_back(sekw);
				/*	cout << endl << endl << "sekw: " << sekw;
					cout << "	pozycje: " << pozycje << " ";
					cout << "qual: " << qual;
					cout << endl << "nr wierzcholka: " << nr_wierzch;
					cout << endl;
	*/

				Vertex newVertex(sekw, sekw_del, pozycje, qual, nr_sekw, nr_wierzch);
				newMyVertex.push_back(newVertex);

				nr_wierzch++;

				qual.clear();
				sekw_del.clear();
				sekw.clear();
				pozycje.clear();
				ile_x = 0;

			}
		}
	}
}
void Show_vertexes()
{
	cout << endl;
	for (i = 0; i < vertexes.size(); i++)
	{
		for (j = 0; j < vertexes[i].size(); j++)
		{
			cout << vertexes[i][j] << " ";
		}
		cout << endl;
	}
}

void Show_Objects(vector<Vertex>& newMyVertex)
{
	cout << "Wektor ZWYKLYCH:" << endl;
	unsigned int size = newMyVertex.size();
	for (unsigned int i = 0; i < size; i++)
	{
		cout << endl << "Wierzcholek " << i << " : " << endl;
		cout << "Sekw: " << newMyVertex[i].seq << "\tpozycje: " << newMyVertex[i].positions << "\tjakosci: " << newMyVertex[i].qualities << "\tnr_sekw: " << newMyVertex[i].nr_seq << endl;
	}
}

void Create_Matrix(vector<Vertex>& newMyVertex)
{
	unsigned int size = newMyVertex.size();

	int **matrix = new int*[size];
	for (i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i != j)
			{
				if (newMyVertex[i].seq == newMyVertex[j].seq)
					matrix[i][j] = 1;
			}
		}
	}

	//cout << endl << "wypelniona macierz BEZ DELECJI" << endl;
	//for (int i = 0; i < size; ++i)
	//{
	//	cout << endl;
	//	for (int j = 0; j < size; ++j)
	//		cout << matrix[i][j] << '\t';
	//}

	int total = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i != j)
			{
				int seq_size = newMyVertex[i].seq.size();
				for (m = 0; m < seq_size; m++)
				{
					if (newMyVertex[i].seq_del[m] == newMyVertex[j].seq_del[m])
					{
						total++;
					}
					else if (newMyVertex[i].seq_del[m] == 'X' || newMyVertex[j].seq_del[m] == 'X')
					{
						total++;
					}

				}
				if (total == seq_size)
				{
					matrix[i][j] = 1;
				}
				total = 0;
			}
		}
	}

	//cout << endl << "wypelniona macierz Z DELECJAMI" << endl;
	//for (int i = 0; i < size; ++i)
	//{
	//	cout << endl;
	//	for (int j = 0; j < size; ++j)
	//		cout << matrix[i][j] << '\t';
	//}



			/*------------HEURYSTYKA------------------*/

	int id = 0;
	int a = 1;

	vector< Vertex >clique_temp;
	vector< Vertex >clique_best;

	for (i = 0; i < size; i++)
	{
		clique_temp.clear();

		id = 0;
		a = 1;

		for (j = i; j < size; j++) //przechodze przez gornotrojkatna czesc macierzy 
		{
			if (i != j)
			{
				if (matrix[i][j] == 1)
				{
					if (newMyVertex[id].nr_seq != newMyVertex[j].nr_seq)  //sprawdzam czy wierzcholki sa z roznych sekwencji
					{
						id = j;
						if (a == 1)
						{
							clique_temp.push_back(newMyVertex[i]);
							a++;

						}

						matrix[i][j] = 444;
						clique_temp.push_back(newMyVertex[j]);

					}
				}
			}
			if (clique_temp.size() > clique_best.size())
				clique_best = clique_temp;
			

		}		
			
		
	}
	//cout << endl << "wypelniona macierz Z KLIKAMI" << endl;
	//for (int i = 0; i < size; ++i)
	//{
	//	cout << endl;
	//	for (int j = 0; j < size; ++j)
	//		cout << matrix[i][j] << '\t';
	//}


	cout << endl << "KLIKA: " << endl;
	for (i = 0; i < clique_best.size(); i++)
	{

		cout << endl << clique_best[i].seq << " - "<<" z sekwencji numer: " << clique_best[i].nr_seq << " -  w pozycji: " << clique_best[i].positions;
		cout << " - nr wierzcholka: " << clique_best[i].nr_vertex << endl;
	}


}


int main()
{
	vector <Vertex> MyVertex;

	int k, p;
	cout << "Podaj k <4;7>:  ";
	cin >> k;
	cout << "Podaj p <0,30>: ";
	cin >> p;
	Vertex seq;
	Read_sequences();
	Show_sequences();
	Read_qualities();
	Show_qualities();

	Create_vertexes(k, p, MyVertex);
	Show_vertexes();

	//Show_Objects(MyVertex, MyDelVertex);
	Create_Matrix(MyVertex);

}

Vertex::~Vertex() {}
