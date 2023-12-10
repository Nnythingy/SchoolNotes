CREATE OR REPLACE FUNCTION customer_info_update(
	p_schema IN VARCHAR2, p_object IN VARCHAR2)
RETURN VARCHAR2 AS condition VARCHAR2 (200);
BEGIN
--	condition := 'username = SYS_CONTEXT("USERENV", "SESSION_USER")';
    condition := 'username = "customer_1"';
    RETURN condition;
END customer_info_update;