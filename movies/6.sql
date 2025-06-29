SELECT AVG(rating) as rating from ratings join movies
ON movies.id = ratings.movie_id
WHERE movies.year = 2012;
