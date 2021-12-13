------------------------------------------------------------------------
-- Function for add_department
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE add_department
    (IN did INT, IN dname TEXT)
AS $$
    INSERT INTO Departments VALUES (did, dname);
$$ LANGUAGE sql;

--TESTCASES--
--CALL add_department(1, 'Finance'); 

------------------------------------------------------------------------
-- Function for remove_department
------------------------------------------------------------------------
 CREATE OR REPLACE PROCEDURE remove_department
    (IN target_did INT)
AS $$
    DELETE FROM Departments WHERE did = target_did;
$$ LANGUAGE sql;

--TESTCASES--
--CALL remove_department(1); 
 
------------------------------------------------------------------------
-- Function for add_employee
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE add_employee
    (IN ename TEXT, IN contact TEXT, IN kind TEXT, IN dept TEXT)
AS $$
DECLARE
curr_did INT;
new_eid INT;
new_email TEXT;

BEGIN
    SELECT did INTO curr_did FROM Departments WHERE dname = dept;

    -- Check if user input (kind) is valid 
    IF kind <> 'Manager' AND kind <> 'Senior' AND kind <> 'Junior'
    THEN RAISE NOTICE 'Invalid input (kind)';

    -- Check if user input (dept) is valid 
    ELSIF curr_did IS NULL
    THEN RAISE NOTICE 'Invalid input (dept)';

    -- Check if user input (contact) is valid 
    ELSIF contact IS NULL
    THEN RAISE NOTICE 'Invalid input (contact)';

    -- Check if user input (name) is valid 
    ELSIF ename IS NULL
    THEN RAISE NOTICE 'Invalid input (name)';

    ELSE
        -- Employees(eid, ename, email, resigned_date, contact, did)
        INSERT INTO Employees VALUES (DEFAULT, ename, 'placeholder', NULL, contact, curr_did, kind);
        
        SELECT currval(pg_get_serial_sequence('Employees', 'eid')) INTO new_eid;
        
        --TODO: Might want to extract only the initials instead of the entire name
        -- as name might be too long in rare cases
        new_email := ename || new_eid || '@company.org';

        --Replace placeholder email with auto-generated email
        UPDATE Employees SET email = new_email WHERE eid = new_eid;

    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION insert_into_roles_1()
RETURNS TRIGGER AS $$
BEGIN
    --Assign eid to specific roles
    IF NEW.role = 'Junior' THEN 
        INSERT INTO Junior VALUES (NEW.eid);
    ELSIF NEW.role = 'Senior' THEN 
        INSERT INTO Booker VALUES (NEW.eid);
    ELSIF NEW.role = 'Manager' THEN 
        INSERT INTO Booker VALUES (NEW.eid);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION insert_into_roles_2()
RETURNS TRIGGER AS $$
DECLARE
curr_role TEXT;
BEGIN
    SELECT role INTO curr_role FROM Employees WHERE eid = NEW.eid;
    --Assign eid to specific roles
    IF curr_role = 'Senior' THEN 
        INSERT INTO Senior VALUES (NEW.eid);
    ELSIF curr_role = 'Manager' THEN 
        INSERT INTO Manager VALUES (NEW.eid);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS insert_into_roles_1 ON Employees;
CREATE TRIGGER insert_into_roles_1
AFTER INSERT ON Employees
FOR EACH ROW EXECUTE FUNCTION insert_into_roles_1();

DROP TRIGGER IF EXISTS insert_into_roles_2 ON Booker;
CREATE TRIGGER insert_into_roles_2
AFTER INSERT ON Booker
FOR EACH ROW EXECUTE FUNCTION insert_into_roles_2();

--TESTCASES--
/*
CALL add_department(1, 'Finance'); --Creates Dept
CALL add_employee('Alice', NULL, 'Manager', 'Finance'); -- Violate FK for contact
CALL add_employee('Alice', '98765432', 'xyz', 'Finance'); -- Exception: invalid kind
CALL add_employee('Alice', '98765432', 'Manager', 'xyz'); -- Exception: invalid dept
CALL add_employee('Alice', '98765432', 'Junior', 'Finance');
CALL add_employee('Bob', '12345678', 'Senior', 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance');
SELECT * FROM employees;

Results:
Alice, Bob, Eve in Employees
Alice in Junior
Bob in Booker and Senior
Eve in Booker and Manager
*/

------------------------------------------------------------------------
-- Function for add_room
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE add_room
    (IN rname TEXT, IN room INT, IN floor INT, IN did INT)
AS $$
    INSERT INTO MeetingRooms VALUES (rname, room, floor, did);
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION insert_into_updates()
RETURNS TRIGGER AS $$
DECLARE
date DATE;
BEGIN
    -- We use current date here since we cant pass parameters into trigger
    SELECT CURRENT_DATE INTO date;
    INSERT INTO Updates VALUES (date, 0, NEW.room, NEW.floor, NULL);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS insert_into_updates ON MeetingRooms;
