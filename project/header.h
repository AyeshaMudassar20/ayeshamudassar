#ifndef GIT_H
#define GIT_H

#include<iostream>
#include<string>
#include <unordered_map>
#include <vector>

using namespace std;

class Account
{
private:
	string username, password;
	static int totalAcc;
	friend class Git;
public:
	bool regsiter(string username, string password);
};


class Git
{
private:
	Account* accounts;
	int hash(string username, int size) const;
public:
	bool chkUser(string user, string pass);
};


class Node
{
public:
	string data;
	int ch;
	Node* childs;
	int comits;
	Node() : data(""), ch(0), childs(NULL), comits(0) {}
};


class Repos
{
private:
	Node* node;
	void Tree(string x);
public:
	void addToRepo(string user);
	bool Repo(string user, string repoName, string x);
	bool File(string user, string repoName, string fileName, string x);
	void displayRepo(string user);
};
//Socials
class SocialNetwork
{
private:
	unordered_map<string, vector<string>> graph; // Key: user, Value: followers
public:
	void updateFollowersFile(const string& followee, const string& follower);
	void removeFollowerFromFile(const string& followee, const string& follower);
	void readUsersFromFile(const string& filename);
	bool userExists(const string& username) const;
	void follow(const string& follower, const string& followee);
	void unfollow(const string& follower, const string& followee);
	bool isFollowing(const string& follower, const string& followee) const;
	void displayFollowers(const string& username) const;
};


#endif