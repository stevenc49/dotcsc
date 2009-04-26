<?PHP
session_start();
if (isset($_SESSION['login'])){
header ("Location: checkout.php");
}


$uname = "";
$pword = "";
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
	$pword = $_POST['password'];

	$uname = htmlspecialchars($uname);
	$pword = htmlspecialchars($pword);

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
		$pword = quote_smart($pword, $db_handle);

		$SQL = "SELECT * FROM users WHERE username = $uname AND password = md5($pword)";
		$result = mysql_query($SQL);
		$num_rows = mysql_num_rows($result);

	//====================================================
	//	CHECK TO SEE IF THE $result VARIABLE IS TRUE
	//====================================================

		if ($result) {
			if ($num_rows > 0) {
				session_start();
				$_SESSION['login'] = "$uname";
				header ("Location: checkout.php");
			}
			else {
				session_start();
				$_SESSION['login'] = "";	//TODO: fix bug when incorrect login, './'surrounds login
				$errorMessage = "<br>Login is incorrect.";
				//header ("Location: signup.php");
			}	
		}
		else {
			$errorMessage = "Error logging on";
		}

	mysql_close($db_handle);

	}

	else {
		$errorMessage = "Error logging on";
	}

}


?>


<html>
<head>
<title>Login</title>
</head>
<body>

<font color="red">
	<?PHP print $errorMessage;?><br><br>
</font>
<FORM NAME ="form1" METHOD ="POST" ACTION ="login.php">

<table>
		<tr>
			<td width="80">
				<b>Username:</b>
			</td>
			<td width="80">
				<INPUT TYPE = 'TEXT' Name ='username'  value="" maxlength="20">
			</td>
		</tr>	
		<tr>
			<td width="80">
				<b>Password:</b>
			</td>
			<td width="80">
				<INPUT TYPE = 'password' Name ='password'  value="" maxlength="16">
			</td>
		</tr>
		
</table>
<INPUT TYPE = "Submit" Name = "Submit1"  VALUE = "Login"> </FORM>

</p>
</body>
</html>