CREATE TRIGGER insert_into_updates
AFTER INSERT ON MeetingRooms
FOR EACH ROW EXECUTE FUNCTION insert_into_updates();

/*
Limitations:
1) Initial capacity is set to 0 (Must be updated to be usable)
*/

--TESTCASES--
--CALL add_department(1, 'Finance');
--CALL add_room('Meeting Room A', 6, 3, 1); 

------------------------------------------------------------------------
-- Function for change_capacity
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE change_capacity
    (IN in_floor INT, IN in_room INT, IN in_cap INT, IN in_date DATE, IN in_id INT)
AS $$
    UPDATE Updates
    SET new_cap = in_cap, date = in_date, editor_id = in_id
    WHERE floor = in_floor AND room = in_room;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION check_meeting()
RETURNS TRIGGER AS $$
DECLARE
curr_date DATE;

BEGIN
    -- We use current date here since we cant pass parameters into trigger
    SELECT CURRENT_DATE INTO curr_date;

    DELETE
    FROM Sessions S
    WHERE (time,date,room,floor) IN (SELECT time, date, room, floor
                                     FROM Joins J
                                     WHERE J.room = NEW.room
                                     AND J.floor = NEW.floor
                                     AND date > curr_date
                                     GROUP BY (time, date, room, floor) 
                                     HAVING COUNT(*) > NEW.new_cap);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS check_meeting ON Updates;
CREATE TRIGGER check_meeting
AFTER UPDATE ON Updates
FOR EACH ROW EXECUTE FUNCTION check_meeting();

/*
Limitations:
1) Change history is not recorded (not in specification anyways)
*/

--TESTCASES-- (To be executed block-by-block)

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE; 
*/

/* ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_room('Meeting Room A', 5, 3, 1);
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Manager', 'Finance'); --eid 3
CALL change_capacity(3, 5, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', '2022-03-14', 5, 3, 1, 2);
INSERT INTO Sessions VALUES ('08:00:00', '2021-03-14', 5, 3, 1, 2);
INSERT INTO Joins VALUES (1, '08:00:00', '2022-03-14', 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', '2022-03-14', 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', '2021-03-14', 5, 3);
SELECT * FROM Joins; --eid 1, 2, 3 present */

/* CALL change_capacity(3, 5, 0, CURRENT_DATE, 1); -- Change capacity to 0 
SELECT * FROM Joins; --eid 1 and 2 deleted (only future sessions affected) */

------------------------------------------------------------------------
-- Function for remove_employee
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE remove_employee
    (IN target_eid INT, IN last_day DATE)
AS $$
    UPDATE Employees
    SET resigned_date = last_day
    WHERE eid = target_eid;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION remove_employee_from_future_meetings()
RETURNS TRIGGER AS $$
DECLARE
curr_date DATE;

BEGIN
    -- We use current date here since we cant pass parameters into trigger
    SELECT resigned_date INTO curr_date FROM Employees WHERE eid = NEW.eid;

    DELETE
    FROM Joins j
    WHERE eid = NEW.eid AND date > curr_date;

    RETURN NEW;
    
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS remove_employee_from_future_meetings ON Employees;
CREATE TRIGGER remove_employee_from_future_meetings
AFTER UPDATE ON Employees
FOR EACH ROW EXECUTE FUNCTION remove_employee_from_future_meetings();

CREATE OR REPLACE FUNCTION prevent_deletion()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Cannot delete Employees (Use remove_employee function instead)';
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS prevent_deletion ON Employees;
CREATE TRIGGER prevent_deletion
BEFORE DELETE ON Employees
FOR EACH ROW EXECUTE FUNCTION prevent_deletion();
--TESTCASES--

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;  */


-- Test removal of employee from Employees
/* ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2
CALL remove_employee(1, '2021-03-15'); --remove Eve from Employees
SELECT * FROM Employees; --eid 1 should have resign_date */

-- Test removal of future meetings from Joins

/* CALL add_room('Meeting Room A', 5, 3, 1);
CALL add_employee('Jack', '00000000', 'Manager', 'Finance'); --eid 3
CALL change_capacity(3, 5, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', '2022-03-14', 5, 3, 1, 2);
INSERT INTO Sessions VALUES ('08:00:00', '2021-03-14', 5, 3, 1, 2);
INSERT INTO Joins VALUES (3, '08:00:00', '2021-03-14', 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', '2022-03-14', 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', '2022-03-14', 5, 3);
CALL remove_employee(3, '2021-03-15'); --remove Jack from Employees 
SELECT * FROM Joins; --should not have future record of eid 3 */

