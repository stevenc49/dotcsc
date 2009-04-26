<?PHP
echo '<a href="home.php"><img src="img/Header.jpg" width="100%" border=0></a>';

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
				$_SESSION['login'] = "1";
				header ("Location: catalog.php");
			}
			else {
				session_start();
				$_SESSION['login'] = "";	//TODO: fix bug when incorrect login, './'surrounds login
				$errorMessage = "<br>Login incorrect.";
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
<title>Home</title>
</head>
<body>

<center>

<h1>Welcome to the UBC Library Interface!</h1></center>
<br>
<p align="center">
To access your choice, click on the on following icons:
</p>
<br>
<p align="center">
<a href="search.php"><img src="img/searchicon2.jpg" height=50 width=50 border=0></img></a> <b> Searching and transfering books </b>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<a href="login.php"><img src="img/loginimg2.jpg" height=50 width=50 border=0></img></a> <b> User Login </b>
</p>
	<br><br><br><br><br><br>
<?php
include ("footer.php");
?>
</body>
</html>