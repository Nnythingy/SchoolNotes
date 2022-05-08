<HTML>
	<h1>Login</h1>
	<body>
		<?php 
			$cookie_name = 'usercookie';
			$cookie_value='8458bb3b73557469a81d49d3fe88c1ec3e570ede';
			setcookie($cookie_name, $cookie_value, time() + (86400 * 90), '/'); // 86400 = 1 day
		?>
		<p>You have been successfully logged in</p>
	</body>
</HTML>
