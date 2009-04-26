<?PHP
include ("TopRegion.php");
include ("db2.php");
include ("adminLinks.php");
if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
	header ("Location: home.php");
}
?>
<br>
<h3 align="center">
<?php
	if (isset($_POST['Submit1'])) {
	print "Book succesfully added into the database";
	}
	
?>
</h3>

<?PHP
$bookTag = "";
$shelfNum = "";
$title = "";
$abbTitle = "";
$author = "";
$ISBN = "";
$callNum = "";
$errorMessage = "";
$num_rows = 0;

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

	//====================================================================
	//	GET THE CHOSEN U AND P, AND CHECK IT FOR DANGEROUS CHARCTERS
	//====================================================================
	$bookTag = $_POST['booktag'];
	$shelfNum = $_POST['shelfnum'];
	$title = $_POST['title'];
	$abbTitle = $_POST['abbTitle'];
	$author = $_POST['author'];
	$ISBN = $_POST['isbn'];
	$callNum = $_POST['callNum'];

	$bookTag = htmlspecialchars($bookTag);
	$shelfNum = htmlspecialchars($shelfNum);
	$title = htmlspecialchars($title);
	$abbTitle = htmlspecialchars($abbTitle);
	$author = htmlspecialchars($author);
	$ISBN = htmlspecialchars($ISBN);
	$callNum = htmlspecialchars($callNum);

//test to see if $errorMessage is blank
//if it is, then we can go ahead with the rest of the code
//if it's not, we can display the error

	//====================================================================
	//	Write to the database
	//====================================================================
	if ($errorMessage == "") {

	$user_name = "root";
	$pass_word = "";
	$database = "libraryDB";
	$server = "127.0.0.1";

	$db_handle = mysql_connect($server, $user_name, $pass_word);
	$db_found = mysql_select_db($database, $db_handle);

	if ($db_found) {

		$bookTag = quote_smart($bookTag, $db_handle);
		$shelfNum = quote_smart($shelfNum, $db_handle);
		$title = quote_smart($title, $db_handle);
		$abbTitle = quote_smart($abbTitle, $db_handle);
		$author = quote_smart($author, $db_handle);
		$ISBN = quote_smart($ISBN, $db_handle);
		$callNum = quote_smart($callNum, $db_handle);
		
	//====================================================================
	//	CHECK THAT THE USERNAME IS NOT TAKEN
	//====================================================================

			$SQL = "INSERT INTO books (bookTagNum, shelfNum, title, abbreviatedTitle, author, isbn, callNum) VALUES ($bookTag, $shelfNum, $title, $abbTitle, $author, $ISBN, $callNum)";
			$result = mysql_query($SQL);
			mysql_close($db_handle);
			//header ("Location: addbook.php");
			
			$title = "";
			$author = "";
			$ISBN = "";
			$callNum = "";
				}
	}
}


?>

	<html>
	<head>
	<title>Book Registration</title>


	</head>
	<body>

		<br>
		<h3 align="center"> Add new books here or please choose another option</h3>

<FORM NAME ="form1" METHOD ="POST" ACTION ="addbook.php">
<p align="center">
<table>
		<tr>
			
				<td width="150" height="20">
					<font  color="black">
						<b>Book Tag Number:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='booktag'  value="" maxlength="4"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>Shelf Number:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='shelfnum'  value="" maxlength="2"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>Title:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='title'  value="<?PHP print $title;?>" maxlength="500"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>Abbreviated Title:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='abbTitle'  value="" maxlength="16"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>Author:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='author'  value="<?PHP print $author;?>" maxlength="500"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>ISBN:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='isbn'  value="<?PHP print $ISBN;?>" maxlength="500"> <br>
					</font>
				</td>
		</tr>
		<tr>
				<td width="150" height="20">
					<font   color="black">
						<b>Call Number:</b>
					</font>
				</td>
				<td width="150" height="20">
					<font   color="black">
						<INPUT TYPE = 'TEXT' Name ='callNum'  value="<?PHP print $callNum;?>" maxlength="500"><br>
					</font>
		</tr>
		
				</td>
			</tr>
</table>

<br>
<INPUT TYPE = "Submit" Name = "Submit1"  VALUE = "Submit">




</FORM>
<br>
</p>
<?PHP print $errorMessage;?>
<br><br>
<?php
include ("footer.php");
?>
	</body>
	</html>
