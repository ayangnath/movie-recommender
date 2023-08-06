#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}
    
    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    ~Recommender();
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    const UserDatabase& m_userDatabase;
    const MovieDatabase& m_movieDatabase;
    auto compScore() const{
        return [this](const MovieAndRank& left, const MovieAndRank& right)
        {
            if (left.compatibility_score > right.compatibility_score)
                return true;
            else if (left.compatibility_score < right.compatibility_score)
                return false;
            
            float leftRating = m_movieDatabase.get_movie_from_id(left.movie_id)->get_rating();
            float rightRating = m_movieDatabase.get_movie_from_id(right.movie_id)->get_rating();
        
            if (leftRating > rightRating)
                return true;
        
            else if (leftRating < rightRating)
                return false;
            
            else return left.movie_id > right.movie_id;
        };
    }
};

#endif // RECOMMENDER_INCLUDED

