#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED
#include "treemm.h"

#include <string>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User*> m_users;
    std::vector<User*> vector_users;
    //std::multimap<std::string, User*> m_users;
};

#endif // USERDATABASE_INCLUDED
