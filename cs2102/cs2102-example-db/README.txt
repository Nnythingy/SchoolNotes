
The ZIP archive cs2102-example-db.zip contains 5 files

* This README.txt file

* cs2102-db-schema.png (ER diagram)

* cs2102-db-schema.txt (DDL table defintions)

* cs2102.sql (PostgresSQL dump of the example db)

* lecture-5-and-6-queries.txt (all queries used on the slides for Lecture 5 & 6)






Import Database Dump
====================

Step 1: Create a new database

Log into PostgreSQL (e.g., with psql) and create a new database, e.g.

CREATE DATABASE my_cs2102_db;  -- Feel free to pick your own name



Step 2: Import dump into the newly create database, e.g.:

psql -d my_cs2102_db -f cs2102.sql  -- you might need to add the full path where cs2102.sql is located



Testing the Data Import
=======================

These two steps should be all that's need to load the data. Now can connect to the database to execute the example queries. In case you use psql, connecting to a database can simply be done with:

\c my_cs2102_db

For a quick test, try getting the number of all countries by executing the simply query

SELECT COUNT(*) FROM countries;

which should return 225 as result


