<?php
//For the top region of the page
//Start Session
session_start();

//Display UBC Header Logo
echo '<a href="home.php"><img src="img/Header.jpg" width="100%" border=0><a>';

//Determines if a User is Online or Offline
if (isset($_SESSION['login']))
{
	//Extract Username
	$login = $_SESSION['login'];
	
	//Removes quotiations
	$login = trim($_SESSION['login'], "'");
	
	//Display on the top left of the page
	echo '<p align="right"> Welcome <b>' . $login . '</b>! <a href="logout.php">Log Out</a></p>';
} 
else if (!isset($_SESSION['login']))
{
	echo '<p align="right"><a href="login.php">Log In</a>   <a href="signup.php">Sign Up</a></p>';
}
?>