-- Test accidental deletion of Employees
/* CALL add_employee('New', '00000000', 'Manager', 'Finance'); --eid 4
SELECT * FROM employees; --eid 4 present */

/* DELETE FROM Employees WHERE eid = 4;
SELECT * FROM employees; --eid 4 still present*/

------------------------------------------------------------------------
-- Function for search_room
------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION search_room
    (IN search_capacity INT, IN search_date DATE, IN start_hour TIME, IN end_hour TIME)
RETURNS TABLE (floor INT, room INT, did INT, capacity INT) AS $$
BEGIN
    RETURN QUERY SELECT DISTINCT rooms.floor, rooms.room, rooms.did, rooms.new_cap
    FROM (MeetingRooms NATURAL JOIN Updates) rooms
    WHERE rooms.new_cap >= search_capacity
    AND NOT EXISTS (SELECT 1 FROM Sessions s
        WHERE s.room = rooms.room AND s.floor = rooms.floor
        AND s.date = search_date AND s.time >= start_hour
        AND s.time < end_hour)
    ORDER BY rooms.new_cap ASC;
END;
$$ LANGUAGE plpgsql;

--TESTCASES--
/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;  */

/* Set up 3 meeting rooms with sample booked sessions
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1
CALL add_room('Meeting Room A', 5, 3, 1);
CALL change_capacity(3, 5, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', '2021-03-14', 5, 3, 1, 1);
INSERT INTO Sessions VALUES ('09:00:00', '2021-03-14', 5, 3, 1, 1);
CALL add_room('Meeting Room B', 7, 2, 1);
CALL change_capacity(2, 7, 20, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', '2021-03-14', 7, 2, 1, 1);
CALL add_room('Meeting Room C', 5, 5, 1);
CALL change_capacity(5, 5, 50, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', '2021-03-14', 5, 5, 1, 1); */

/* Search room on available date -> all rooms should be available
SELECT * FROM search_room(10, '2021-03-15', '08:00:00', '09:00:00'); */

/* Search room with available timing -> all rooms should be available
SELECT * FROM search_room(10, '2021-03-14', '12:00:00', '20:00:00'); */

/* Search room on from 8 to 10 -> no rooms should be available
SELECT * FROM search_room(10, '2021-03-14', '08:00:00', '10:00:00'); */

/* Search room on from 9 to 10 -> Room B and C should be available
SELECT * FROM search_room(10, '2021-03-14', '09:00:00', '10:00:00'); */

/* Search room on from 9 to 10 with min capacity = 40 -> only room C should be available
SELECT * FROM search_room(40, '2021-03-14', '09:00:00', '10:00:00'); */

------------------------------------------------------------------------
-- Function for declare_health
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE declare_health
    (IN eid INT, IN date DATE, IN temp FLOAT)
AS $$
DECLARE
fever BOOLEAN;
BEGIN
    fever := temp > 37.5;
    INSERT INTO HealthDeclarations VALUES (date, eid, temp, fever);
END;
$$ LANGUAGE plpgsql;

--TESTCASES--
/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;  */

/* --Setting up 2 Employees in database
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2 */

/* CALL declare_health(1, CURRENT_DATE, 40.2); --Case 1: Fever
CALL declare_health(2, CURRENT_DATE, 36.0); --Case 2: No Fever
SELECT * FROM HealthDeclarations; */

------------------------------------------------------------------------
-- Function for contact_tracing
------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION find_close_contacts
    (IN target_eid INT)
RETURNS TABLE(out_eid INT) AS $$
BEGIN
    -- Step 3b: Find all distinct employees that are close contacts (excluding the employee)
    RETURN QUERY SELECT DISTINCT eid
    FROM Joins J,
        -- Step 3a: Find all approved meetings that the employee was part of within the past 3 days
        (SELECT S.time, S.date, S.room, S.floor
         FROM Sessions S JOIN Joins J2 
         ON S.date = J2.date 
            AND S.time = J2.time
            AND S.room = J2.room
            AND S.floor = J2.floor
         WHERE S.date >= CURRENT_DATE - 3
            AND S.date <= CURRENT_DATE
            AND J2.eid = target_eid
            AND S.approver_id IS NOT NULL) subtable
    WHERE subtable.time = J.time
        AND subtable.date = J.date
        AND subtable.room = J.room
        AND subtable.floor = J.floor 
        AND J.eid <> target_eid;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION contact_tracing
    (IN in_eid INT)
