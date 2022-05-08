<!DOCTYPE html>
<?php
if(isset($_GET['frame_so']))
	header('X-Frame-Options: SAMEORIGIN');
else if(isset($_GET['frame_deny']))
	header('X-Frame-Options: DENY');
?>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
		<h1>Welcome to the web security tutorial!</h1>
		<h2>Headers:</h2>
		<ul>
		<?php
		foreach (getallheaders() as $name => $value) {
			echo "<li>$name: $value</li>\n";
		}?>
		</ul>
		<script>
			var arr = document.URL.split("/");
			var origin = arr[0] + "//" + arr[2];
			console.log("Cookies in " + origin + ": " + document.cookie);
		</script>
	</body>
</html>
