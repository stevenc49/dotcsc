<?PHP
include ("TopRegion.php");
include ("db2.php");
include ("adminLinks.php");
if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
	header ("Location: home.php");
}


	// This page will list all of the items
	// from the items table. Each item will have
	// a link to add it to the cart

	//Sending a Query to MySQL DB
	$result = mysql_query("
	select misplacedid, title, shelf.shelfnum, lastscanned
	from misplaced, books, shelf
	where misplaced.booktagnum = books.booktagnum 
	and misplaced.foundatshelf=shelf.shelftagnum
	");
	$num_rows = mysql_num_rows($result);
	
	//print_r($_GET);
	switch($_GET["action"])
	{
		case "remove_item":
		{
			RemoveItem($_GET["id"]);
			header("Location: misplaced.php?action=");
			break;
		}
		case "remove_all":
		{
			RemoveAll();
			header("Location: misplaced.php?action=");
			break;
		}
		default:
		{
		}
	}

	function RemoveItem($misplacedid) {
		mysql_query("delete from misplaced where misplaced.misplacedid = $misplacedid");
	}
	function RemoveAll() {
		mysql_query("truncate table misplaced");
	}

?>
<html>
	<head>
		<title>Misplaced Books</title>
	</head>
	<body>
		<h2>Misplaced</h2>
		<p> The following are books that have been misplaced.<br>
			Please return the books to their proper location and then click the link when resolved. <br>
<?php
if ($num_rows > 0)
	{
?>
		<table>
		
		<tr>
			<td bgcolor="navy" width="15%" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Title</h3>
				</font>
			</td>
			<td bgcolor="navy" width="10%" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Shelf Found At</h3>
				</font>
			</td>
			<td bgcolor="navy" width="40%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Last Scanned</h3>
				</font>
			</td>
			<td bgcolor="navy" width="35%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Resolve</h3>
				</font>
			</td>
		</tr>
		
			<?php
			while($row = mysql_fetch_assoc($result)){
			?>

		<tr>
			<tr>
				<td width="35%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["title"]; ?>
				</font>
			</td>
				<td width="10%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["shelfnum"]; ?>
				</font>
			</td>
				<td width="40%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["lastscanned"]; ?>
				</font>
			</td>				
			<td width="35%" height="10">
				<font face="verdana" size="1" color="black">
					<?php
						echo '<a href="misplaced.php?action=remove_item&id=' . $row["misplacedid"] . '">Click here when resolved</a>';
					?>
				</font>
			</td>
		</tr>
			<tr>
				<td width="100%" colspan="12">
					<hr size="1" color="navy" NOSHADE>
				</td>
			</tr>
<?php
	}
}
else
{
	echo '
			<br>
			<h3 align= "center">No Misplaced Book</h3>';
}
?>	
			</table>
			<a href="misplaced.php?action=remove_all"><font size="2">Clear All</a></font>
			<br>
<?php
include ("footer.php");
?>
		</body>
</html>