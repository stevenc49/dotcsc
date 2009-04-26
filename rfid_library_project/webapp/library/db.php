<?php

// This page contains the connection routine for the
// database as well as getting the ID of the cart, etc

$dbUser = "root";
$dbPass = "";
$dbName = "libraryDB";
$dbServer = "127.0.0.1";

function ConnectToDb($dbServer, $dbUser, $dbPass, $dbName)
{
// Connect to the database and return
// true/false depending on whether or
// not a connection could be made.

$db_handle = mysql_connect($dbServer, $dbUser, $dbPass);
$db_found = mysql_select_db($dbName, $db_handle);

//Enable $db_found in session
$_SESSION['db_found'] = $db_found;

/*if(!$db_handle || !$db_found)
return false;
else
return true; */
}

function GetCartId()
{
// This function will generate an encrypted string and
// will set it as a cookie using set_cookie. This will
// also be used as the cookieId field in the cart table

if(isset($_COOKIE["cartId"]))
{
return $_COOKIE["cartId"];
}
else
{
// There is no cookie set. We will set the cookie
// and return the value of the users session ID

session_start();
setcookie("cartId", session_id(), time() + ((3600 * 24) * 30));
return session_id();
}
}

?>