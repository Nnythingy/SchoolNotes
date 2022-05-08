<!doctype HTML>
<html>
<head>
	<meta charset="utf-8">
	<title>I'm a cookie thief!</title>
</head>
<body>
	<?php
		$flag = 'f667abf6d272a1257d4557b6ef2aeddc1de15f12';
		$cookie_value = '';
		if($_SERVER['REQUEST_METHOD'] == 'POST'){
			$cookie_value = $_POST['cookie'];
		} else{
			$cookie_value = $_GET['cookie'];
		}
		if(strpos($cookie_value, '8458bb3b73557469a81d49d3fe88c1ec3e570ede') !== false){
			echo '<p>This cookie is delicious.</p>';
			echo '<script>console.log("It is dangerous to go alone. Take this. (you got a flag ' . $flag . ')");</script>';
		} else{
			echo 'Horrible cookie!';
		}
	?>
</body>
</html>
