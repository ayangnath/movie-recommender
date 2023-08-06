#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> m_id; //given an id, can map to a movie
    TreeMultimap<std::string, Movie*> m_directors; //given a director, can map to all movies with that director
    TreeMultimap<std::string, Movie*> m_actors; //given an actor, can map to all movies with that actor
    TreeMultimap<std::string, Movie*> m_genres; //given a genre, can map to all movies with that genre
    std::vector<Movie*> vector_movies; //storing all the Movie pointers in a vector so easy to delete in constructor
};

#endif // MOVIEDATABASE_INCLUDED
