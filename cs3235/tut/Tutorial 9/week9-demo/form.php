<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
		<form action="http://demo.org/form.php" method="POST">
			<input name="amount" type="text">
			<input name="recipient" type="text">
			<input type="submit" value="Submit">
		</form>
		<script>
		<?php
		if(!isset($_COOKIE['user'])){
			echo 'alert("Please log in first!");';
		} else if($_SERVER['REQUEST_METHOD'] == 'POST') {
			echo 'alert("' . $_COOKIE['user'] . ' transfers ' . $_POST['amount'] .
				' dollars to ' . $_POST['recipient'] . '");';
		}
		?>
		</script>
	</body>
</html>
