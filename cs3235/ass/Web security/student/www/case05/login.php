<HTML>
	<h1>Login</h1>
	<body>
		<?php 
			$cookie_name = 'usercookie';
			$cookie_value='cc682385c5b4b2095fe6b733a92c565b72ec6a5a';
			setcookie($cookie_name, $cookie_value, time() + (86400 * 90), '/'); // 86400 = 1 day
		?>
		<p>You have been successfully logged in</p>
	</body>
</HTML>
