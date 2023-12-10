-- Demo script of Projects Table

--1. Login as user company who is granted with Read privilege of OLS policy to show whole table
SELECT * FROM PROJECTS;

--2. Login as user hr_1 who is HR manager and authorized with User label "S:MAN,TEC,SAF,REP,STR,REV,BLU:HR_MGR"
-- Level: Secret , 
-- Compartments: TECHNICAL, MANAGERIAL, SAFETY, REPORT, BLUEPRINT,STRATEGY, and REVIEW.
-- Group: HUMAN_RESOURCE_MANAGEMENT but also can access it's child group HUMAN_RESOURCE_RECRUITERS

-- HR Manager can view all projects of HR department
SELECT PROJECTID, PROJECTNAME, SECURITYLEVEL,DEPARTMENT,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTS 
ORDER BY general_ols_col;

-- 3. HR Manager is able to add a new project of which default data label is "S:MAN,TEC,SAF,REP,STR,REV,BLU:HR_MGR" 
INSERT INTO Company.PROJECTS (PROJECTID, PROJECTNAME, STARTDATE, ENDDATE, DEPARTMENT, SECURITYLEVEL) 
VALUES (50120, 'Demo', TO_DATE('2021-02-01', 'YYYY-MM-DD'), TO_DATE('2023-02-01', 'YYYY-MM-DD'), 'HR', 'Restricted');


-- 4. HR Manager able to update project data label 
UPDATE COMPANY.PROJECTS
SET    general_ols_col = CHAR_TO_LABEL('general_ols_policy','C::HR_REC')
WHERE  PROJECTID = 50120;

--5. Login as user hr_2 who is HR employee and authorized with User label "S:TEC,SAF,REP,STR,REV,BLU:HR_REC"
--Level: Secret level, 
--Compartments: TECHNICAL, SAFETY, REPORT, BLUEPRINT,STRATEGY, and REVIEW.
--Group: HUMAN_RESOURCE_RECRUITERS group 

-- HR employee can view all projects of HR department excpet for those are developed by HR management team which belong to ancestor group
SELECT PROJECTID, PROJECTNAME, SECURITYLEVEL,DEPARTMENT,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTS 
ORDER BY general_ols_col;

-- 6. run above step 3., expect to fail since DAC don't grant granted 'INSERT' and 'UPDATE' permissions on this table to Role:employee 


--7. Login as user globalit_1 who is IT Global  manager and authorized with User label "S:MAN,TEC,SAF,FIN,REP,BUD,REV,BLU:IT_GLOBAL_MGR"
--Level:Secret level, 
--Compartments: FINANCIAL, TECHNICAL, MANAGERIAL, SAFETY, REPORT, BLUEPRINT, BUDGET, and REVIEW.
--Group: TECHNOLOGY_SUPPORT_MANAGEMENT group but also can access child group TECHNOLOGY_GLOBAL_ENGINEERS, TECHNOLOGY_SUPPORT_TECHNICIAN and TECHNOLOGY_GLOBAL_TECHNICIAN 
-- 

-- IT Global Manager can view all projects of their departments including IT Support department which is under IT Global
SELECT PROJECTID, PROJECTNAME, SECURITYLEVEL,DEPARTMENT,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTS 
ORDER BY general_ols_col;

--8. Login as user globalit_2 who is Global IT Engineer and authorized with User label "C:TEC,SAF,REP,REV,BLU:IT_GLOBAL_ENG"
-- Level:Confidential level, 
-- Compartments: TECHNICAL, SAFETY, REPORT, BLUEPRINT,and REVIEW.
-- Group: TECHNOLOGY_GLOBAL_ENGINEERS group 

-- IT Global ENGINEERs only can view projects of Global IT departments <= Confidential level, but cannot view project of IT Support department since the group of IT Support department is not child group of TECHNOLOGY_GLOBAL_ENGINEERS
SELECT PROJECTID, PROJECTNAME, SECURITYLEVEL,DEPARTMENT,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTS 
ORDER BY general_ols_col;


--------------------------------------------------------------------------------------------

-- Demo script of ProjectDocuments Table

--1. Login as user company who is granted with Read privilege of OLS policy to show whole table
SELECT * FROM PROJECTDOCUMENTATION; -- use documents of project Project Falcon to demo


--2. Login as user globalit_1 who is IT Global manager and authorized with User label "S:MAN,TEC,SAF,FIN,REP,BUD,REV,BLU:IT_GLOBAL_MGR"
--Level:Secret level, 
--Compartments: FINANCIAL, TECHNICAL, MANAGERIAL, SAFETY, REPORT, BLUEPRINT, BUDGET, and REVIEW.
--Group: TECHNOLOGY_SUPPORT_MANAGEMENT group but also can access child group TECHNOLOGY_GLOBAL_ENGINEERS, TECHNOLOGY_SUPPORT_TECHNICIAN and TECHNOLOGY_GLOBAL_TECHNICIAN 
-- 

-- IT Global Managers can view all project documents of their departments including documents of IT Support department 
SELECT PROJECTID, PROJECTNAME, CONTENT, DOCUMENTTYPE, SECURITYLEVEL, DEPARTMENT, DATATYPE,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTDOCUMENTATION 
ORDER BY general_ols_col;


--3. Login as user globalit_2 who is Global IT Engineer and authorized with User label "C:TEC,SAF,REP,REV,BLU:IT_GLOBAL_ENG"
-- Level:Confidential level, 
-- Compartments: TECHNICAL, SAFETY, REPORT, BLUEPRINT,and REVIEW.
-- Group: TECHNOLOGY_GLOBAL_ENGINEERS group 

-- IT Global ENGINEERs can view documents of Project Falcon except for those secret-level doc, budget/finiancial related doc, and doc of IT support department
SELECT DOCID, PROJECTID, PROJECTNAME, CONTENT, DOCUMENTTYPE, SECURITYLEVEL, DEPARTMENT, DATATYPE,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTDOCUMENTATION 
ORDER BY general_ols_col;

-- IT Global ENGINEERs can add new project document
INSERT INTO Company.PROJECTDOCUMENTATION (DOCID, PROJECTID, PROJECTNAME, DOCUMENTTYPE, CONTENT, DATATYPE, DEPARTMENT, SECURITYLEVEL) 
VALUES (40020, 50101, 'Project Falcon', 'Technical', 'demo', 'Review', 'Global IT', 'Confidential');

-- IT Global ENGINEERs can update project document
UPDATE COMPANY.PROJECTDOCUMENTATION
SET    CONTENT = 'Technical specifications for project Falcon... DEMO'
WHERE  DOCID = 40001;

--4. Login as user globalit_3 who is Global IT Technician and authorized with default User label "R:TEC,SAF,REP,REV,BLU:IT_GLOBAL_TEC"
-- Default Level:Restricted level, 
-- Compartments: TECHNICAL, SAFETY, REPORT, BLUEPRINT,and REVIEW.
-- Group: TECHNOLOGY_GLOBAL_TECHNICIANS group 

-- IT Global Technician can view Project Falcon except for those secret/confidential-level doc, budget/finiancial related doc, and doc of IT support department
SELECT PROJECTID, PROJECTNAME, CONTENT, DOCUMENTTYPE, SECURITYLEVEL, DEPARTMENT, DATATYPE,
LABEL_TO_CHAR(general_ols_col) OLS_LABEL 
FROM COMPANY.PROJECTDOCUMENTATION 
ORDER BY general_ols_col;
