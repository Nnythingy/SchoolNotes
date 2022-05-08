<!DOCTYPE HTML>
<html>
	<head>
		<title>Requested page not found</title>
		<meta charset="utf-8">
	</head>
	<body>
		<?php 
			echo "Your requested page " . urldecode($_SERVER['REQUEST_URI']) . ' does not exist!';
		?>	
	</body>
</html>
