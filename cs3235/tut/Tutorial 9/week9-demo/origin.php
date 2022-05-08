<!DOCTYPE html>
<?php
$frame_args = "";
if(isset($_GET['frame_so'])){
	$frame_args .= '?frame_so';
} else if(isset($_GET['frame_deny'])){
	$frame_args .= '?frame_deny';
}
?>
<html>
	<head>
		<meta charset="utf-8">
		<title>Same Origin Policy Demo</title>
		<link rel="stylesheet" href="http://demo.org:80/css/demo80.css">
		<link rel="stylesheet" href="http://demo.org:8888/css/demo8888.css">
		<link rel="stylesheet" href="http://bbs.demo.org:80/css/bbs.css">
		<link rel="stylesheet" href="http://blog.demo.org:80/css/blog.css">
	</head>
	<body>
		<script>
			function load_listener(){
				alert("Loaded");
			}
			function access(url, method){
				const request = new XMLHttpRequest();
				request.addEventListener("load", load_listener);
				request.open(method, url, true);
				request.send();
			}
			function set_domain(domain){
				document.domain = domain;
			}
		</script>
		<h3>GET XMLHttpRequest</h3>
		<button onclick="access('http://demo.org:80/', 'GET')">demo.org:80</button>
		<button onclick="access('http://demo.org:8888/', 'GET')">demo.org:8888</button>
		<button onclick="access('http://bbs.demo.org:80/', 'GET')">bbs.demo.org:80</button>
		<button onclick="access('http://blog.demo.org:80/', 'GET')">blog.demo.org:80</button>
		<h3>POST XMLHttpRequest</h3>
		<button onclick="access('http://demo.org:80/', 'POST')">demo.org:80</button>
		<button onclick="access('http://demo.org:8888/', 'POST')">demo.org:8888</button>
		<button onclick="access('http://bbs.demo.org:80/', 'POST')">bbs.demo.org:80</button>
		<button onclick="access('http://blog.demo.org:80/', 'POST')">blog.demo.org:80</button>
		<h3>GET XMLHttpRequest (CORS)</h3>
		<button onclick="access('http://demo.org:80/?cors', 'GET')">demo.org:80</button>
		<button onclick="access('http://demo.org:8888/?cors', 'GET')">demo.org:8888</button>
		<button onclick="access('http://bbs.demo.org:80/?cors', 'GET')">bbs.demo.org:80</button>
		<button onclick="access('http://blog.demo.org:80/?cors', 'GET')">blog.demo.org:80</button>
		<h3>POST XMLHttpRequest (CORS)</h3>
		<button onclick="access('http://demo.org:80/?cors', 'POST')">demo.org:80</button>
		<button onclick="access('http://demo.org:8888/?cors', 'POST')">demo.org:8888</button>
		<button onclick="access('http://bbs.demo.org:80/?cors', 'POST')">bbs.demo.org:80</button>
		<button onclick="access('http://blog.demo.org:80/?cors', 'POST')">blog.demo.org:80</button>
		<h3>iframes</h3>
		<h4>demo.org:80</h4>
		<iframe name="demo80iframe" height=400px width=400px src="http://demo.org:80/frame.php<?php echo $frame_args ?>"></iframe>
		<h4>demo.org:8888</h4>
		<iframe name="demo8888iframe" height=400px width=400px src="http://demo.org:8888/frame.php<?php echo $frame_args ?>"></iframe>
		<h4>bbs.demo.org:80</h4>
		<iframe name="bbsiframe" height=400px width=400px src="http://bbs.demo.org:80/frame.php<?php echo $frame_args ?>"></iframe>
		<h4>blog.demo.org:80</h4>
		<iframe name="blogiframe" height=400px width=400px src="http://blog.demo.org:80/frame.php<?php echo $frame_args ?>"></iframe>
		<h3>img</h3>
		<h4>demo.org:80</h4>
		<img width=90px src="http://demo.org:80/images/cat.png">
		<h4>demo.org:8888</h4>
		<img width=90px src="http://demo.org:8888/images/cat.png">
		<h4>bbs.demo.org:80</h4>
		<img width=90px src="http://bbs.demo.org:80/images/cat.png">
		<h4>blog.demo.org:80</h4>
		<img width=90px src="http://blog.demo.org:80/images/cat.png">
		<h3>css</h3>
		<h4 class="demo80">demo.org:80</h4>
		<h4 class="demo8888">demo.org:8888</h4>
		<h4 class="bbs">bbs.demo.org:80</h4>
		<h4 class="blog">blog.demo.org:80</h4>
		<h3>form (POST)</h3>
		<form action="http://demo.org:80/" method="POST">
			<input type="submit" value="demo.org:80">
		</form>
		<form action="http://demo.org:8888/" method="POST">
			<input type="submit" value="demo.org:8888">
		</form>
		<form action="http://bbs.demo.org:80/" method="POST">
			<input type="submit" value="bbs.demo.org:80">
		</form>
		<form action="http://blog.demo.org:80/" method="POST">
			<input type="submit" value="blog.demo.org:80">
		</form>
			<h3>form (GET)</h3>
		<form action="http://demo.org:80/" method="GET">
			<input type="submit" value="demo.org:80">
		</form>
		<form action="http://demo.org:8888/" method="GET">
			<input type="submit" value="demo.org:8888">
		</form>
		<form action="http://bbs.demo.org:80/" method="GET">
			<input type="submit" value="bbs.demo.org:80">
		</form>
		<form action="http://blog.demo.org:80/" method="GET">
			<input type="submit" value="blog.demo.org:80">
		</form>
		<script>
			var url_from = "demo.org:80";
		</script>
		<script src="http://demo.org:80/scripts/sayhello.js"></script>
		<script>
			url_from = "demo.org:8888";
		</script>
		<script src="http://demo.org:8888/scripts/sayhello.js"></script>
		<script>
			url_from = "bbs.demo.org:80";
		</script>
		<script src="http://bbs.demo.org:80/scripts/sayhello.js"></script>
		<script>
			url_from = "blog.demo.org:80";
		</script>
		<script src="http://blog.demo.org:80/scripts/sayhello.js"></script>
		<script>
			function show_cookie(){	
				var frame = document.getElementsByName("demo80iframe")[0];
				try{
					console.log("Cookie of demo.org:80 = " + frame.contentDocument.cookie);
				} catch(err){
					console.log(err);
				}
				frame = document.getElementsByName("demo8888iframe")[0];
				try{
					console.log("Cookie of demo.org:8888 = " + frame.contentDocument.cookie);
				} catch(err){
					console.log(err);
				}
				frame = document.getElementsByName("bbsiframe")[0];
				try{
					console.log("Cookie of bbs.demo.org:80 = " + frame.contentDocument.cookie);
				} catch(err){
					console.log(err);
				}
				frame = document.getElementsByName("blogiframe")[0];
				try{
					console.log("Cookie of blog.demo.org:80 = " + frame.contentDocument.cookie);
				} catch(err){
					console.log(err);
				}
			}
		</script>
		<h3>Cookies</h3>
		<button onclick="show_cookie()">Show cookies</button>
		<h4><a href="http://demo.org:80/">demo.org:80</a></h4>
		<h4><a href="http://demo.org:8888/">demo.org:8888</a></h4>
		<h4><a href="http://bbs.demo.org:80/">bbs.demo.org:80</a></h4>
		<h4><a href="http://blog.demo.org:80/">blog.demo.org:80</a></h4>
	</body>
</html>
