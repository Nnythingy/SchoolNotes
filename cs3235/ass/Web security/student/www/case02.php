<h1>Case 02</h1>
<?php session_start();
	include_once 'global-libs/HTMLPurifier/HTMLPurifier.auto.php';
	$config = HTMLPurifier_Config::createDefault();
	$purifier = new HTMLPurifier($config);

	include_once 'includes/db_connect.php';
	define("TABLE", "table2");

	if (isset($_POST['search'])) {
		$search = $_POST['search'];
		$query = "SELECT voucher from ".TABLE ." WHERE id = '".$search."'";
		
		$result = mysqli_query($conn, $query);
		
		include_once 'includes/show_error.php';

		if (isset($result) and empty($clean_sqlerror)){
			while ($row = mysqli_fetch_array($result)) {
				$voc = $row[0];
			}
		}
		
		mysqli_close($conn);

	}
?>
<html>
	<body>
		<div align="center">
			Grab Your discount vouchers. Only admin will get it this round.
			<br/>
			<?php
			if (isset($voc) && !isset($clean_sqlerror) && $voc != "") {
				echo "Your voucher (aka flag) is <b>\"" . $voc . "\"</b><br/><br/>";
			} else {
				echo "The id does not belong to an admin<br/><br/>";
			}
			$voc = "";
			?>
			<form method="post" action="">
				<label for="search">Enter UserId (eg.1): </label>
				<input type="text" name="search">
				<br/>
				<br/>
				<input type="submit">
			</form>
		</div>
	</body>

</html>

