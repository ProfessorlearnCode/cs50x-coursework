SELECT AVG(energy) AS average FROM songs where artist_id = (SELECT id from artists where name = 'Drake');
