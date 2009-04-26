<html>
<head>
	<title>Transfer List</title>
</head>
<?php
	include ("TopRegion.php");
if (isset($_SESSION['login']))
{
	$uname = $_SESSION['login'];
}
include ("db2.php");
include ("Links.php");

function bookListId()
{
	// This function will generate an encrypted string and
	// will set it as a cookie using set_cookie. This will
	// also be used as the cookieId field in the cart table

	if(isset($_COOKIE["bookListId"]))
	{
		return $_COOKIE["bookListId"];
	}
	else
	{
		// There is no cookie set. We will set the cookie
		// and return the value of the users session ID

		session_start();
		setcookie("bookListId", session_id(), time() + ((3600 * 24) * 30));
		return session_id();
	}
}

switch($_GET["action"])
{
case "add_item":
{
AddItem($_GET["id"], $_GET["con"]);
ShowCart();
break;
}
case "update_item":
{
UpdateItem($_GET["id"], $_GET["con"]);
ShowCart();
break;
}
case "remove_item":
{
RemoveItem($_GET["id"]);
ShowCart();
break;
}
case "remove_all":
{
RemoveAll();
ShowCart();
break;
}
default:
{
ShowCart();
}
}

function AddItem($bookId, $container) {
//This create an error
//function can not detect connection

$dbUser = "root";
$dbPass = "";
$dbName = "libraryDB";
$dbServer = "127.0.0.1";

// Connect to the database and return
// true/false depending on whether or
// not a connection could be made.

$s = mysql_connect($dbServer, $dbUser, $dbPass);
$d = mysql_select_db($dbName, $s);

$result = mysql_query("select count(*) from list where cookieId = '" . bookListId() . "' and bookId = $bookId");
$row = mysql_fetch_row($result);
$numRows = $row[0];

if($numRows == 0)
{
// This item doesn't exist in the users cart,
// we will add it with an insert query

//This also creates an error
//Is the problem that it can't access to the database?
mysql_query("insert into list(cookieId, bookId, container) values('" . bookListId(). "', $bookId, $container)");
}
else
{
// This item already exists in the users cart,
// we will update it instead
print "Book already exists! ";
echo "<br>";
}
}
function UpdateItem($itemId, $qty) { // will be removed
mysql_query("update list set qty = $qty where cookieId = '" . bookListId() . "' and itemId = $itemId");
}
function RemoveItem($bookId) {
mysql_query("delete from list where cookieId = '" . bookListId() . "' and bookId = $bookId");
}
function RemoveAll() {
mysql_query("TRUNCATE TABLE list");
}
?>

<?php
function Showcart() { //still work in process

$dbUser = "root";
$dbPass = "";
$dbName = "libraryDB";
$dbServer = "127.0.0.1";

$s = mysql_connect($dbServer, $dbUser, $dbPass);
$d = mysql_select_db($dbName, $s);

$result = mysql_query("select * from list inner join books on list.bookId = books.bookId where list.cookieId = '" . bookListId() . "' order by books.title asc");
$num_rows = mysql_num_rows($result);
echo 	'	
		
		<h2>Book List</h2>
		<p> Please confirm that this is the list of books that you would like to find. <br>
			When completed, press the "Transfer List to Handheld" button. <br>
			There ';
		if($num_rows == 0)
			{
			echo 'are no book entires.';
			}
				if ($num_rows)
					{
					if ($num_rows == 1)
					{
						echo 'is';
					} else if($num_rows > 1){
						echo 'are';
					}
			echo		'	
						<font color=navy><b>' . $num_rows . '</b></font> 
						book 
						';
					if ($num_rows == 1)
					{
						echo 'entry';
					} else if($num_rows > 1)
					{
						echo 'entries'; 
					}
			echo		' in the list.
						</p>
					';
					}
if ($num_rows > 0)
{		
echo	'
		<table>
		<tr>
			<td bgcolor="navy" width="200" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Title</h3>
				</font>
			</td>
			<td bgcolor="navy" width="200" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Author</h3>
				</font>
			</td>
			<td bgcolor="navy" width="200" height="10">
				<font face="verdana" size="1" color="white">
					<h3>ISBN</h3>
				</font>
			</td>
			<td bgcolor="navy" width="200" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Call Number</h3>
				</font>
			</td>
			<td bgcolor="navy" width="200" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Status</h3>
				</font>
			</td>
			<td bgcolor="navy" width="200" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Remove</h3>
				</font>
			</td>
		</tr>
	';
	

while($row = mysql_fetch_array($result)){
// Increment the total cost of all items

?>
	
	
	
	<tr>
	
	<td width="200" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["title"]; ?>
		</font>
	</td>
	
	<td width="200" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["author"]; ?>
		</font>
	</td>
	
	<td width="200" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["isbn"]; ?>
		</font>
	</td>
	
	<td width="200" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["callNum"]; ?>
		</font>
	</td>
	
	<td width="200" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["status"]; ?>
		</font>
	</td>
	
	<td>
	<font face="verdana" size="1" color="black">
		<a href="list.php?action=remove_item&id=<?php echo $row["bookId"]; ?>">Remove</a>
	</font>
	</td>
	</tr>
	

	<tr>
		<td width="100%" colspan="6">
			<hr size="1" color="navy" NOSHADE>
		</td>
	</tr>
<tr>


</tr>


<?php
	//Session Variable to Extract the bookID for C_ALL (Clear ALL)
	$_SESSION['bookId'] = $row["bookId"];
}

	echo '</table>';
	echo '
		<form action="transfer.php" method="post">	
			<INPUT TYPE= "SUBMIT" Name = "transfer" VALUE="Transfer List to Handheld">
		</form>
		<a href="list.php?action=remove_all"><font size="2">Clear All</a></font>
		';
	}
else
{
	echo '
			<br>
			<h3 align= "center">No List Entry</h3>';
}
}
?>



<?PHP
/*
$port = mysql_query("select books.bookid from list inner join books on list.bookId = books.bookId where list.cookieId = '" . bookListId() . "' order by books.title asc");

while ($transfer = mysql_fetch_assoc($port)) {
$file_handle = fopen("Transfer.txt", "a");
$file_contents = $transfer["bookid"];
fwrite($file_handle, $file_contents);
}
fclose($file_handle);
*/
?>
</td>
<br><br><br><br><br>
<?php
include ("footer.php");
?>
</html>
