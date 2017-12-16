// Parsing KEGG Data.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "linkedlist.h"

using namespace std;

bool Find(string str, string piece)
{
	int L = piece.size();
	for (int i = 0; i < str.size() - L; i++)
	{
		string text = str.substr(i, i + L);
		if (text == piece)
			return true;
	}
	return false;
}

long long ComputeHash(string word, int m)
{
	const int p = 22543;
	const int x = 26;
	long long hash = 0;
	long long x_powered = 1;
	char *word_array = new char[word.length() + 1];
	std::strcpy(word_array, word.c_str());
	for (int i = 0; i <= word.length(); i++)
	{
		hash = (hash % p) + (word_array[i] % p) * (x_powered % p);
		x_powered = (x_powered % p) * (x % p);
	}
	delete[] word_array;
	return (hash % m);
}

int main()
{
	vector <pair<long long, string>> Gene_Bank;
	vector <string> Gene_Parsed;
	vector <long long> Enzyme_Int;
	vector <string> Enzyme_File;
	string line;
	string title;
	string title_2;
	string title_3;
	string temp;
	string tempone;
	string temptwo;

	ifstream infile("Gene Bank.txt");

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			stringstream ss(line);
			getline(ss, temp, ':');
			getline(ss, tempone, ':');
			long long number = stol(temp);
			Gene_Bank.push_back(make_pair(number, tempone));
		}
		infile.close();
	}

	for (int i = 10; i < 985; i++)
	{
		Gene_Parsed.clear();
		Enzyme_Int.clear();
		Enzyme_File.clear();
		string n;
		if (i < 10)
		{
			n = "00";
		}
		else if (i < 100)
		{
			n = "0";
		}

		string str = "ec00" + n + to_string(i) + ".txt";

		ifstream myfile(str);
		if (myfile.is_open())
		{
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

				if (temptwo == "enzyme")
				{
					Enzyme_File.push_back(tempone);
				}

				if (count == 1)
				{
					title = temp;
					cout << str << endl;
				}
				if (count == 3)
				{
					title_2 = temp;
				}
				if (count == 4)
				{
					title_3 = temp;
				}
				count++;
			}
			myfile.close();
		}

		for (int i = 0; i < Enzyme_File.size(); i++)
		{
			if (Find(Enzyme_File[i], ">"))
			{
				Enzyme_File.erase(Enzyme_File.cbegin() + i, Enzyme_File.cbegin() + i + 1);
			}
		}
		for (int i = 0; i < Enzyme_File.size(); i++)
		{
			stringstream ss(Enzyme_File[i]);
			getline(ss, temp, ':');
			getline(ss, temp, ':');
			Enzyme_File[i] = temp;
		}
		for (int i = 0; i < Enzyme_File.size(); i++)
		{
			if (!Find(Enzyme_File[i], "-"))
			{
				long long hash = ComputeHash(Enzyme_File[i], 9291);
				Enzyme_Int.push_back(hash);
			}
		}

		for (int i = 0; i < Enzyme_Int.size(); i++)
		{
			string hold = Gene_Bank[Enzyme_Int[i]].second;
			stringstream hs(hold);
			while (getline(hs, temp, ','))
			{
				if (Find(temp, Enzyme_File[i]))
				{
					stringstream sss(temp);
					getline(sss, tempone, ' ');
					getline(sss, temptwo, ' ');
					Gene_Parsed.push_back(temptwo);
				}
			}
		}

		string s = "Pathways_" + to_string(i) + ".txt";
		ofstream outfile(s);
		if (outfile.is_open())
		{
			outfile << title << endl;
			outfile << title_2 << endl;
			outfile << title_3 << endl;
			for (int i = 0; i < Gene_Parsed.size(); i++)
			{
				outfile << Gene_Parsed[i] << endl;
			}

		}
	}

    return 0;
}

