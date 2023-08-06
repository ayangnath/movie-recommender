#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>


#include <iostream>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{}

MovieDatabase::~MovieDatabase()
{
    for (int i = 0; i <vector_movies.size();i++)
    {
        delete vector_movies[i];
    }
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open the file!" << endl;
        return false;
    }
    
    string line;
    string id;
    string name;
    string releaseYear;
    string lineOfDirectors;
    string lineOfActors;
    string lineOfGenres;
    float rating;
    
    while (getline(infile, line))
    {
        if (line == "")
            continue;
        
        id = line; //gets the id, which is at the top of the line
        getline(infile, name); //reading the movie name
        getline(infile, releaseYear); //reading the release year

        
        vector<string> directors; //reading the line directors;
        getline(infile, lineOfDirectors);
        //loop through the string, adding each director to the vector
        unsigned long start = 0;
        unsigned long end = 0;
        while (end < lineOfDirectors.length())
        {
            end = lineOfDirectors.find(",", start);
            if (end ==-1)
                end = lineOfDirectors.length();
            
            directors.push_back(lineOfDirectors.substr(start, end-start));
            //cout << lineOfDirectors.substr(start, end-start);
            start = end+1;
        }
        
        
        vector<string> actors;//read line of actors
        getline(infile, lineOfActors);
        start = 0;
        end = 0;
        while (end < lineOfActors.length())
        {
            end = lineOfActors.find(",", start);
            if (end ==-1)
                end = lineOfActors.length();
            
            actors.push_back(lineOfActors.substr(start, end-start));
            start = end+1;
        }
        
        vector<string> genres;//read line of genres
        getline(infile, lineOfGenres);
        start = 0;
        end = 0;
        while (end < lineOfGenres.length())
        {
            end = lineOfGenres.find(",", start);
            if (end ==-1)
                end = lineOfGenres.length();
            
            genres.push_back(lineOfGenres.substr(start, end-start));
            start = end+1;
        }
        
        infile >> rating; //reads the rating;
        infile.ignore(10000, '\n');
        
        
        Movie *movie = new Movie(id, name, releaseYear, directors, actors, genres, rating);
        vector_movies.push_back(movie);
        
        string upperID; //this and the for loop below makes the ID not case sensitive
        for (int i = 0; i < id.size(); i++)
        {
            upperID+=toupper(id.at(i));
        }
        m_id.insert(upperID, movie);
        
        for (int i = 0; i < directors.size(); i++) //loop through each director and insert to the tree
        {
            string upperDirector;
            for (int j = 0; j < directors.at(i).size(); j++)
                upperDirector+=toupper(directors.at(i).at(j)); //makes it so directors are not case sensitive
            m_directors.insert(upperDirector, movie);
        }
        
        for (int i = 0; i < actors.size(); i++) //loop throigh actors to insert into the tree
        {
            string upperActor;
            for (int j = 0; j < actors.at(i).size(); j++)
                upperActor+=toupper(actors.at(i).at(j)); //makes it so actors are not case sensitive
            m_actors.insert(upperActor, movie);
        }
        
        for (int i = 0; i < genres.size(); i++) //loops through genres to insert into the tree
        {
            string upperGenre;
            for (int j = 0; j < genres.at(i).size(); j++)
                upperGenre+=toupper(genres.at(i).at(j)); //makes it so genres are not case sensitive
            m_genres.insert(upperGenre, movie);
        }
        
        if(!getline(infile, line))
            break;
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string upperID;
    for (int i = 0; i < id.size(); i++)
    {
        upperID+=toupper(id.at(i));
    }
    
    if (!m_id.find(upperID).is_valid())
        return nullptr;
    
   else return m_id.find(upperID).get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> result;
    
    string upperDirector;
    for (int i = 0; i < director.size(); i++)
        upperDirector+=toupper(director.at(i)); //to make parameter not case sensitive
    
    TreeMultimap<string, Movie*>::Iterator it = m_directors.find(upperDirector);
    while (it.is_valid())
    {
        result.push_back(it.get_value());
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> result;
    
    string upperActor;
    for (int i = 0; i < actor.size(); i++)
        upperActor+=toupper(actor.at(i)); //to make parameter not case sensitive
    
    TreeMultimap<string, Movie*>::Iterator it;
    for (it = m_actors.find(upperActor); it.is_valid(); it.advance())
    {
        result.push_back(it.get_value());
    }

    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> result;
    
    string upperGenre;
    for (int i = 0; i < genre.size(); i++)
        upperGenre+=toupper(genre.at(i)); //to make parameter not case sensitive
    
    TreeMultimap<string, Movie*>::Iterator it;
    for (it = m_genres.find(upperGenre); it.is_valid(); it.advance())
    {
        result.push_back(it.get_value());
    }

    return result;
}

