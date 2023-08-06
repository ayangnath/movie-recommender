#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history): m_userName(full_name), m_userEmail(email), m_watch_history(watch_history)
{
    // Replace this line with correct code.
}

User::~User(){};

string User::get_full_name() const
{
    return m_userName;  // Replace this line with correct code.
}

string User::get_email() const
{
    return m_userEmail;  // Replace this line with correct code.
}

vector<string> User::get_watch_history() const
{
    return m_watch_history;  // Replace this line with correct code.
}
