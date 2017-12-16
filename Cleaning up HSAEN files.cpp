// Cleaning up HSAEN files.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "linkedlist.h"

bool Find(vector <string> vecint, string num)
{
	for (int i = 0; i < vecint.size(); i++)
	{
		if (vecint[i] == num)
		{
			return true;
		}
	}

	return false;
}

void RemoveDuplicates(vector <string>& vecstr)
{
	vector <string> holder;

	for (int i = 0; i < vecstr.size(); i++)
	{
		if (!Find(holder, vecstr[i]))
		{
			holder.push_back(vecstr[i]);
		}
	}
	vecstr.clear();
	for (int i = 0; i < holder.size(); i++)
	{
		vecstr.push_back(holder[i]);
	}
	holder.clear();
}

int main()
{
	string str;
	string hold;
	int count = 0;
	vector <string> PathwayGenes;

	//input data from all hsa files
	for (int n = 10; n <= 5300; n++)
	{
		PathwayGenes.clear();
		str = "Pathways_HSA_" + to_string(n) + ".txt";
		ifstream Pathways(str);
		if (Pathways.is_open())
		{
			while (getline(Pathways, hold))
			{
				PathwayGenes.push_back(hold);
			}


		//delete duplicates
		RemoveDuplicates(PathwayGenes);
		cout << str << endl;
		//insert data back into text file
		ofstream myfile(str);
		for (int i = 0; i < PathwayGenes.size(); i++)
		{
			myfile << PathwayGenes[i] << endl;
		}
		Pathways.close();
		}
	}
    return 0;
}

