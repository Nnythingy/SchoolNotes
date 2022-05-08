<?php
if(!session_id())
    session_start();
if (empty($_SESSION['token'])) {
    $_SESSION['token'] = bin2hex(random_bytes(32));
}
$token = $_SESSION['token'];
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
        <h1>Greetings: <?php echo $_GET['greeter']; ?></h1>
		<form action="http://demo.org/form-safe.php" method="POST">
			<input name="csrf_token" type="hidden" value="<?php echo $token; ?>">
			<input name="amount" type="text">
			<input name="recipient" type="text">
			<input type="submit" value="Submit">
		</form>
		<script>
		<?php
		if(!isset($_COOKIE['user'])){
			echo 'alert("Please log in first!");';
		} else if($_SERVER['REQUEST_METHOD'] == 'POST') {
			if(!empty($_POST['csrf_token']) && hash_equals($token, $_POST['csrf_token'])){
				echo 'alert("' . $_COOKIE['user'] . ' transfers ' . $_POST['amount'] .
					' dollars to ' . $_POST['recipient'] . '");';
			} else{
				echo 'alert("CSRF token invalid!");';
			}
		}
		?>
		</script>
	</body>
</html>