RETURNS TABLE(eid INT) AS $$
DECLARE
is_fever BOOLEAN;
BEGIN
    -- Step 1: Check if this employee is having a fever
    is_fever = (SELECT fever 
                FROM HealthDeclarations H
                WHERE date = CURRENT_DATE
                    AND H.eid = in_eid);
    -- Step 2: Perform contact tracing if having fever                    
    IF (is_fever) THEN
        -- Step 3: Find close contacts
        RETURN QUERY SELECT out_eid
        FROM find_close_contacts(in_eid);
        -- Step 4: Remove close contacts from all meetings in the next 7 days
        DELETE FROM Joins J
        WHERE J.date >= CURRENT_DATE
            AND J.date <= CURRENT_DATE + 7
            AND J.eid IN (SELECT out_eid AS eid FROM find_close_contacts(in_eid));
        -- Step 5: Delete all sessions that are booked by the employee
        DELETE FROM Sessions S
        WHERE S.booker_id = in_eid
            AND S.date >= CURRENT_DATE;
        -- Step 6: Remove employee from all future meeting room booking
        DELETE FROM Joins J2
        WHERE J2.eid = in_eid
            AND J2.date >= CURRENT_DATE;
    END IF;
END;
$$ LANGUAGE plpgsql;

--TESTCASES--
/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;  */
        
-- Set up (SET eid 1 to have fever)
-- eid 1,2 in Session 1, (booked, approved by eid 1)
-- eid 1,3 in Session 2, (booked, approved by eid 1)
-- eid 1,2,3 in Session 3, (booked, approved by eid 2)
-- eid 1,2,3 in Session 4, (booked, approved by eid 1)
-- eid 2,3 in Session 5 (booked, approved by eid 2)

/* ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Manager', 'Finance'); --eid 3
CALL add_room('Meeting Room A', 5, 3, 1);
CALL change_capacity(3, 5, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE - 4, 5, 3, 1, 1); --Session 1
INSERT INTO Joins VALUES (1, '08:00:00', CURRENT_DATE - 4, 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', CURRENT_DATE - 4, 5, 3);

INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE - 2, 5, 3, 1, 1); --Session 2
INSERT INTO Joins VALUES (1, '08:00:00', CURRENT_DATE - 2, 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', CURRENT_DATE - 2, 5, 3);

INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 5, 5, 3, 2, 2); --Session 3
INSERT INTO Joins VALUES (1, '08:00:00', CURRENT_DATE + 5, 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', CURRENT_DATE + 5, 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', CURRENT_DATE + 5, 5, 3);

INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 8, 5, 3, 1, 1); --Session 4
INSERT INTO Joins VALUES (1, '08:00:00', CURRENT_DATE + 8, 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', CURRENT_DATE + 8, 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', CURRENT_DATE + 8, 5, 3);

INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 9, 5, 3, 2, 2); --Session 5
INSERT INTO Joins VALUES (2, '08:00:00', CURRENT_DATE + 9, 5, 3);
INSERT INTO Joins VALUES (3, '08:00:00', CURRENT_DATE + 9, 5, 3);
CALL declare_health(1, CURRENT_DATE, 40.0); -- SET eid 1 to have fever
CALL declare_health(2, CURRENT_DATE, 36.0);
CALL declare_health(3, CURRENT_DATE, 36.0);
SELECT * FROM Joins; -- Should have 12 entries for now */

/* -- Returns eid 3 as close contacts (from Session 2)
SELECT * FROM contact_tracing(1);  */

/* -- Only future sessions (Session 4) booked by eid 1 are removed 
SELECT * FROM Sessions S WHERE S.booker_id = 1; */

/* -- eid 1 is removed from all future meetings (including those that are not booked by him)
SELECT * FROM Joins J WHERE J.eid = 1;  */

/* -- eid 2 is removed from Session 4 (4: meeting cancelled by eid 1)
SELECT * FROM Joins J WHERE J.eid = 2; */

/* -- eid 3 is removed from Session 3,4 (3: within 7 days of close contact, 
   --                                    4: meeting cancelled by eid 1)
 SELECT * FROM Joins J WHERE J.eid = 3;  */ 

------------------------------------------------------------------------
-- Function for non_compliance
------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION non_compliance
    (IN start_date DATE, IN end_date DATE)
RETURNS TABLE(eid INT, number_of_days BIGINT) AS $$
DECLARE
total_days INT := end_date - start_date + 1;
BEGIN
    IF (total_days <= 0) THEN
        RAISE NOTICE 'Invalid start/end date input';
    ELSE
        RETURN QUERY (SELECT sub2.eid, total_days - sub2.number_of_days
        FROM
            -- LEFT JOIN to account for employees that does not have an entry in HealthDeclarations
            -- Convert those with 'NULL' number of days to 0
            (SELECT DISTINCT E.eid, COALESCE(sub1.days, 0) AS number_of_days
            FROM Employees E
            LEFT JOIN
                -- To find eid and number of days declared in the date range 
                (SELECT H.eid, COUNT(*) AS days
                    FROM HealthDeclarations H
                    WHERE date >= start_date AND date <= end_date
                    GROUP BY H.eid) sub1
            ON E.eid = sub1.eid) sub2
        WHERE sub2.number_of_days < total_days --Exclude those that are compliant
        ORDER BY total_days - sub2.number_of_days DESC); -- Order by desc as requested in specs
    END IF;
