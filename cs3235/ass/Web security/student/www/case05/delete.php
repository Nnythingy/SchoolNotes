<html>
<head></head>
<body>
<h1>Removing your account</h1>
	
<?php
$Flag = '8d68424c1387bc61e86dfb9598c2fa4dca822cbf';
$cookie_value = 'cc682385c5b4b2095fe6b733a92c565b72ec6a5a';
$csrfToken = '522b2f2da93aad37a138677f33e5e11364161d23';
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
