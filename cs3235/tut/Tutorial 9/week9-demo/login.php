<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
		<form action="http://demo.org/login.php" method="POST">
			<input name="user" type="text">
			<input type="submit" value="Submit">
		</form>
		<script>
		<?php
		if(isset($_COOKIE['user'])){
			echo 'alert("You have already logged in as ' . $_COOKIE['user'] . '");';
		} else if($_SERVER['REQUEST_METHOD'] == 'POST') {
			setcookie('user', $_POST['user'], [ 'expires' => time() + 500 ]);
		}
		?>
		</script>
	</body>
</html>
