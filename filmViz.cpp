#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
// #include <windows.h>
#include <stdlib.h>   
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>

using namespace std;

class Movie
{

private:
    double originalRating, remakeRating;
    string originalID, remakeID, title;
    bool gotRemakeRating, gotOriginalRating;

public:
    Movie(string movieTitle, string originalTconst, string remakeTconst)
    {
        this->title = movieTitle;
        this->originalID = originalTconst;
        this->remakeID = remakeTconst;

        // cout << originalRating << endl;
        //   cout << "try" << endl;
    }

    void printName()
    {
        cout << title << endl;
    }

    bool thisMovie(string tconst)
    {
        if (tconst == originalID)
        {
            return true;
        }
        else if (tconst == remakeID)
        {
            return true;
        }

        return false;
    }

    void setRating(string id, double rating)
    {
        if (id == originalID)
        {
            this->originalRating = rating;
            // cout << this->originalRating << endl;
            this->gotOriginalRating = true;
        }
        else if (id == remakeID)
        {
            this->remakeRating = rating;
            // cout << remakeRating << endl;
            this->gotRemakeRating = true;
        }
        else
        {
            cout << "invalid id provided for movie" << endl;
        }

        // cout << this->originalRating << endl;
    }

    bool gotRatings()
    {
        if (gotRemakeRating && gotOriginalRating)
        {
            return true;
        }
        return false;
    }

    void compareRatings()
    {
        cout << "============================================================================================================= " << endl;
        
        if (originalRating > remakeRating)
        {
            cout << title << endl;
            sleep(1.5);
            
            cout << "Original: " << originalRating << " "
                 << "Remake: " << this->remakeRating << endl;
            sleep(3);
            cout << "The original was better" << endl;
            cout << endl;
            sleep(2);
        }
        else if (originalRating < remakeRating)
        {
            cout << title << endl;
             sleep(1.5);
            cout << "Original: " << originalRating << " "
                 << "Remake: " << remakeRating << endl;
                  sleep(3);
            cout << "The remake was better" << endl;
            cout << endl;
            sleep(2);
        }
        else
        {
            cout << title  << endl;
            sleep(1.5);
            cout << "Original: " << originalRating << " "
                 << "Remake: " << remakeRating << endl;
            sleep(3);     
            cout << "They were the same but still" << endl;
            cout << endl;
            sleep(2);
        }
    }
};

int main()
{
    string line, word;

    vector<Movie> movies;

    fstream file("titleData.csv", ios::in);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            // cout << line << endl;

            vector<string> temp;
            stringstream str(line);

            while (getline(str, word, ','))
            {
                temp.push_back(word);
                // cout << word << endl;
            }
            // cout << temp[0] << endl;
            Movie tempMovie(temp[0], temp[1], temp[2]);
            movies.push_back(tempMovie);
        }
    }
    else
    {
        cout << "Could not open the file\n";
    }

    // for (Movie currentMovie : movies)
    // {
    //     currentMovie.printName();
    // }

    fstream file2("data.tsv", ios::in);

    if (file2.is_open())
    {
        while (getline(file2, line))
        {
            // cout << line << endl;

            vector<string> temp;
            stringstream str(line);

            while (getline(str, word, '\t'))
            {
                temp.push_back(word);
                // cout << word << endl;
            }

            for (Movie &currentMovie : movies)
            {
                if (currentMovie.thisMovie(temp[0]))
                {

                    int n = temp[1].length();

                    // declaring character array
                    char char_array[n + 1];

                    // copying the contents of the
                    // string to char array
                    strcpy(char_array, temp[1].c_str());

                    // char s[] = temp[1];
                    double rating = stod(char_array);
                    currentMovie.setRating(temp[0], rating);
                    if (currentMovie.gotRatings())
                    {
                        currentMovie.compareRatings();
                    }
                }
            }
        }
    }
    else
    {
        cout << "Could not open the file\n";
    }

    // for (Movie currentMovie : movies)
    // {
    //     currentMovie.compareRatings();
    // }
}
