#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

void findMatches(const Recommender& r,
 const MovieDatabase& md,
 const string& user_email,
 int num_recommendations) {
 // get up to ten movie recommendations for the user
 vector<MovieAndRank> recommendations =
 r.recommend_movies(user_email, 10);
 if (recommendations.empty())
 cout << "We found no movies to recommend :(.\n";
 else {
for (int i = 0; i < recommendations.size(); i++) {
 const MovieAndRank& mr = recommendations[i];
 Movie* m = md.get_movie_from_id(mr.movie_id);
 cout << i+1 << ". " << m->get_title() << " ("
 << m->get_release_year() << ")\n Rating: "
 << m->get_rating() << "\n Compatibility Score: "
 << mr.compatibility_score << "\n";
}
 }
}

const string USER_DATAFILE  = "/Users/ayannath/Desktop/Pnetphlix/Pnetphlix/users.txt";
const string MOVIE_DATAFILE = "/Users/ayannath/Desktop/Pnetphlix/Pnetphlix/movies.txt";

//uncomment these lines in g32
// const string USER_DATAFILE= "/u/eng/class/classnth/proj4/users.txt";
// const string MOVIE_DATAFILE= "/u/eng/class/classnth/proj4/movies.txt";


int main()
{
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    
    
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }

    for (;;)
    {
        cout << "What do you want to test? (or say quit) Say: user, id, director, actor, genre, or recs: ";
        string answer;
        getline(cin, answer);
        
        if (answer == "quit")
            return 0;
        
        if (answer == "user")
        {
            cout << "Enter user email address (or quit): ";
            string email;
            getline(cin, email);
            if (email == "quit")
                return 0;
            User* u = udb.get_user_from_email(email);
            if (u == nullptr)
                cout << "No user in the database has that email address." << endl;
            else
            {
                cout << "Found " << u->get_full_name() << endl;
                vector<string> watch_history = u->get_watch_history();
                for(int i = 0 ; i < watch_history.size(); i++)
                {
                    cout << watch_history[i] << endl;
                }
            }
        }
        
        if (answer == "id")
        {
            cout << "Enter 7 character movie id (or quit): ";
            string id;
            getline(cin, id);
            if (id == "quit")
                return 0;
            Movie* m = mdb.get_movie_from_id(id);
            if (m == nullptr)
                cout << "No movie in the database has that this movie ID." << endl;
            else
                cout << "Found " << m->get_title() << endl;
        }
        
        if (answer == "director")
        {
            cout << "Enter a director (or quit): ";
            string director;
            getline(cin, director);
            if (director == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_director(director);
            if (result.size()==0)
                cout << "No movies in the database has that this director." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout <<result[i]->get_title()<< endl;
            }
        }
        
        if (answer == "actor")
        {
            cout << "Enter a actor (or quit): ";
            string actor;
            getline(cin, actor);
            if (actor == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_actor(actor);
            if (result.size()==0)
                cout << "No movies in the database has that this actor." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout <<result[i]->get_title()<< endl;
            }
        }
        
        if (answer == "genre")
        {
            cout << "Enter a genre (or quit): ";
            string genre;
            getline(cin, genre);
            if (genre == "quit")
                return 0;
            vector<Movie*> result = mdb.get_movies_with_genre(genre);
            if (result.size()==0)
                cout << "No movies in the database has that this genre." << endl;
            else
            {
                for (int i = 0; i < result.size(); i++)
                    cout <<result[i]->get_title()<< endl;
            }
        }
        
        if (answer == "recs")
        {
            string user;
            cout << "Enter a user for recs (or quit): ";
            getline(cin, user);
            if (user == "quit")
                return 0;
            Recommender name(udb, mdb);
            findMatches(name, mdb, user, 10);
        }
        
    }
    
}