END;
$$ LANGUAGE plpgsql;

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE; */ 

/* --Setting up 3 Employees in database
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Manager', 'Finance'); --eid 3 */

/* --Total Number of days in testcase: 4 days
--Case 1: Normal employee that declares everyday
CALL declare_health(1, CURRENT_DATE, 40.2);
CALL declare_health(1, CURRENT_DATE - 1, 40.2);
CALL declare_health(1, CURRENT_DATE - 2, 40.2);
CALL declare_health(1, CURRENT_DATE - 3, 40.2);
--Case 2: eid 2 declares only 1 day
CALL declare_health(2, CURRENT_DATE, 36.0);
--Case 3: eid 3 declares 3 days
CALL declare_health(3, CURRENT_DATE, 40.2);
CALL declare_health(3, CURRENT_DATE - 1, 40.2);
CALL declare_health(3, CURRENT_DATE - 3, 36.0);
SELECT * FROM HealthDeclarations; --Should have 8 entries in total */

/* -- Returns 3 missing days for eid 2, 1 missing day for eid 3
SELECT non_compliance(CURRENT_DATE - 3, CURRENT_DATE); */

------------------------------------------------------------------------
-- Function for view_manager_report
------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION view_manager_report
    (IN in_start_date DATE, IN in_eid INT)
RETURNS TABLE (floor INT, room INT, date DATE, start_hr TIME, eid INT)
AS $$
BEGIN
    IF (NOT EXISTS (SELECT * FROM Manager M WHERE M.eid = in_eid)) THEN
        RETURN;
    ELSE
        RETURN QUERY 
        SELECT S.floor, S.room, S.date, S.time, S.booker_id
        FROM Sessions S
        JOIN MeetingRooms M
        ON S.room = M.room AND S.floor = M.floor
        WHERE S.date >= in_start_date 
            AND S.approver_id IS NULL
            AND M.did IN (SELECT E.did FROM Employees E WHERE E.eid = in_eid)
        ORDER BY date ASC, time ASC;
    END IF;
END;
$$ LANGUAGE plpgsql;

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE; */ 

/* --Setting up 3 Employees in database
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_department(2, 'HR');
CALL add_employee('Eve', '00000000', 'Junior', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Manager', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Manager', 'HR'); --eid 3 
CALL add_room('Meeting Room A', 5, 3, 1);
CALL add_room('Meeting Room B', 6, 3, 2);
CALL change_capacity(3, 5, 30, CURRENT_DATE, 2);
CALL change_capacity(3, 6, 30, CURRENT_DATE, 3);
INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 5, 5, 3, 2, NULL); --Session 1
INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 6, 5, 3, 2, 2); --Session 2
INSERT INTO Joins VALUES (1, '08:00:00', CURRENT_DATE + 5, 5, 3);
INSERT INTO Joins VALUES (2, '08:00:00', CURRENT_DATE + 5, 5, 3);
INSERT INTO Sessions VALUES ('08:00:00', CURRENT_DATE + 5, 6, 3, 3, NULL); --Session 3
INSERT INTO Joins VALUES (3, '08:00:00', CURRENT_DATE + 5, 5, 3); */

/* --Case 1: Input eid does not correspond to a Manager's eid
SELECT view_manager_report(CURRENT_DATE, 1); --Empty Table */

/* --Case 2: eid 2 (Only output Session 1 since Session 2 is already approved)
SELECT view_manager_report(CURRENT_DATE, 2); */ 

/* --Case 3: eid 3 (Only output Session 3 since eid 3 is the same dept as this booking)
SELECT view_manager_report(CURRENT_DATE, 3); */

------------------------------------------------------------------------
-- Function for book_room
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE book_room
    (IN in_floor INT, IN in_room INT, IN in_date DATE, IN in_start TIME, IN in_end TIME, IN in_id INT)
AS $$
DECLARE 
bookTime TIME := in_start;
BEGIN

    -- Check if times given is valid
    IF (in_start >= in_end)
    THEN RAISE NOTICE 'Invalid time input (start time be before end time)';

    -- Check if inputted date and time is over
    ELSIF (in_date < CURRENT_DATE) OR (in_date = CURRENT_DATE AND in_start < CURRENT_TIME)
    THEN RAISE NOTICE 'You can only book meetings in advance';

    -- Check if room is available for the entire duration
    ELSIF EXISTS (SELECT * FROM Sessions 
        WHERE room = in_room AND floor = in_floor AND date = in_date
        AND approver_id IS NOT NULL AND time >= in_start AND time < in_end)
    THEN RAISE NOTICE 'Room is not available for the given duration';

    ELSE
        WHILE bookTime < in_end LOOP
        INSERT INTO Sessions VALUES (bookTime, in_date, in_room, in_floor, in_id, NULL);
        SELECT bookTime + INTERVAL '1 hour' INTO bookTime;
        END LOOP;

    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION insert_into_sessions()
