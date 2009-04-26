
<?PHP
$title = "";
$errorMessage = "";

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
	$title = $_POST['title'];
	$title = htmlspecialchars($title);

//test to see if $errorMessage is blank
//if it is, then we can go ahead with the rest of the code
//if it's not, we can display the error

	//====================================================================
	//	Write to the database
	//====================================================================
}
//"list.php?action=add_item&id=' . $row["bookId"] . '"

?>

	<html>
	<head>
	<title>Search</title>


	</head>
	<body>

	
<FORM NAME ="form1" METHOD ="GET" ACTION ="catalog.php?search=<?php echo $title;?>" >

Search: <INPUT TYPE = 'TEXT' Name ='search'  value="" maxlength="500"> 

<INPUT TYPE = "Submit" Name = "Submit1"  VALUE = "Search">



</FORM>
<P>

<?PHP print $errorMessage;?>

	</body>
	</html>