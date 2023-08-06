#include "Recommender.h"
#include "User.h"
#include "UserDatabase.h"
#include "Movie.h"
#include "MovieDatabase.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database) : m_userDatabase(user_database), m_movieDatabase(movie_database)
{}

Recommender::~Recommender(){}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<MovieAndRank> result;
    unordered_map<string, int> map;
    
    User* u = m_userDatabase.get_user_from_email(user_email); //finding the user
    
    if (!u || movie_count<=0)
        return vector<MovieAndRank>();
    
    vector<string> watchHistory = u->get_watch_history(); //getting the user's watch history
    
    for (int i = 0; i < watchHistory.size(); i++) //for every movie in the watch history, execute the code below
    {
        Movie* mov = m_movieDatabase.get_movie_from_id(watchHistory.at(i)); //finding the current movie
        
        vector<string> directors = mov->get_directors();
        for (int j = 0; j < directors.size(); j++) //looping through the directors in current movie
        {
            //For each director d associated with m, each movie in the movie database that
            //has d in its list of directors contributes 20 points to the compatibility score
            vector<Movie*> moviesWithDirector = m_movieDatabase.get_movies_with_director(directors.at(j)); //get all the movies with this director
            for (int k = 0; k < moviesWithDirector.size(); k++)
            {
                string id = moviesWithDirector.at(k)->get_id();
                map[id]+=20;
            }
        }
        
        vector<string> actors = mov->get_actors();
        for (int j = 0; j < actors.size(); j++)
        {
            //For each actor a associated with m, each movie in the movie database that has a
            //in its list of actors contributes 30 points to the compatibility score
            vector<Movie*> moviesWithActor = m_movieDatabase.get_movies_with_actor(actors.at(j)); //get all movies with this actor
            for (int k = 0; k< moviesWithActor.size(); k++)
            {
                string id = moviesWithActor.at(k)->get_id();
                map[id]+=30;
            }
        }
        
        vector<string> genres = mov->get_genres();
        for (int j = 0; j < genres.size(); j++)
        {
            //For each genre g associated with m, each movie in the movie database that has
            //g in its list of genres contributes 1 point to the compatibility score
            vector<Movie*> moviesWithGenre = m_movieDatabase.get_movies_with_genre(genres.at(j)); //gets all movie with this genre
            for (int k = 0; k < moviesWithGenre.size(); k++)
            {
                string id = moviesWithGenre.at(k)->get_id();
                map[id]+=1;
            }
        }
    }
    
    for (int j = 0; j < watchHistory.size(); j++) //erasing all movies that user already watched from the map
    {
        map.erase(watchHistory.at(j));
    }
    
    for (auto it = map.begin(); it!= map.end(); it++) //looping through the map and adding to a vector so it can be sorted
    {
        result.push_back(MovieAndRank(it->first, it->second));
    }
    
    std::sort(result.begin(), result.end(), compScore());
    
    if (movie_count< result.size())
        return vector<MovieAndRank>(result.begin(), result.begin()+movie_count);
    else return result;
}
