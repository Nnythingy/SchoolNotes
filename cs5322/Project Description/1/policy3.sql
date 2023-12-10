BEGIN
    DBMS_RLS.DROP_POLICY(
      	object_schema    => 'ECOMMERCE',
      	object_name      => 'Users',
      	policy_name      => 'customer_info_update_policy'
  	 );
   	DBMS_RLS.ADD_POLICY (
      	object_schema    => 'ECOMMERCE',
      	object_name      => 'Users',
      	policy_name      => 'customer_info_update_policy',
      	function_schema  => 'ECOMMERCE',
      	policy_function  => 'customer_info_update',
      	statement_types  => 'SELECT, UPDATE, DELETE',
        --statement_types  => 'UPDATE, DELETE',
      	update_check     => TRUE
  	 );
END;