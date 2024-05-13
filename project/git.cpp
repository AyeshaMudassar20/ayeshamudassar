#include"header.h"
#include<fstream>
#include<vector>
#include<string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include<iostream>
using namespace std;
bool checkStringSimilarity(string x, string y);
bool Git::chkUser(string user, string pass) //User Login
{
	int count = 0;
	ifstream in;
	in.open("Count.txt");
	in >> count;
	in.close();
	accounts->totalAcc = count * 2;
	this->accounts = new Account[count * 2];//dynamic memory allocation
	for (int i = 0; i < count * 2; i++) 
	{
		accounts[i].username = " ";
	}

	in.open("Users.txt");

	int index;
	string userr, passs;
	for (int i = 0; i < count; i++) 
	{
		in >> userr >> passs;
		index = hash(user, count * 2);//to calculate an index,
		accounts[index].username = userr;
		accounts[index].password = passs;
	}

	int total = 0;
	for (int i = 0; i < user.length(); i++)
	{
		total += int(user[i]);
	}
	int value = total % (count * 2);
	while (accounts[value].username != " " && accounts[value].username != user)
	{
		if (value == accounts->totalAcc)
		{
			value = 0;
		}
		value++;
	}
	if (accounts[value].username == user && accounts[value].password == pass)
	{
		return true;
	}
	return false;
}
int Git::hash(string username, int size) const //constant hash funstion
{
	int total = 0;
	for (int i = 0; i < username.length(); i++)
	{
		total += int(username[i]);//Adds the ASCII value of the characters of the username
	}
	int value = total % size;
	while (accounts[value].username != " ")
	{
		value++;
		if (value == size)
		{
			value = 0;
		}
	}
	return value;
}

int Account::totalAcc = 0;
bool Account::regsiter(string username, string password) //User Registeration
{
	Repos rp;
	ifstream in;
	bool valid = true;
	in.open("Users.txt");

	string usrr, pss;
	while (!in.eof()) //ye loop user ko file se read krne k liye hai
	{
		in >> usrr >> pss;

		if (checkStringSimilarity(username, usrr)) //ye condition check kr rhi hai k user already exist hai ya nahi
		{
			valid = false;
		}
	}
	in.close();

	if (valid)
	{
		ofstream out;
		out.open("Users.txt", ios::app);
		out << username << endl << password << endl;
		out.close();

		int count;
		ifstream in;
		in.open("Count.txt");
		in >> count;
		in.close();

		out.open("Count.txt");
		count++;
		out << count;
		out.close();

		rp.addToRepo(username);

		return true;
	}
	return false;
}
bool checkStringSimilarity(string x, string y)
{
	if (x.length() != y.length())
		return false;
	else
	{
		for (int i = 0; i < x.length(); i++)
		{
			if (x[i] != y[i])
			{
				return false;
			}
		}
		return true;
	}
}
void Repos::Tree(string x) //Tree Structure
{
	if (x == "load")
	{
		ifstream in;
		in.open("Repositories.txt");

		int users, repos, files;
		string str;
		in >> users;
		node = new Node;
		node->childs = new Node[users];
		node->ch = users;

		for (int i = 0; i < users; i++) //Es loop mn user ko file se read kr k tree mn store kr rha hai
		{
			in >> str;
			node->childs[i].data = str;
			in >> repos;
			node->childs[i].childs = new Node[repos];
			node->childs[i].ch = repos;
			for (int j = 0; j < repos; j++)
			{
				in >> str;
				node->childs[i].childs[j].data = str;
				in >> files;
				node->childs[i].childs[j].childs = new Node[files];
				node->childs[i].childs[j].ch = files;
				for (int k = 0; k < files; k++)
				{
					in >> str;
					node->childs[i].childs[j].childs[k].data = str;
				}
			}
		}
		in.close();
	}
	else if (x == "unload")
	{
		ofstream out;
		out.open("Repositories.txt");
		out << node->ch << endl;

		for (int i = 0; i < node->ch; i++)
		{
			out << node->childs[i].data << endl;
			out << node->childs[i].ch << endl;

			for (int j = 0; j < node->childs[i].ch; j++)
			{
				out << node->childs[i].childs[j].data << endl;
				out << node->childs[i].childs[j].ch << endl;
				for (int k = 0; k < node->childs[i].childs[j].ch; k++)
				{
					out << node->childs[i].childs[j].childs[k].data << endl;
				}
			}
		}
	}
}