RETURNS TRIGGER AS $$
DECLARE
hasFever BOOLEAN;
BEGIN
    SELECT fever INTO hasFever FROM HealthDeclarations WHERE eid = NEW.booker_id AND date = CURRENT_DATE;

    -- Check if user is a booker
    IF NOT EXISTS (SELECT * FROM Booker WHERE eid = NEW.booker_id)
    THEN RAISE NOTICE 'Only senior employees and managers can book rooms';
    RETURN NULL;

    -- Check if user is a current employee
    ELSIF EXISTS (SELECT * FROM Employees WHERE eid = NEW.booker_id AND resigned_date IS NOT NULL)
    THEN RAISE NOTICE 'Only current employees are allowed to book rooms';
    RETURN NULL;

    -- Check if user has declared their health
    ELSIF hasFever IS NULL
    THEN RAISE NOTICE 'Declare your temperature before you can book a room';
    RETURN NULL;

    -- Check if has a fever
    ELSIF hasFever
    THEN RAISE NOTICE 'You have a fever. You cannot book a room';
    RETURN NULL;

    -- Check if room is available for the 1 hr session
    ELSIF EXISTS (SELECT * FROM Sessions 
        WHERE room = NEW.room AND floor = NEW.floor AND date = NEW.date
        AND approver_id IS NOT NULL AND time >= NEW.time AND time < (NEW.time + INTERVAL '1 hour'))
    THEN RAISE NOTICE 'Room is not available for this session';
    RETURN NULL;

    ELSE
        RETURN NEW;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION booker_joins_sessions()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO Joins VALUES (NEW.booker_id, NEW.time, NEW.date, NEW.room, NEW.floor); -- Booker joins the meeting
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS insert_into_sessions ON Sessions;
CREATE TRIGGER insert_into_sessions
BEFORE INSERT ON Sessions
FOR EACH ROW EXECUTE FUNCTION insert_into_sessions();

DROP TRIGGER IF EXISTS booker_joins_sessions ON Sessions;
CREATE TRIGGER booker_joins_sessions
AFTER INSERT ON Sessions
FOR EACH ROW EXECUTE FUNCTION booker_joins_sessions();

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE; */ 

/* --Setting up 5 Employees in database, 2 valid , 3 invalid
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Senior', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Junior', 'Finance'); --eid 3 
CALL add_employee('Fred', '00000000', 'Senior', 'Finance'); --eid 4 
CALL add_employee('Charles', '00000000', 'Senior', 'Finance'); --eid 5
CALL declare_health(1, CURRENT_DATE, 36.5);
CALL declare_health(2, CURRENT_DATE, 36.5);
*/

/* Set up 2 meeting rooms
CALL add_room('Meeting Room A', 3, 3, 1);
CALL change_capacity(3, 3, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('09:00:00', CURRENT_DATE + 1, 3, 3, 1, 1);
CALL add_room('Meeting Room B', 5, 5, 1);
CALL change_capacity(5, 5, 20, CURRENT_DATE, 1);  */

/* --Junior employee tries to book - error
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '10:00:00', 3); */

/* --Resigned employee tries to book - error
CALL remove_employee(5, '2021-03-15');
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '10:00:00', 5); */

/* --Booker tries to book without declaring health - error
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '10:00:00', 4); */

/* --Booker tries to book with fever - error
CALL declare_health(4, CURRENT_DATE,40.2);
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '10:00:00', 4); */

/* --Booker tries to book with invalid timings - error
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '09:00:00', 2); 
CALL book_room(5, 5, CURRENT_DATE - 1, '09:00:00', '10:00:00', 2); 
CALL book_room(5, 5, CURRENT_DATE, '00:00:00', '00:00:01', 2); */

/* --Booker tries to book a room that already has an approved booking - error
CALL book_room(3, 3, CURRENT_DATE + 1, '08:00:00', '10:00:00', 2); */

/* --Booker books empty room for 1 hour - success
CALL book_room(5, 5, CURRENT_DATE + 1, '08:00:00', '09:00:00', 2);
SELECT * FROM Sessions; -- 2 rows
SELECT * FROM Joins; -- 2 row */

