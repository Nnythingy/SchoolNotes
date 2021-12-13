------------------------------------------------------------------------
------------------------------------------------------------------------
--
-- CS2102 - ASSIGNMENT 1 (SQL)
--
------------------------------------------------------------------------
------------------------------------------------------------------------

DROP VIEW IF EXISTS student, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;



------------------------------------------------------------------------
-- Replace the dummy values without Student ID & NUSNET ID
------------------------------------------------------------------------

CREATE OR REPLACE VIEW student(student_id, nusnet_id) AS
 SELECT 'A0216695U', 'e0540252'
;






------------------------------------------------------------------------
-- Query Q1
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v1 (city_name) AS
SELECT name AS city_name
FROM cities
WHERE capital = 'primary'
AND population > 10000000
;





------------------------------------------------------------------------
-- Query Q2
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v2 (country_name, capital_count) AS
SELECT co.name AS country_name, COUNT(*) AS capital_count
FROM countries co JOIN cities c
ON co.iso2 = c.country_iso2
GROUP BY co.iso2, c.capital
HAVING c.capital = 'primary'
AND COUNT(co.name) > 1
;





------------------------------------------------------------------------
-- Query Q3
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v3 (country_name) AS
SELECT name AS country_name
FROM countries
WHERE countries.continent = 'Europe'
AND countries.gdp / countries.population > (SELECT gdp / population
    FROM countries
    WHERE countries.iso2 = 'SG')
;





------------------------------------------------------------------------
-- Query Q4
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v4 (country_name) AS
SELECT t.name AS country_name
FROM (SELECT countries.iso2, countries.name
    FROM countries,
        (SELECT country_iso2, COUNT(*) AS count
        FROM cities
        GROUP BY country_iso2, capital)t1
    WHERE countries.iso2 = t1.country_iso2
    GROUP BY countries.iso2
    HAVING COUNT(*) = 1)t JOIN cities
ON t.iso2 = cities.country_iso2
WHERE cities.capital = 'primary'
;





------------------------------------------------------------------------
-- Query 5
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v5 (country_name, domestic_connections_count) AS
SELECT name AS country_name, domestic_connections_count
FROM countries JOIN (SELECT fromISO, COUNT(*) AS domestic_connections_count
FROM (SELECT a1.country_iso2 AS fromISO, connections.from_code,
        connections.to_code, a2.country_iso2 AS toISO
    FROM airports a1 JOIN connections 
    ON a1.code = connections.from_code
    JOIN airports a2
    ON a2.code = connections.to_code
    WHERE a1.country_iso2 = a2.country_iso2)t
GROUP BY fromISO
HAVING COUNT(*) > 100
)a
ON iso2 = a.fromISO
ORDER BY domestic_connections_count DESC
;





------------------------------------------------------------------------
-- Query Q6
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v6 (country_name1, country_name2) AS
SELECT DISTINCT (CASE 
        WHEN c1.population > c2.population
        THEN c2.name
        ELSE c1.name
        END
    ) country_name1, 
    (CASE 
        WHEN c1.population > c2.population
        THEN c1.name
        ELSE c2.name
        END
    ) country_name2
FROM countries c1 JOIN borders
ON c1.iso2 = borders.country1_iso2
JOIN countries c2
ON borders.country2_iso2 = c2.iso2
WHERE c1.continent = c2.continent
AND c1.continent = 'Asia'
;




------------------------------------------------------------------------
-- Query Q7
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v7 (country_name) AS
SELECT name AS country_name
FROM countries c1
WHERE c1.continent = 'Asia'
EXCEPT
SELECT name
FROM (
    SELECT iso2
    FROM users u JOIN visited v
    ON u.user_id = v.user_id
    WHERE name = 'Marie'
    OR name = 'Bill'
    OR name = 'Sam'
    OR name = 'Sarah')t
JOIN countries c
ON t.iso2 = c.iso2
WHERE c.continent = 'Asia'
;





------------------------------------------------------------------------
-- Query Q8
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v8 (city_name) AS
SELECT a.city AS city_name
FROM (SELECT to_code
    from routes JOIN airports
    ON routes.to_code = airports.code JOIN countries
    ON airports.country_iso2 = countries.iso2
    WHERE routes.airline_code = 'SQ'
    AND routes.from_code = 'SIN'
    AND(countries.iso2 = 'US'
        OR countries.continent = 'Europe')
    )t
JOIN routes r
ON t.to_code = r.from_code
JOIN airports a
ON r.to_code = a.code
JOIN countries c
ON a.country_iso2 = c.iso2
WHERE c.iso2 = 'US'
AND r.airline_code = 'SQ'
;





------------------------------------------------------------------------
-- Query Q9
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v9 (country_name, crossing_count) AS
WITH RECURSIVE border_path AS (
SELECT DISTINCT country1_iso2, country2_iso2, 1 AS stops
FROM borders
WHERE country1_iso2 = 'MY'
UNION ALL
SELECT b.country1_iso2, b.country2_iso2, p.stops+1
FROM border_path p, borders b
WHERE p.country2_iso2 = b.country1_iso2
AND p.stops < 10
)
SELECT DISTINCT name AS country_name, min(stops) AS crossing_count
FROM border_path JOIN countries
ON border_path.country2_iso2 = countries.iso2
WHERE countries.continent = 'Africa'
GROUP BY name
;






------------------------------------------------------------------------
-- Query Q10
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v10 (airport_name) AS
SELECT a1.name AS airport_name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'Europe'

INTERSECT

SELECT a1.name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'Asia'

INTERSECT

SELECT a1.name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'Africa'

INTERSECT

SELECT a1.name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'North America'

INTERSECT

SELECT a1.name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'South America'

INTERSECT

SELECT a1.name
FROM countries count1 JOIN airports a1
ON count1.iso2 = a1.country_iso2
JOIN connections c
ON a1.code = c.from_code
JOIN airports a2
ON c.to_code = a2.code
JOIN countries count2
ON a2.country_iso2 = count2.iso2
WHERE count2.continent = 'Oceania'
;


