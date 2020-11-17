#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <ctime>
#include <stdlib.h>

void init(int& num_p, std::vector<int>& num_in_group , std::vector<std::string>& list_groups)
{
	std::ifstream read_file("list.dat");
	assert(read_file.is_open());
	num_p = 0;
	std::string group;
	while (std::getline(read_file,group))
	{
		list_groups.push_back(group);
		std::istringstream iss(group);	
		int num = 0;
		while (iss.good())
		{
			std::string person;
			iss >> person;
			num++;
			num_p++;
		}
		num_in_group.push_back(num);
	}
}

std::vector<int> makeGroupDist (int num_people)
{
	std::string bs;
	while (bs != "big" and bs != "small")
	{
		std::cout << "big/small group?" << "\n";
		std::cin >> bs;
	}
	std::vector<int> group_dist;
	int max_person, dec_ind, n;

	if (bs == "big")
	{
		group_dist = {4,4,4};
		max_person = 5; dec_ind = 3;
		n = num_people - 12;
	}
	else if (bs == "small")
	{
		group_dist = {3,3};
		max_person = 4; dec_ind = 2;
		n = num_people - 6;
	}
	while (n>0)
	{
		bool addgroup = true;
		for (int i = 0 ; i < group_dist.size() ; i++)
		{
			if (group_dist[i] < max_person)
			{
				group_dist[i]++;
				addgroup = false;
				break;
			}
		}
		if(addgroup)
		{
			for (int i = group_dist.size()-dec_ind; i < group_dist.size() ; i++)
			{
				group_dist[i]--;
			}
			group_dist.push_back(max_person-1);
		}
		n--;
	}
	return group_dist;
}

void roll(std::vector<int> group_dist, std::vector<std::string> list_groups, std::vector<int> num_in_group)
{
	for (int i = 0 ; i < group_dist.size() ; i++)
	{
		while (group_dist[i]>0)
		{
			int ind_rand;
			do{
				ind_rand = rand() % list_groups.size();
			}while (num_in_group[ind_rand]>group_dist[i]); //please do iteration max try catch
			std::cout << list_groups[ind_rand] << " " << std::flush;
			list_groups.erase(list_groups.begin() + ind_rand);
			group_dist[i] -= num_in_group[ind_rand];
			num_in_group.erase(num_in_group.begin() + ind_rand);
		}
		std::cout << "\n";
	}	
}
int main(int argc, char* argv[])
{
	srand((int)time(0));
	std::vector<std::string> list_groups;
	std::vector<int> num_in_group;
	int num_people;
	init(num_people,num_in_group,list_groups);
	std::cout << num_people << "\n";
	std::vector<int> group_dist = makeGroupDist(num_people);
	for (int i = 0 ; i < group_dist.size() ; i++)
	{
		std::cout << group_dist[i] << "\n";
	}
	std::string reroll;
	while (reroll != "n")
	{

		roll(group_dist,list_groups,num_in_group);
		std::cout << "reroll (y/n)" << "\n";
		std::cin >> reroll ;
	}
	return 0;
}

