#pragma once

#include <iostream>

using namespace std;

const int maxN = 20;

typedef struct Node
{
	Node* pnext = nullptr;
	int Vertix = 0;
}*StrAdj;

struct Graph
{
private:
	int numOfVertices = 0;
	bool matrix[maxN][maxN] = { };

	StrAdj str_adj[maxN] = {};

	void addEdge(int i, int j)
	{
		if (i > numOfVertices || j > numOfVertices || i <= 0 || j <= 0 || i == j)
			return;
		i--; j--;
		matrix[i][j] = true;
		matrix[j][i] = true;
	}

public:

	Graph()
	{
		for (int i = 0; i < maxN; i++)
			for (int j = 0; j < maxN; j++)
				matrix[i][j] = 0;
	}

	void save(char* filename)
	{
		FILE* file;
		fopen_s(&file, filename, "wb+");

		if (file)
			fwrite(this, sizeof(Graph), 1, file);

		if (file)
			fclose(file);
	}

	void load(char* filename)
	{
		FILE* file;
		fopen_s(&file, filename, "rb+");

		if (file)
			fread(this, sizeof(Graph), 1, file);

		for (int i = 0; i < numOfVertices; i++)
			str_adj[i] = nullptr;

		if (file)
			fclose(file);

	}

	void initGraph()
	{
		while (numOfVertices <= 0 || numOfVertices > maxN)
		{
			std::cout << "Num of verticles = ";
			std::cin >> numOfVertices;
		}

		int answer = 1, firstVertix = 0, secondVertix = 0;
		while (answer == 1)
		{
			std::cout << "First vertix = ";
			std::cin >> firstVertix;

			std::cout << "Second vertix = ";
			std::cin >> secondVertix;

			addEdge(firstVertix, secondVertix);

			std::cout << "One more? (1 - Yes, 2 - No)\n";
			std::cin >> answer;

			system("cls");
		}

		system("cls");
	}

	int getNumOfV()
	{
		return numOfVertices;
	}

	void printMatrix()
	{
		if (!numOfVertices)
			return;

		std::cout << "Matrix is :\n";

		for (int i = 0; i < 4; i++)
			std::cout << ' ';

		for (int i = 0; i < numOfVertices; i++)
		{
			std::cout << '[' << i + 1 << ']';
		}
		std::cout << std::endl;

		for (int i = 0; i < numOfVertices; i++)
		{
			std::cout << '[' << i + 1 << ']';
			std::cout << ' ';

			for (int j = 0; j < numOfVertices; j++)
			{
				std::cout << ' ';
				if (matrix[i][j])
					std::cout << '1';
				else
					std::cout << '0';
				std::cout << ' ';
			}
			std::cout << std::endl;
		}
	}

	void DistMatrix(int** Matrix)
	{
		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				if (matrix[i][j] == true)
				{
					Matrix[i][j] = 1;
				}
				else
				{
					Matrix[i][j] = 0;
				}
			}
		}
	}
	void PrintDistMatr(int** Matrix)
	{
		cout << endl;
		cout << "Matrix is :" << endl;

		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				cout << Matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}
};

void floyd(Graph our, int** Matrix)
{
	int i, j, k;

	for (k = 0; k < our.getNumOfV(); k++)
	{
		for (i = 0; i < our.getNumOfV(); i++)
		{
			for (j = 0; j < our.getNumOfV(); j++)
			{
				if (i == j)
				{
					Matrix[i][j] = 0;
					continue;
				}
				if (Matrix[i][k] != 0 && Matrix[k][j] != 0 && Matrix[i][j] != 0)
				{
					if (Matrix[i][k] + Matrix[k][j] < Matrix[i][j])
					{
						Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
					}
				}
				else if (Matrix[i][j] != 0)
				{
					continue;
				}
				else if (Matrix[i][k] != 0 && Matrix[k][j] != 0)
				{
					Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
				}
			}
		}
	}
}