<!DOCTYPE html>
<html>
<head><title>Post a message here</title></head>
<body>
<?php if($_SERVER['REQUEST_METHOD'] == "GET"): ?>
Post a message here
<form method="POST" action="/post.php">
<input type="text" name="message"></input>
<input type="submit" value="Submit"></input>
</form>
<?php else: ?>
<?php 
$file = fopen("/tmp/message.txt", "w") or die("unable to open file");
$message = $_POST['message'];
fwrite($file, $message);
fclose($file);
?>
Message submitted.
<?php endif; ?>
<script>
</script>
</body>
</html>