void Repos::addToRepo(string user) //Add User to Repository
{
	ifstream in;
	in.open("Repositories.txt");

	int users = 0, repos = 0, files;
	string str;
	in >> users;
	node = new Node();
	node->childs = new Node[users];
	node->ch = users;

	for (int i = 0; i < users; i++)
	{
		in >> str;
		node->childs[i].data = str;
		in >> repos;
		node->childs[i].childs = new Node[repos];
		node->childs[i].ch = repos;
		for (int j = 0; j < repos; j++)
		{
			in >> str;
			node->childs[i].childs[j].data = str;
			in >> files;
			node->childs[i].childs[j].childs = new Node[files];
			node->childs[i].childs[j].ch = files;
			for (int k = 0; k < files; k++)
			{
				in >> str;
				node->childs[i].childs[j].childs[k].data = str;
			}
		}
	}
	in.close();

	ofstream out;
	out.open("Repositories.txt");
	out << node->ch + 1 << endl;

	for (int i = 0; i < node->ch; i++)
	{
		out << node->childs[i].data << endl;
		out << node->childs[i].ch << endl;
		for (int j = 0; j < node->childs[i].ch; j++)
		{
			out << node->childs[i].childs[j].data << endl;
			out << node->childs[i].childs[j].ch << endl;
			for (int k = 0; k < node->childs[i].childs[j].ch; k++)
			{
				out << node->childs[i].childs[j].childs[k].data << endl;
			}
		}
	}

	out << user << endl << 0 << endl;
}

bool Repos::File(string user, string repoName, string fileName, string x) //File Functions
{
	if (x == "add")
	{
		ifstream in;
		in.open("Repositories.txt");

		int users, repos, files;
		string str;
		in >> users;
		node = new Node;
		node->childs = new Node[users];
		node->ch = users;

		for (int i = 0; i < users; i++)
		{
			in >> str;
			node->childs[i].data = str;
			in >> repos;
			node->childs[i].childs = new Node[repos];
			node->childs[i].ch = repos;
			for (int j = 0; j < repos; j++) //Es loop mn file ko add krne k liye hai
			{
				in >> str;
				node->childs[i].childs[j].data = str;
				in >> files;
				if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName)
				{
					files++;
				}
				node->childs[i].childs[j].childs = new Node[files];
				node->childs[i].childs[j].ch = files;
				for (int k = 0; k < files; k++)
				{
					if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && k == files - 1)
					{
						node->childs[i].childs[j].childs[k].data = fileName;
					}
					else
					{
						in >> str;
						node->childs[i].childs[j].childs[k].data = str;
					}
				}
			}
		}
		in.close();
		Tree("unload");
	}
	else if (x == "delete")
	{
		Tree("load");

		if (!File(user, repoName, fileName, "search"))
		{
			return false;
		}

		ofstream out;
		out.open("Repositories.txt");

		out << node->ch << endl;
		for (int i = 0; i < node->ch; i++)
		{
			out << node->childs[i].data << endl;
			out << node->childs[i].ch << endl;
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				out << node->childs[i].childs[j].data << endl;
				if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName)
				{
					out << node->childs[i].childs[j].ch - 1 << endl;
				}
				else
				{
					out << node->childs[i].childs[j].ch << endl;
				}
				for (int k = 0; k < node->childs[i].childs[j].ch; k++)
				{
					if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && node->childs[i].childs[j].childs[k].data == fileName)
					{
					}
					else
					{
						out << node->childs[i].childs[j].childs[k].data << endl;
					}
				}
			}
		}
		return true;
	}
	else if (x == "search")
	{
		for (int i = 0; i < node->ch; i++)
		{
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				for (int k = 0; k < node->childs[i].childs[j].ch; k++)
				{
					if (node->childs[i].data != user || node->childs[i].childs[j].data != repoName)
					{
						break;
					}
					else if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName && node->childs[i].childs[j].childs[k].data == fileName)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
}

bool Repos::Repo(string user, string repoName, string x) //Repository Functions
{
	Tree("load");

	if (x == "add")
	{
		ifstream in;
		in.open("Repositories.txt");

		int users, repos, files;
		string str;
		in >> users;
		node = new Node;
		node->childs = new Node[users];
		node->ch = users;

		for (int i = 0; i < users; i++)
		{
			in >> str;
			node->childs[i].data = str;
			in >> repos;
			if (str == user)
			{
				repos++;
			}
			node->childs[i].childs = new Node[repos];
			node->childs[i].ch = repos;
			for (int j = 0; j < repos; j++)
			{
				if (node->childs[i].data == user && j == repos - 1)
				{
					node->childs[i].childs[j].data = repoName;
					node->childs[i].childs[j].ch = 0;
				}
				else
				{
					in >> str;
					node->childs[i].childs[j].data = str;
					in >> files;
					node->childs[i].childs[j].childs = new Node[files];
					node->childs[i].childs[j].ch = files;
					for (int k = 0; k < files; k++)
					{
						in >> str;
						node->childs[i].childs[j].childs[k].data = str;
					}
				}
			}
		}
		in.close();
		Tree("unload");
		return true;
	}
	else if (x == "delete")
	{
		Tree("load");

		if (!Repo(user, repoName, "search"))
		{
			return false;
		}

		ofstream out;
		out.open("Repositories.txt");
		out << node->ch << endl;

		for (int i = 0; i < node->ch; i++)
		{
			out << node->childs[i].data << endl;
			if (node->childs[i].data == user)
			{
				out << node->childs[i].ch - 1 << endl;
			}
			else
			{
				out << node->childs[i].ch << endl;
			}
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				if (node->childs[i].data != user && node->childs[i].childs[j].data != repoName)
				{
					out << node->childs[i].childs[j].data << endl;
					out << node->childs[i].childs[j].ch << endl;
					for (int k = 0; k < node->childs[i].childs[j].ch; k++)
					{
						out << node->childs[i].childs[j].childs[k].data << endl;
					}
				}
			}
		}
		return true;
	}
	else if (x == "search")//Search Repository
	{
		bool flag = false;
		for (int i = 0; i < node->ch; i++)
		{
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				if (node->childs[i].data != user)
				{
					break;
				}
				else if (node->childs[i].data == user && node->childs[i].childs[j].data == repoName)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (x == "commit")	//Commit Repository
	{
		Tree("load");
		for (int i = 0; i < node->ch; i++)
		{
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				if (node->childs[i].childs[j].data == repoName)
				{
					node->childs[i].childs[j].comits++;
				}
			}
		}
	}
	else if (x == "searchRepoDetails")	 //Search Repository Details		
	{
		Tree("load");
		bool flag = false;
		for (int i = 0; i < node->ch; i++)
		{
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				if (node->childs[i].childs[j].data == repoName)
				{
					cout << "\n";
					cout << "\n\t-> User        :  " << node->childs[i].data;
					cout << "\n\t-> Repo Name   :  " << node->childs[i].childs[j].data;
					cout << "\n\t-> Total Files :  " << node->childs[i].childs[j].ch;
					cout << "\n\n";
					return true;
				}
			}
		}
		return false;
	}

}

