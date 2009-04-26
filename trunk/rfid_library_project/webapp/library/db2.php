<?php

// This page contains the connection routine for the
// database as well as getting the ID of the cart, etc

$dbUser = "root";
$dbPass = "";
$dbName = "libraryDB";
$dbServer = "127.0.0.1";

// Connect to the database and return
// true/false depending on whether or
// not a connection could be made.

$db_handle = mysql_connect($dbServer, $dbUser, $dbPass);
$db_found = mysql_select_db($dbName, $db_handle);

?>