/* --Booker books empty room for 6 hours - success
CALL book_room(5, 5, CURRENT_DATE + 1, '09:00:00', '15:00:00', 1);
SELECT * FROM Sessions; -- 8 rows
SELECT * FROM Joins; -- 8 row */

------------------------------------------------------------------------
-- Function for approve_meeting
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE approve_meeting
    (IN in_floor INT, IN in_room INT, IN in_date DATE, IN in_start TIME, IN in_end TIME, IN in_id INT)
AS $$
DECLARE 
curr_time TIME := in_start;
BEGIN
    IF (in_end <= in_start) THEN
        RAISE NOTICE 'Invalid start/end hr';
    ELSIF (in_date < CURRENT_DATE) OR (in_date = CURRENT_DATE AND in_start < CURRENT_TIME)
        THEN RAISE NOTICE 'You can only approve meetings in advance';
    ELSE
        LOOP
            EXIT WHEN curr_time >= in_end;
            IF EXISTS (SELECT * FROM Sessions S
                        WHERE S.time = curr_time
                            AND S.room = in_room
                            AND S.floor = in_floor 
                            AND S.date = in_date) THEN
                UPDATE Sessions SET approver_id = in_id
                WHERE room = in_room
                AND floor = in_floor 
                AND date = in_date
                AND time = curr_time;
            END IF;
            curr_time = curr_time + interval '1' hour;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_update_sessions()
RETURNS TRIGGER AS $$
DECLARE
resign_status BOOLEAN;
approval_status BOOLEAN;
BEGIN
    SELECT (E.resigned_date IS NOT NULL) INTO resign_status 
    FROM Employees E
    WHERE E.eid = NEW.approver_id;

    SELECT (S.approver_id IS NOT NULL) INTO approval_status 
    FROM Sessions S
    WHERE S.room = NEW.room
        AND S.floor = NEW.floor
        AND S.date = NEW.date
        AND S.time = NEW.time;

    IF NOT EXISTS (SELECT * FROM Manager WHERE eid = NEW.approver_id)
        -- Case 1: Cannot approve if not manager
        THEN RAISE NOTICE 'Only managers can approve rooms';
        RETURN NULL;
    ELSIF NOT EXISTS(
        SELECT * FROM MeetingRooms M JOIN Employees E
        ON M.did = E.did
        WHERE E.eid = NEW.approver_id
        AND M.room = NEW.room
        AND M.floor = NEW.floor
    )
    THEN
        --Case 2: Cannot approve if different department 
        RAISE NOTICE 'Approver is not from the same department as booker';
        RETURN NULL;
    ELSIF (resign_status) THEN
        --Case 3: Cannot approve if resigned
        RAISE NOTICE 'Not allowed to approve meetings when resigned';
        RETURN NULL;
    ELSIF (approval_status) THEN
        --Case 4: Cannot approve if already approved
        RAISE NOTICE 'Not allowed to approve meetings that are already approved';
        RETURN NULL;
    ELSE 
        RETURN NEW;
    END IF;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS check_update_sessions ON Sessions;
CREATE TRIGGER check_update_sessions
BEFORE UPDATE ON Sessions
FOR EACH ROW EXECUTE FUNCTION check_update_sessions();

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE;
*/

--Setting up 5 Employees in database, 2 valid , 3 invalid
/* ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_department(2, 'Test');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Senior', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Junior', 'Finance'); --eid 3 
CALL add_employee('Fred', '00000000', 'Senior', 'Finance'); --eid 4 
CALL add_employee('Charles', '00000000', 'Senior', 'Finance'); --eid 5
CALL add_employee('Mallory', '00000000', 'Manager', 'Test'); --eid 6
CALL declare_health(1, CURRENT_DATE, 36.5);
CALL declare_health(2, CURRENT_DATE, 36.5); */


/* --Set up 2 meeting rooms
CALL add_room('Meeting Room A', 3, 3, 1);
CALL change_capacity(3, 3, 30, CURRENT_DATE, 1); 
INSERT INTO Sessions VALUES ('09:00:00', CURRENT_DATE + 1, 3, 3, 1, 1);
CALL add_room('Meeting Room B', 5, 5, 1);
CALL change_capacity(5, 5, 20, CURRENT_DATE, 1);
*/

/* --Booker books empty room for 2 hour
CALL book_room(5, 5, CURRENT_DATE + 1, '07:00:00', '08:00:00', 2);
CALL book_room(5, 5, CURRENT_DATE + 1, '08:00:00', '09:00:00', 2);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved)
SELECT * FROM Joins; -- 3 rows */

/* --Invalid start time/end time - failure
CALL approve_meeting(5, 5, CURRENT_DATE + 1, '07:00:00', '04:00:00', 1);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved) */

