SELECT AVG(energy) AS "Drake's Energy" FROM songs WHERE artist_id =
(SELECT id FROM artists WHERE name == 'Drake');
