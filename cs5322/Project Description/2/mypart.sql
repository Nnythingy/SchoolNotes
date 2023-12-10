--in lbac account
BEGIN
    SA_POLICY_ADMIN.APPLY_TABLE_POLICY (
            policy_name    => 'general_ols_policy',
            schema_name    => 'company',
            table_name     => 'projectdocumentation',
            table_options  => 'read_control');
END;

-- Enable OLS policy on projectdocumentation table
BEGIN
    SA_POLICY_ADMIN.ENABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'projectdocumentation');
END;

-- Enable OLS policy on projectdocumentation table
BEGIN
    SA_POLICY_ADMIN.DISABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'projectdocumentation');
END;

--in company schema account
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C:TEC,REP:IT_GLOBAL')
WHERE docid = 40001;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S:STR,BLU:HR')
WHERE docid = 40002;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R:FIN,BUD:IT_GLOBAL')
WHERE docid = 40003;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C:TEC,REP:IT_SUPPORT')
WHERE docid = 40004;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S:STR,BLU:HR')
WHERE docid = 40005;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R:TEC,REP:IT_GLOBAL')
WHERE docid = 40006;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C:STR,REP:HR')
WHERE docid = 40007;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S:TEC,BLU:IT_GLOBAL')
WHERE docid = 40008;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R:TEC,REP:IT_SUPPORT')
WHERE docid = 40009;
UPDATE projectdocumentation
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C:FIN,BUD:IT_GLOBAL')
WHERE docid = 40010;

--in lbac account
-- Disable OLS policy on projectdocumentation table
BEGIN
    SA_POLICY_ADMIN.ENABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'projectdocumentation');
END;

BEGIN
    SA_POLICY_ADMIN.APPLY_TABLE_POLICY (
            policy_name    => 'general_ols_policy',
            schema_name    => 'company',
            table_name     => 'employeetrainingrecords',
            table_options  => 'read_control');
END;

-- Enable OLS policy on employeetrainingrecords table
BEGIN
    SA_POLICY_ADMIN.ENABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'employeetrainingrecords');
END;

-- Enable OLS policy on employeetrainingrecords table
BEGIN
    SA_POLICY_ADMIN.DISABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'employeetrainingrecords');
END;

--in company schema account
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R')
WHERE trainingrecordid = 20001;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C')
WHERE trainingrecordid = 20002;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S')
WHERE trainingrecordid = 20003;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R')
WHERE trainingrecordid = 20004;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C')
WHERE trainingrecordid = 20005;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S')
WHERE trainingrecordid = 20006;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R')
WHERE trainingrecordid = 20007;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'C')
WHERE trainingrecordid = 20008;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'S')
WHERE trainingrecordid = 20009;
UPDATE employeetrainingrecords
SET general_ols_col = CHAR_TO_LABEL('general_ols_policy', 'R')
WHERE trainingrecordid = 20010;

-- Enable OLS policy on employeetrainingrecords table
BEGIN
    SA_POLICY_ADMIN.ENABLE_TABLE_POLICY (
            policy_name => 'general_ols_policy',
            schema_name => 'company',
            table_name  => 'employeetrainingrecords');
END;