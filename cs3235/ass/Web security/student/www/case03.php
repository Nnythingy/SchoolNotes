<html>
<head></head>
<body>
<h1>Case 03</h1>
	
<?php
$csrfToken = '522b2f2da93aad37a138677f33e5e11364161d23';
$flag_val = '8d978f6361871efffe25d8bdd3d313c13c6da317';
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
