<html>
<head></head>
<body>
<h1>Removing your account</h1>
	
<?php
$Flag = '!!FLAG_VALUE!!';
$cookie_value = '!!COOKIE_VALUE!!';
$csrfToken = '!!CSRF_TOKEN!!';
if(isset($_COOKIE['usercookie']) and
	$_COOKIE['usercookie'] == $cookie_value and
	isset($_POST['csrf_token']) and
  $_POST['csrf_token'] == $csrfToken){
  echo "Account deleted!.<br/>";
  echo "You won a flag: " . $Flag;
}
?>
Are you sure you want to delete your account?
<form action='' method='post'>
  <input type='hidden' name='csrf_token' value='<?php echo $csrfToken; ?>'/>
  <input type='submit' name='submit' value='Yes!'/>
</form>
</body>
</html>
