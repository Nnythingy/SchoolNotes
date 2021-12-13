/* Good practice to drop everything used first to have a clean slate */
DROP TABLE IF EXISTS pizzas, customers, restaurants, contains, likes, sells CASCADE;


/* Relational schema, create all tables */
CREATE TABLE pizzas (
  pizza  TEXT PRIMARY KEY
);

CREATE TABLE customers (
  cname  TEXT PRIMARY KEY,
  area   TEXT NOT NULL
);

CREATE TABLE restaurants (
  rname  TEXT PRIMARY KEY,
  area   TEXT NOT NULL
);

CREATE TABLE contains (
  pizza       TEXT REFERENCES pizzas(pizza), /* Good practice, but can simply be REFERENCES pizzas and SQL can infer automatically */
  ingredient  TEXT,
  PRIMARY KEY (pizza, ingredient)
);

CREATE TABLE likes (
  cname  TEXT REFERENCES customers(cname),
  pizza  TEXT REFERENCES pizzas(pizza),
  PRIMARY KEY (cname, pizza)
);

CREATE TABLE sells (
  rname  TEXT REFERENCES restaurants(rname),
  pizza  TEXT REFERENCES pizzas(pizza),
  price  NUMERIC NOT NULL CHECK (price > 0), /* From the insert below, can be INT, but better to be safe */
  PRIMARY KEY (rname, pizza)
);


/* Insert all values needed */
INSERT INTO pizzas VALUES ('Diavola');
INSERT INTO pizzas VALUES ('Funghi');
INSERT INTO pizzas VALUES ('Hawaiian');
INSERT INTO pizzas VALUES ('Margherita');
INSERT INTO pizzas VALUES ('Marinara');
INSERT INTO pizzas VALUES ('Siciliana');

INSERT INTO customers VALUES ('Homer','West');
INSERT INTO customers VALUES ('Lisa','South');
INSERT INTO customers VALUES ('Maggie','East');
INSERT INTO customers VALUES ('Moe','Central');
INSERT INTO customers VALUES ('Ralph','Central');
INSERT INTO customers VALUES ('Willie','North');

INSERT INTO restaurants VALUES ('Corleone Corner','North');
INSERT INTO restaurants VALUES ('Gambino Oven','Central');
INSERT INTO restaurants VALUES ('Lorenzo Tavern','Central');
INSERT INTO restaurants VALUES ('Mamma''s Place','South'); /* Weird thing about SQL, that's how you can add single quote in a string */
INSERT INTO restaurants VALUES ('Pizza King','East');

INSERT INTO contains VALUES ('Diavola','Cheese');
INSERT INTO contains VALUES ('Diavola','Chilli');
INSERT INTO contains VALUES ('Diavola','Salami');
INSERT INTO contains VALUES ('Funghi','Ham');
INSERT INTO contains VALUES ('Funghi','Mushroom');
INSERT INTO contains VALUES ('Hawaiian','Ham');
INSERT INTO contains VALUES ('Hawaiian','Pineapple');
INSERT INTO contains VALUES ('Margherita','Cheese');
INSERT INTO contains VALUES ('Margherita','Tomato');
INSERT INTO contains VALUES ('Marinara','Seafood');
INSERT INTO contains VALUES ('Siciliana','Anchovies');
INSERT INTO contains VALUES ('Siciliana','Capers');
INSERT INTO contains VALUES ('Siciliana','Cheese');

INSERT INTO likes VALUES ('Homer','Hawaiian');
INSERT INTO likes VALUES ('Homer','Margherita');
INSERT INTO likes VALUES ('Lisa','Funghi');
INSERT INTO likes VALUES ('Maggie','Funghi');
INSERT INTO likes VALUES ('Moe','Funghi');
INSERT INTO likes VALUES ('Moe','Siciliana');
INSERT INTO likes VALUES ('Ralph','Diavola');

INSERT INTO sells VALUES ('Corleone Corner','Diavola',24);
INSERT INTO sells VALUES ('Corleone Corner','Hawaiian',25);
INSERT INTO sells VALUES ('Corleone Corner','Margherita',19);
INSERT INTO sells VALUES ('Gambino Oven','Siciliana',16);
INSERT INTO sells VALUES ('Lorenzo Tavern','Funghi',23);
INSERT INTO sells VALUES ('Mamma''s Place','Marinara',22);
INSERT INTO sells VALUES ('Pizza King','Diavola',17);
INSERT INTO sells VALUES ('Pizza King','Hawaiian',21);
