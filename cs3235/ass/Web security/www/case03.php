<html>
<head></head>
<body>
<h1>Case 03</h1>
	
<?php
$csrfToken = '!!CSRF_TOKEN!!';
$flag_val = '!!FLAG_VALUE!!';
if(isset($_POST['csrf_token']) and
  $_POST['csrf_token'] == $csrfToken){
  echo "Successful post.<br/>";
  echo '<script>console.log("Flag: '.$flag_val.'");</script>'; 
}
?>
<form action='' method='post'>
  <input type='hidden' name='csrf_token' value='<?php echo $csrfToken; ?>'/>
  <input type='submit' name='submit' value='submit'/>
</form>
</body>
</html>