/* --Approver approves booking with date < CURRENT_DATE - failure
CALL approve_meeting(1, 1, CURRENT_DATE - 1, '09:00:00', '10:00:00', 1);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved) */


/* --Non manager approves existing booking - failure
CALL approve_meeting(5, 5, CURRENT_DATE + 1, '08:00:00', '09:00:00', 4);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved) */


/* --Wrong department manager approves existing booking - failure
CALL approve_meeting(5, 5, CURRENT_DATE + 1, '08:00:00', '09:00:00', 6);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved)
*/

/* --Approver not allowed to approve bookings that are already approved - failure
CALL approve_meeting(3, 3, CURRENT_DATE + 1, '09:00:00', '10:00:00', 1);
SELECT * FROM Sessions; -- 3 rows (1 approved, 2 not approved) */

/* --Approves both meeting at the same time - success
CALL approve_meeting(5, 5, CURRENT_DATE + 1, '07:00:00', '09:00:00', 1);
SELECT * FROM Sessions; -- 3 rows (3 approved) */

------------------------------------------------------------------------
-- Function for unbook_room
------------------------------------------------------------------------
CREATE OR REPLACE PROCEDURE unbook_room
    (IN in_floor INT, IN in_room INT, IN in_date DATE, IN in_start TIME, IN in_end TIME, IN in_id INT)
AS $$
DECLARE
curr_time TIME := in_start;

BEGIN
    -- Check if times given is valid
    IF (in_start >= in_end)
    THEN RAISE NOTICE 'Invalid time input (start time must be before end time)';

    -- Check if inputted date and time is over
    ELSIF (in_date < CURRENT_DATE) OR (in_date = CURRENT_DATE AND in_start < CURRENT_TIME)
    THEN RAISE NOTICE 'You can only unbook rooms in advance';

    ELSE
        LOOP
        EXIT WHEN curr_time >= in_end;
        IF EXISTS (SELECT * FROM Sessions S
                    WHERE S.time = curr_time
                        AND S.room = in_room
                        AND S.floor = in_floor 
                        AND S.date = in_date
                        AND S.booker_id = in_id) THEN
            DELETE FROM Sessions S
            WHERE S.time = curr_time
                AND S.date = in_date
                AND S.room = in_room
                AND S.floor = in_floor
                AND S.booker_id = in_id;
            END IF;
        SELECT curr_time + INTERVAL '1 hour' INTO curr_time;
        END LOOP;
    END IF;
END;
$$ LANGUAGE plpgsql;

/* --(OPTIONAL: in case there are existing entries)
TRUNCATE TABLE Employees, HealthDeclarations, Departments, MeetingRooms, 
Updates, Junior, Booker, Senior, Manager, Sessions, Joins CASCADE; */ 

/* --Setting up 5 Employees in database, 2 valid , 3 invalid
ALTER SEQUENCE Employees_eid_seq RESTART;
CALL add_department(1, 'Finance');
CALL add_employee('Eve', '00000000', 'Manager', 'Finance'); --eid 1 
CALL add_employee('Alice', '00000000', 'Senior', 'Finance'); --eid 2
CALL add_employee('Bob', '00000000', 'Junior', 'Finance'); --eid 3 
CALL add_employee('Fred', '00000000', 'Senior', 'Finance'); --eid 4 
CALL add_employee('Charles', '00000000', 'Senior', 'Finance'); --eid 5
CALL declare_health(1, CURRENT_DATE, 36.5);
CALL declare_health(2, CURRENT_DATE, 36.5);
*/

/* --Set up 1 meeting rooms
CALL add_room('Meeting Room A', 3, 3, 1);
CALL change_capacity(3, 3, 30, CURRENT_DATE, 1); 
*/

/* -- Book 6 hrs
CALL book_room(3, 3, CURRENT_DATE + 5, '09:00:00', '15:00:00', 1);
-- Book 1 hr
CALL book_room(3, 3, CURRENT_DATE + 1, '09:00:00', '10:00:00', 1);
SELECT * FROM Sessions; -- 7 rows */

/* --Invalid time input
CALL unbook_room(3, 3, CURRENT_DATE + 1, '09:00:00', '05:00:00', 1);
SELECT * FROM Sessions; -- 7 rows */

/* --Invalid date input
CALL unbook_room(3, 3, CURRENT_DATE - 1, '09:00:00', '10:00:00', 1);
SELECT * FROM Sessions; -- 7 rows */

/* --Deletion by non-booker not allowed
CALL unbook_room(3, 3, CURRENT_DATE + 1, '09:00:00', '10:00:00', 2);
SELECT * FROM Sessions; -- 7 rows */

/* --Multi-delete works 
CALL unbook_room(3, 3, CURRENT_DATE + 5, '08:00:00', '16:00:00', 1);
SELECT * FROM Sessions; -- 1 row */