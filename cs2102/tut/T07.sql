CREATE TABLE Offices (
  oid      INTEGER,
  address  VARCHAR(60),
  PRIMARY  KEY (oid)
);

-- eid = eid of department 's manager
CREATE TABLE Departments (
  did      INTEGER,
  dbudget  INTEGER NOT NULL,
  oid      INTEGER NOT NULL,
  eid      INTEGER NOT NULL,
  PRIMARY  KEY (did),
  FOREIGN  KEY (oid) REFERENCES Offices
);

CREATE TABLE Employees (
  eid INTEGER,
  did INTEGER NOT NULL,
  PRIMARY KEY (eid),
  FOREIGN KEY (did) REFERENCES Departments
);

CREATE TABLE Engineers (
  eid INTEGER,
  PRIMARY KEY (eid),
  FOREIGN KEY (eid) REFERENCES Employees
);

CREATE TABLE Managers (
  eid INTEGER,
  PRIMARY KEY (eid),
  FOREIGN KEY (eid) REFERENCES Employees
);

-- eid = eid of project's supervisor
CREATE TABLE Projects (
  pid      INTEGER,
  pbudget  INTEGER NOT NULL,
  eid      INTEGER NOT NULL,
  PRIMARY KEY (pid),
  FOREIGN KEY (eid) REFERENCES Managers
);

CREATE TABLE WorkType (
  wid        INTEGER,
  max_hours  INTEGER NOT NULL,
  PRIMARY KEY (wid)
);

CREATE TABLE Works (
  pid    INTEGER,
  eid    INTEGER,
  wid    INTEGER,
  hours  INTEGER NOT NULL,
  PRIMARY KEY (pid,eid),
  FOREIGN KEY (eid) REFERENCES Engineers,
  FOREIGN KEY (pid) REFERENCES Projects,
  FOREIGN KEY (wid) REFERENCES WorkType
  ON DELETE CASCADE
);