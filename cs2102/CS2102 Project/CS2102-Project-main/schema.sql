DROP TABLE IF EXISTS Employees, HealthDeclarations, Departments, MeetingRooms, Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;

CREATE TABLE Departments (
    did INTEGER,
    dname TEXT UNIQUE NOT NULL,
    PRIMARY KEY (did)
);

CREATE TABLE Employees (
    eid SERIAL,
    ename TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL,
    resigned_date DATE,
    /* We do not need to query the contact numbers of employees, 
    so we can convert into single-valued attribute (refer to Lecture 4 Slide 34)*/
    contact TEXT NOT NULL, 
    did INTEGER NOT NULL,
    role TEXT,
    PRIMARY KEY (eid),
    FOREIGN KEY (did) REFERENCES Departments (did),
    CONSTRAINT valid_role CHECK (role = 'Manager' OR role = 'Senior' OR role = 'Junior')
);

CREATE TABLE HealthDeclarations (
    date DATE,
    eid INTEGER,
    temp FLOAT,
    fever BOOLEAN NOT NULL,
    PRIMARY KEY (date, eid),
    FOREIGN KEY (eid) REFERENCES Employees (eid) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT valid_temp CHECK (temp >= 34 AND temp <= 43)
);


CREATE TABLE MeetingRooms (
    rname TEXT NOT NULL,
    room INTEGER,
    floor INTEGER,
    did INTEGER NOT NULL,
    PRIMARY KEY (room, floor),
    FOREIGN KEY (did) REFERENCES Departments (did) 
);

CREATE TABLE Junior (
    eid INTEGER,
    PRIMARY KEY (eid),
    FOREIGN KEY (eid) REFERENCES Employees (eid) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Booker (
    eid INTEGER,
    PRIMARY KEY (eid),
    FOREIGN KEY (eid) REFERENCES Employees (eid) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Senior (
    eid INTEGER,
    PRIMARY KEY (eid),
    FOREIGN KEY (eid) REFERENCES Booker (eid) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Manager (
    eid INTEGER,
    PRIMARY KEY (eid),
    FOREIGN KEY (eid) REFERENCES Booker (eid) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Updates (
    date DATE,
    new_cap INTEGER NOT NULL,
    room INTEGER,
    floor INTEGER,
    editor_id INTEGER,
    PRIMARY KEY (date, room, floor),
    UNIQUE (room,floor),
    FOREIGN KEY (room, floor) REFERENCES MeetingRooms (room, floor),
    FOREIGN KEY (editor_id) REFERENCES Manager (eid)
);

CREATE TABLE Sessions (
    time TIME,
    date DATE,
    room INTEGER,
    floor INTEGER,
    booker_id INTEGER NOT NULL,
    approver_id INTEGER,
    PRIMARY KEY (time, date, room, floor),
    FOREIGN KEY (room, floor) REFERENCES MeetingRooms (room, floor),
    FOREIGN KEY (booker_id) REFERENCES Booker (eid),
    FOREIGN KEY (approver_id) REFERENCES Manager (eid)
);

CREATE TABLE Joins (
    eid INTEGER,
    time TIME,
    date DATE,
    room INTEGER,
    floor INTEGER,
    PRIMARY KEY (time, date, room, floor, eid),
    FOREIGN KEY (time, date, room, floor) REFERENCES Sessions (time, date, room, floor) ON DELETE CASCADE,
    FOREIGN KEY (eid) REFERENCES Employees (eid)
);

-- Ensures that Employees.eid starts with 1
ALTER SEQUENCE Employees_eid_seq RESTART;