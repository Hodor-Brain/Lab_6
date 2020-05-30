#include "Header.h"

void main()
{
	Graph my;

	my.initGraph();

	char f[] = "Graph.TXT";
	char* a = f;

	my.save(a);

	my.load(a);

	my.printMatrix();

	int** Matrix = new int*[20];
	for (int i = 0; i < 20; i++)
	{
		Matrix[i] = new int[20];
	}

	my.DistMatrix(Matrix);

	floyd(my,Matrix);

	int diameter = 0;

	for (int i = 0; i < my.getNumOfV(); i++)
	{
		int max = 0;
		
		for (int j = 0; j < my.getNumOfV(); j++)
		{
			if (Matrix[i][j] > max)
			{
				max = Matrix[i][j];
			}
		}

		if (max > diameter)
		{
			diameter = max;
		}
	}

	cout << endl;
	cout << "Diameter of graph = " << diameter << endl;
}