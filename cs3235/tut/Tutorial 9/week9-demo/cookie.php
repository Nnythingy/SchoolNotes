<?php
$samesite = "";
if(isset($_GET['cookie-strict']))
	$samesite = "Strict";
else if(isset($_GET['cookie-lax']))
	$samesite = "Lax";
else if(isset($_GET['cookie-none']))
	$samesite = "None";
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
		<h1>Cookies handout!</h1>
		</ul>
		<script>
			var arr = document.URL.split("/");
			var origin = arr[0] + "//" + arr[2];
			var cookie_name = "cookie" + origin.substring(7);
			console.log("Cookies in " + origin + ": " + document.cookie);
			var samesite="<?php echo $samesite; ?>";
			if(samesite === ""){
				document.cookie = cookie_name + "=" + origin + "; max-age=300"
			} else{
				document.cookie = cookie_name + "=" + origin + "; max-age=300; SameSite=" + samesite;
			}
		</script>
	</body>
</html>
