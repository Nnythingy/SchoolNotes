<HTML>
	<h1>Login</h1>
	<body>
		<?php 
			$cookie_name = 'usercookie';
			$cookie_value='!!COOKIE_VALUE!!';
			setcookie($cookie_name, $cookie_value, time() + (86400 * 90), '/'); // 86400 = 1 day
		?>
		<p>You have been successfully logged in</p>
	</body>
</HTML>
