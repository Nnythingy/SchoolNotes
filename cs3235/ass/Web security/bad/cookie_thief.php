<!doctype HTML>
<html>
<head>
	<meta charset="utf-8">
	<title>I'm a cookie thief!</title>
</head>
<body>
	<?php
		$flag = '!!FLAG_VALUE!!';
		$cookie_value = '';
		if($_SERVER['REQUEST_METHOD'] == 'POST'){
			$cookie_value = $_POST['cookie'];
		} else{
			$cookie_value = $_GET['cookie'];
		}
		if(strpos($cookie_value, '!!COOKIE_VALUE!!') !== false){
			echo '<p>This cookie is delicious.</p>';
			echo '<script>console.log("It is dangerous to go alone. Take this. (you got a flag ' . $flag . ')");</script>';
		} else{
			echo 'Horrible cookie!';
		}
	?>
</body>
</html>
