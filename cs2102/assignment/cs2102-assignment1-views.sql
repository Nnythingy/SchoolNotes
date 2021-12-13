------------------------------------------------------------------------
------------------------------------------------------------------------
--
-- CS2102 - ASSIGNMENT 1 (SQL)
--
------------------------------------------------------------------------
------------------------------------------------------------------------



DROP VIEW IF EXISTS student, v1, v2, v3, v4, v6, v7, v8, v9, v10;



------------------------------------------------------------------------
-- Replace the dummy values without Student ID & NUSNET ID
------------------------------------------------------------------------

DROP VIEW student;
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

;





------------------------------------------------------------------------
-- Query Q6
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v6 (country_name1, country_name2) AS

;




------------------------------------------------------------------------
-- Query Q7
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v7 (country_name) AS

;





------------------------------------------------------------------------
-- Query Q8
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v8 (city_name) AS

;





------------------------------------------------------------------------
-- Query Q9
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v9 (country_name, crossing_count) AS

;






------------------------------------------------------------------------
-- Query Q10
------------------------------------------------------------------------

CREATE OR REPLACE VIEW v10 (airport_name) AS

;


