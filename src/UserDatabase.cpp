#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    
}

UserDatabase::~UserDatabase()
{
    for (int i = 0; i <vector_users.size();i++)
    {
        delete vector_users[i];
    }
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open the file!" << endl;
        return false;
    }

    string line;
    string name;
    string email;
    int movies;

    while (getline(infile, line))
    {
        if (line=="")
            continue;

        name = line; //gets the username which is at the top

        getline(infile, email); //reading email address

        infile >> movies; //reads the number of movies;
        infile.ignore(10000, '\n');

        vector<string> movie_ids; //reading the movie IDs
        for (int i = 0; i < movies; i++)
        {
            getline(infile, line);
            movie_ids.push_back(line);
        }

        User *user = new User(name, email, movie_ids);
        vector_users.push_back(user);
        m_users.insert(email, user);
        
        if(!getline(infile, line))
            break;
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!m_users.find(email).is_valid())
        return nullptr;
    
    else return m_users.find(email).get_value();
}
