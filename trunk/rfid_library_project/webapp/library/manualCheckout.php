<?php
include ("TopRegion.php");
include ("db2.php");
include ("adminLinks.php");
$bookId = $_SESSION['bookId'];
?>

<?PHP

$uname = "";
$errorMessage = "";
//==========================================
//	ESCAPE DANGEROUS SQL CHARACTERS
//==========================================
function quote_smart($value, $handle) {

   if (get_magic_quotes_gpc()) {
       $value = stripslashes($value);
   }

   if (!is_numeric($value)) {
       $value = "'" . mysql_real_escape_string($value, $handle) . "'";
   }
   return $value;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST'){
	$uname = $_POST['username'];

	$uname = htmlspecialchars($uname);

	//==========================================
	//	CONNECT TO THE LOCAL DATABASE
	//==========================================
	$user_name = "root";
	$pass_word = "";
	$database = "libraryDB";
	$server = "127.0.0.1";

	$db_handle = mysql_connect($server, $user_name, $pass_word);
	$db_found = mysql_select_db($database, $db_handle);

	if ($db_found) {

		$uname = quote_smart($uname, $db_handle);
	

		//check if user input exists in user table
		$SQL = "SELECT username FROM users WHERE username=$uname";
		$result = mysql_query($SQL);
		$num_rows = mysql_num_rows($result);
		
		if ($result)
		{
			if ($num_rows > 0)
			{
				//check out to user
				$SQL = "UPDATE books SET checkedoutBy=$uname WHERE bookid=$bookId";
				mysql_query($SQL);

				//change status to checked out
				$SQL = "UPDATE books SET status=\"Checked Out\" WHERE bookid=$bookId";
				mysql_query($SQL);

				//update due date
				//$today = date('y:m:d');
				$today = date('y:m:d');
				//$dueDate = date_add($today, new DateInterval("P5D"));
				// add 3 days to date
				$NewDate=Date('y:m:d', strtotime("+14 days"));
				$SQL = "UPDATE books SET dueDate=\"$NewDate\" WHERE bookid=$bookId";
				mysql_query($SQL);
				
				//return to admin Catalog
				header ("Location: adminCatalog.php?action=");
			}
			else
			{
				$uname = trim($uname, "'");
				$errorMessage = "$uname does not exist";
			}
		}
		else {
			print ("Check Out Unsuccessful");
		}



	mysql_close($db_handle);

	}

	else {
		$errorMessage = "Error checking out";
	}

}


?>
<html>
<br>
<head>
<title>Manual Check-Out</title>
</head>
	<body>
	
	<font color="red">
		<?PHP print $errorMessage;?>
	</font>
	<h2>Manual Check-Out</h2>
		Enter the username of the book that is checked out.
		<br><br>
		<FORM NAME ="form1" METHOD ="POST" ACTION ="manualCheckout.php" >

		<b>Check out to</b> : <INPUT TYPE = 'TEXT' Name ='username'  value="" maxlength="500">

		<INPUT TYPE = "Submit" Name = "Submit1"  VALUE = "Submit">

		</FORM>
		<br><br>
<?php
include ("footer.php");
?>
		</body>
	</html>