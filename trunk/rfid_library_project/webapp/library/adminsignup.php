<?PHP
//session_start();
//if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
	//header ("Location: login.php");
//}

//set the session variable to 1, if the user signs up. That way, they can use the site straight away
//do you want to send the user a confirmation email?
//does the user need to validate an email address, before they can use the site?
//do you want to display a message for the user that a particular username is already taken?
//test to see if the u and p are long enough
//you might also want to test if the users is already logged in. That way, they can't sign up repeatedly without closing down the browser
//other login methods - set a cookie, and read that back for every page
//collect other information: date and time of login, ip address, etc
//don't store passwords without encrypting them

echo '<a href="home.php"><img src="img/Header.jpg" width="100%" border=0><a>';

$uname = "";
$pword = "";
$ecode = "";
$error = "";
$errorMessage = "";
$errorMessage2 = "";
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
	$uname = $_POST['username'];
	$pword = $_POST['password'];
	$ecode = $_POST['employeeCode'];

	$uname = htmlspecialchars($uname);
	$pword = htmlspecialchars($pword);
	$ecode = htmlspecialchars($ecode);

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

		$uname = quote_smart($uname, $db_handle);
		$pword = quote_smart($pword, $db_handle);
		$ecode = quote_smart($ecode, $db_handle);

	//====================================================================
	//	CHECK THAT THE USERNAME IS NOT TAKEN
	//====================================================================
		$SQL = "SELECT * FROM users WHERE username = $uname";
		$result = mysql_query($SQL);
		$num_rows = mysql_num_rows($result);

		//If Username Already Taken
		if ($num_rows > 0) {
			$errorMessage = "Username already taken";
				if ($ecode != "123")
				{
					$errorMessage2 = "Your employee code is incorrect.<br>Please notify your supervisor.";
				}
			
			}
		/* else if ($ecode != "123") 
		{
			$errorMessage = "Your employee code is incorrect.<br>Please notify your supervisor.";
		}*/
		else
		{
			if ($ecode != "123")
			{
				$errorMessage2 = "Your employee code is incorrect.<br>Please notify your supervisor.";
			}
			
			if ($ecode == "123")
			{
			$ecode = '\'admin\'';
			
			// wont register the $ecode
			$SQL = "INSERT INTO users (username, password, userType) VALUES ($uname, md5($pword), $ecode)";
			$result = mysql_query($SQL);

			mysql_close($db_handle);
			
			session_start();
			$_SESSION['login'] = "$uname";

			header ("Location: admindash.php");
			}
		}
	}

}
else
{
	$errorMessage = "Not BEING CONNECTED";
	print ($errorMessage);
}
}
//$handle = popen("c:\\Untitled1.exe", "w");
//print $handle;
?>

	<html>
	<head>
	<title>Register</title>


	</head>
	<body>
<font color="red">
	<?PHP print $errorMessage;?> <br>
	<?PHP print $errorMessage2;?> <br>
</font>
	
<FORM NAME ="form1" METHOD ="POST" ACTION ="adminsignup.php">
	<table>
		<tr>
			<td width="145">
				<b>Username:</b>
			</td>
			<td width="145">
				<INPUT TYPE = 'TEXT' Name ='username'  value="<?PHP 
				$uname = trim($uname , "'");
				print $uname;
				?>" maxlength="20">
			</td>
		</tr>	
		<tr>
			<td width="145">
				<b>Password:</b>
			</td>
			<td width="145">
				<INPUT TYPE = 'password' Name ='password'  value="" maxlength="16">
			</td>
		</tr>
		<tr>
			<td width="145">
				<b>Authorization Code:</b>
			</td>
			<td width="145">
				<INPUT TYPE = 'password' Name ='employeeCode'  value="" maxlength="16">
			</td>
		</tr>
</table>
<P>
<INPUT TYPE = "Submit" Name = "Submit1"  VALUE = "Register">

</FORM>
<P>
<br><br><br><br><br><br><br><br><br>
<p align="center">
<a href="login.php">Return to Login</a>
&nbsp;&nbsp;
<a href="home.php">Return to Home</a>
<?php
include ("footer.php");
?>
</p>
	</body>
	</html>
