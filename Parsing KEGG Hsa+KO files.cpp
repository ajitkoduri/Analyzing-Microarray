// Parsing KEGG Hsa+KO files.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

bool Find(string str, string piece)
{
	int L = piece.size();
	if (str.size() > piece.size())
	{
		for (int i = 0; i <= str.size() - L; i++)
		{
			string text = str.substr(i, i + L);
			if (text == piece)
				return true;
		}
	}
	return false;
}

int main()
{
	vector <string> Genes_Parsed;
	vector <string> Gene_File;
	string line;
	vector <string> title;
	string temp;
	string tempone;
	string temptwo;
	string tempthree;

	vector <string> hold;

	const clock_t begin_time = clock();
	
	title.resize(4);
	for (int n = 10; n <= 5300; n++)
	{
		Genes_Parsed.clear();
		Gene_File.clear();
		hold.clear();
		title.clear();
		hold.resize(3);
		title.resize(4);

		string c;
		if (n < 1000)
		{
			c = "0";
		}

		if (n < 100)
		{
			c = "00";
		}

		string str = "hsa0" + c + to_string(n) + ".txt";
		ifstream myfile(str);

		if (myfile.is_open())
		{
			cout << str << endl;
			int count = 0;
			while (getline(myfile, line))
			{
				stringstream ss(line);
				getline(ss, temp, '"');
				getline(ss, temp, '"');
				getline(ss, tempone, '"');
				getline(ss, tempone, '"');
				getline(ss, temptwo, '"');
				getline(ss, temptwo, '"');

				hold[count % 3] = temptwo;

				if (count < 5 && count > 0)
				{
					title[count - 1] = temp;
				}

				if (count > 2)
				{
					if (hold[(count - 2) % 3] == "gene")
					{
						Gene_File.push_back(temp);
					}
				}

				count++;
			}
			myfile.close();
		}

		for (int i = 0; i < Gene_File.size(); i++)
		{
			if (Gene_File[i] == "rectangle")
			{
				Gene_File.erase(Gene_File.cbegin() + i, Gene_File.cbegin() + i + 1);
			}
		}

		string h;
		for (int i = 0; i < Gene_File.size(); i++)
		{
			stringstream sstream(Gene_File[i]);
			while (getline(sstream, h, ','))
			{
				Genes_Parsed.push_back(h);
			}
		}
		for (int i = 0; i < Genes_Parsed.size(); i++)
		{
			if (Find(Genes_Parsed[i], " "))
			{
				Genes_Parsed[i].erase(Genes_Parsed[i].cbegin(), Genes_Parsed[i].cbegin() + 1);
			}
			if (Find(Genes_Parsed[i], "..."))
			{
				Genes_Parsed[i].erase(Genes_Parsed[i].cbegin() + Genes_Parsed[i].length() - 3, Genes_Parsed[i].cbegin() + Genes_Parsed[i].length());
			}
		}

		if (!Genes_Parsed.empty())
		{
			string s = "Pathways_HSA_" + to_string(n) + ".txt";
			ofstream outfile(s);
			if (outfile.is_open())
			{
				outfile << title[3] << endl;
				for (int i = 0; i < Genes_Parsed.size(); i++)
				{
					outfile << Genes_Parsed[i] << endl;
				}

			}
		}
	}

	std::cout << float(clock() - begin_time) << endl;

    return 0;
}

