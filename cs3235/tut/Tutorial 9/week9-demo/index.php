<?php
if(isset($_GET['cors']))
	header('Access-Control-Allow-Origin: *');
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Web Security Tutorial</title>
	</head>
	<body>
		<h1>Welcome to the web security tutorial!</h1>
		<h2>Get some cookies!</h2>
		<h3>Default</h3>
		<ul>
			<li><a href="http://demo.org:80/cookie.php">demo.org:80</a></li>
			<li><a href="http://demo.org:8888/cookie.php">demo.org:8888</a></li>
			<li><a href="http://bbs.demo.org:80/cookie.php">bbs.demo.org:80</a></li>
			<li><a href="http://blog.demo.org:80/cookie.php">blog.demo.org:80</a></li>
		</ul>
		<h3>SameSite=None</h3>
		<ul>
			<li><a href="http://demo.org:80/cookie.php?cookie-none">demo.org:80</a></li>
			<li><a href="http://demo.org:8888/cookie.php?cookie-none">demo.org:8888</a></li>
			<li><a href="http://bbs.demo.org:80/cookie.php?cookie-none">bbs.demo.org:80</a></li>
			<li><a href="http://blog.demo.org:80/cookie.php?cookie-none">blog.demo.org:80</a></li>
		</ul>
		<h3>SameSite=Lax</h3>
		<ul>
			<li><a href="http://demo.org:80/cookie.php?cookie-lax">demo.org:80</a></li>
			<li><a href="http://demo.org:8888/cookie.php?cookie-lax">demo.org:8888</a></li>
			<li><a href="http://bbs.demo.org:80/cookie.php?cookie-lax">bbs.demo.org:80</a></li>
			<li><a href="http://blog.demo.org:80/cookie.php?cookie-lax">blog.demo.org:80</a></li>
		</ul>
		<h3>SameSite=Strict</h3>
		<ul>
			<li><a href="http://demo.org:80/cookie.php?cookie-strict">demo.org:80</a></li>
			<li><a href="http://demo.org:8888/cookie.php?cookie-strict">demo.org:8888</a></li>
			<li><a href="http://bbs.demo.org:80/cookie.php?cookie-strict">bbs.demo.org:80</a></li>
			<li><a href="http://blog.demo.org:80/cookie.php?cookie-strict">blog.demo.org:80</a></li>
		</ul>
	</body>
</html>
