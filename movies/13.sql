
Select name from people
where id IN
(
Select person_id from stars
where movie_id IN
(
Select movie_id from stars
where person_id =
(
Select id FROM people
where name  = 'Kevin Bacon' AND birth = 1958
)
)
)And name!= 'Kevin Bacon' order by name;