void Repos::displayRepo(string user)
{
	Tree("load");
	for (int i = 0; i < node->ch; i++)
	{
		if (node->childs[i].data == user)
		{
			for (int j = 0; j < node->childs[i].ch; j++)
			{
				cout << "\n\t-> Repository Name: " << node->childs[i].childs[j].data;
				cout << "\n\t-> Files: ";
				for (int k = 0; k < node->childs[i].childs[j].ch; k++)
				{
					cout << node->childs[i].childs[j].childs[k].data << " ";
				}
				cout << "\n\n";
			}
		}
	}
}
//Socials
void SocialNetwork::readUsersFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cerr << "Error: Unable to open file " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string username;
		ss >> username;
		string follower;
		vector<string> followers;
		while (ss >> follower)
		{
			followers.push_back(follower);
			updateFollowersFile(username, follower); // Update followers file
		}
		graph[username] = followers;
	}
	file.close();
}

// Function to update followers file
void SocialNetwork::updateFollowersFile(const string& followee, const string& follower)
{
	ofstream file(followee + "_followers.txt", ios::app);
	if (file.is_open())
	{
		file << follower << endl;
		file.close();
	}
	else
	{
		cerr << "Error: Unable to update followers file for user " << followee << endl;
	}
}

// Function to remove follower from followers file
void SocialNetwork::removeFollowerFromFile(const string& followee, const string& follower)
{
	string line;
	ifstream inFile(followee + "_followers.txt");
	ofstream outFile(followee + "_temp.txt");
	while (getline(inFile, line))
	{
		if (line != follower)
			outFile << line << endl;
	}
	inFile.close();
	outFile.close();
	remove((followee + "_followers.txt").c_str());
	rename((followee + "_temp.txt").c_str(), (followee + "_followers.txt").c_str());
}

// Function to check if user exists
bool SocialNetwork::userExists(const string& username) const
{
	return graph.find(username) != graph.end();
}

// Function to follow another user
void SocialNetwork::follow(const string& follower, const string& followee)
{
	if (!userExists(followee))
	{
		cout << "User " << followee << " not found." << endl;
		return;
	}

	if (follower == followee)
	{
		cout << "You cannot follow yourself." << endl;
		return;
	}

	if (!isFollowing(follower, followee))
	{
		graph[follower].push_back(followee);
		updateFollowersFile(followee, follower); // Update followers file
		cout << follower << " is now following " << followee << endl;
	}
	else {
		cout << follower << " is already following " << followee << endl;
	}
}

void SocialNetwork::unfollow(const string& follower, const string& followee)
{
	if (!userExists(followee))
	{
		cout << "User " << followee << " not found." << endl;
		return;
	}

	if (isFollowing(follower, followee))
	{
		auto it = find(graph[follower].begin(), graph[follower].end(), followee);
		graph[follower].erase(it);
		removeFollowerFromFile(followee, follower); // Remove follower from followers file
		cout << follower << " unfollowed " << followee << endl;
	}
	else
	{
		cout << follower << " is not following " << followee << endl;
	}
}

void SocialNetwork::displayFollowers(const string& username) const
{
	ifstream file(username + "_followers.txt");
	if (!file.is_open())
	{
		cout << "No followers found for user " << username << endl;
		return;
	}

	string follower;
	cout << "Followers of " << username << ":" << endl;
	while (getline(file, follower))
	{
		cout << follower << endl;
	}
	file.close();
}
// Function to check if a user is already following another user
bool SocialNetwork::isFollowing(const string& follower, const string& followee) const
{
	if (!userExists(follower) || !userExists(followee))
	{
		return false;
	}
	return find(graph.at(follower).begin(), graph.at(follower).end(), followee) != graph.at(follower).end();
}