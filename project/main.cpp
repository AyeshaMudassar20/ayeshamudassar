#include"header.h"   
#include<fstream>
#include<string>
#include<iostream>

using namespace std;

int main()
{
    Account account;
    string user, pass, repoName, fileName;
    int val, val2;

    Git git{};
    Repos repos{};

    bool log = false;
    do
    {
        system("color 0B");

        cout << "\t\t\t<Git Simulator>\n";

        cout << "\n\n Please Select an Option:\n\n";
        cout << "1) Register\n";
        cout << "2) Login\n";
        cout << "3) Exit\n";
        cout << "\nEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            cout << "\nEnter Username : ";
            cin >> user;
            cout << "\nEnter Password : ";
            cin >> pass;
            cout << endl;
            if (account.regsiter(user, pass))
            {
                cout << "Registered Successfully!\n\n";
            }
            else
            {
                cout << "Invalid Username!!\n\n";
            }
        }
        else if (val == 2)
        {
            cout << "Login\n";
            cout << endl << endl << "Enter Username : ";
            cin >> user;
            cout << endl << endl << "Enter Password : ";
            cin >> pass;
            cout << endl;
            log = git.chkUser(user, pass);
            if (log)
            {
                cout << "Successfully Logged In!\n\n";
            }
            else
            {
                cout << "Invalid Username or Password!!\n\n";
            }
        }
        else if (val == 3)
        {
            cout << "Exiting\n";
            break;
        }
        else
        {
            cout << "Invalid Choice\n";
        }

        if (log)
        {
            do
            {
                cout << "\tGit Simulator\n\n";
                cout << "Please Select an Option:\n";
                cout << "0) Social Features\n";
                cout << "1) Create Repository\n";
                cout << "2) Remove Repository\n";
                cout << "3) Create File in Repository\n";
                cout << "4) Remove File from Repository\n";
                cout << "5) Search a Repository\n";
                cout << "6) Search a File in Repository\n";
                cout << "7) Commit in Repository\n";
                cout << "8) Display All Repository\n";
                cout << "9) Logout\n";
                cout << "\nEnter: ";
                cin >> val2;

                switch (val2)
                {
                case 0:
                {
                    SocialNetwork network;
                    network.readUsersFromFile("Users.txt");
                    cout << " Social Features\n";

                    string username, action, target;
                    while (true)
                    {
                        cout << "Enter username : ";
                        cin >> username;

                        if (!network.userExists(username))
                        {
                            cout << "User " << username << " not found." << endl;
                            continue;
                        }

                        cout << "Enter action" << endl;
                        cout << "1) follow\n";
                        cout << "2) unfollow\n";
                        cout << "3) display\n";
                        cout << "4) exit\n";
                        cin >> action;

                        if (action == "follow" || action == "unfollow")
                        {
                            cout << "Enter target username: ";
                            cin >> target;

                            if (!network.userExists(target))
                            {
                                cout << "User " << target << " not found." << endl;
                                continue;
                            }

                            if (action == "follow")
                            {
                                network.follow(username, target);
                            }
                            else
                            {
                                network.unfollow(username, target);
                            }
                        }
                        else if (action == "display")
                        {
                            network.displayFollowers(username);
                        }
                        else if (action == "exit")
                        {
                            cout << "Exiting social features..\n";
                            break; // Exit the social features submenu
                        }
                        else
                        {
                            cout << "Invalid action. Please try again." << endl;
                        }
                    }
                    break;
                }
                case 1:
                    cout << "Respository Creation\n";
                    cout << "Enter Repo Name:\n";
                    cin >> repoName;
                    repos.Repo(user, repoName, "add");
                    cout << "Repository Created!!!\n";
                    break;
                case 2:
                    cout << "Respository Deletion\n";
                    if (repos.Repo(user, repoName, "delete"))
                    {
                        cout << "Repository Deleted\n";
                    }
                    else
                    {
                        cout << "Repository Not Deleted\n";
                    }
                    break;
                case 3:
                    cout << "File Creation in Respository\n";
                    cout << "\n\nEnter File Name:\n";
                    cin >> fileName;
                    cout << "Enter Repository Name:\n";
                    cin >> repoName;
                    repos.File(user, repoName, fileName, "add");
                    cout << "File Created\n";
                    break;
                case 4:
                    cout << "File deletion from respository\n";
                    cout << "\n\nEnter File Name:\n";
                    cin >> fileName;
                    if (repos.File(user, repoName, fileName, "delete"))
                    {
                        cout << "File Deleted\n";
                    }
                    else
                    {
                        cout << "File Not Deleted\n";
                    }
                    break;
                case 5:
                    cout << "Searching Respository details\n";
                    cout << "Enter Repository Name: ";
                    cin >> repoName;
                    if (!repos.Repo(" ", repoName, "searchRepoDetails"))
                    {
                        cout << "Repository Not Found\n";
                    }
                    else
                    {
                        cout << "Repository Found\n";
                    }
                    break;
                case 6:
                    cout << "Searching file\n";
                    cout << "Enter File name: ";
                    cin >> fileName;
                    if (!repos.File(" ", repoName, fileName, "searchRepoDetails"))
                    {
                        cout << "File Not Found\n";
                    }
                    else
                    {
                        cout << "File found\n";
                    }
                    break;
                case 7:
                    cout << "Respository commits\n";
                    repos.Repo(" ", repoName, "commit");
                    cout << "Committed\n";
                    break;
                case 8:
                    cout << "Displaying All Repositories\n";
                    repos.displayRepo(user);
                    break;
                case 9:
                    cout << "Logging Out\n";
                    log = false;
                    break;
                default:
                    cout << "Invalid Choice\n";
                    break;
                }
                cout << endl;

            } while (val2 != 9);
        }
    } while (val != 3);

    return 0;
}
