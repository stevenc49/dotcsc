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
	$result = mysql_query("select * from books order by title");
	
	//print_r($_GET);
	switch($_GET["action"])
	{
		case "check_in":
		{
			ChangeToCheckIn($_GET["id"]);
			header("Location: adminCatalog.php?action=");
			break;
		}
		case "check_out":
		{
			//ChangeToCheckOut($_GET["id"]);
			getBookId($_GET["id"]);
			header("Location: manualCheckout.php");
			break;
		}
		case "remove_item":
		{
			RemoveItem($_GET["id"]);
			header("Location: adminCatalog.php?action=");
			break;
		}
		default:
		{
		}
	}

	function ChangeToCheckIn($bookId) {
		mysql_query("UPDATE books SET status=\"Checked In\" WHERE bookid=$bookId");
		mysql_query("UPDATE books SET checkedoutBy=\"\" WHERE bookid=$bookId");
		mysql_query("UPDATE books SET dueDate=\"\" WHERE bookid=$bookId");
	}
	function getBookId($bookId) {
		$_SESSION['bookId'] = "$bookId";
	}
	function ChangeToCheckOut($bookId) {
		mysql_query("UPDATE books SET status=\"Checked Out\" WHERE bookid=$bookId");
	}
	function RemoveItem($bookId) {
		mysql_query("delete from books where bookId = $bookId");
	}

	
?>
<html>
	<head>
		<title>Admin Catalog</title>
	</head>
	<body>
		<h2>Catalog Management</h2>
		<p> You may check in/check out books from this page <br>
			You may also delete books from the library's database here </p>
		
		<table>
		
		<tr>
			<td bgcolor="navy" width="14.6%" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Title</h3>
				</font>
			</td>
			<td bgcolor="navy" width="10.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Author</h3>
				</font>
			</td>
			<td bgcolor="navy" width="1%" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Shelf Number</h3>
				</font>
			</td>
			<td bgcolor="navy" width="13.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>ISBN</h3>
				</font>
			<td bgcolor="navy" width="13.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Call Number</h3>
				</font>
			</td>
				</font>
			</td>
			<td bgcolor="navy" width="10.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Status</h3>
				</font>
			</td>
			<td bgcolor="navy" width="12.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Checked out by</h3>
				</font>
			</td>
			<td bgcolor="navy" width="12.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Due Date</h3>
				</font>
			</td>
			<td bgcolor="navy" width="14.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Check in/out</h3>
				</font>
			</td>
			<td bgcolor="navy" width="16.6%" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Delete Book</h3>
				</font>
			</td>
		</tr>
		
			<?php
			while($row = mysql_fetch_assoc($result)){
			?>

		<tr>
			<tr>
			<td width="14.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["title"]; ?>
				</font>
			</td>
			<td width="10.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["author"]; ?>
				</font>
			</td>
			<td width="1.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["shelfNum"]; ?>
				</font>
			</td>
			<td width="13.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["isbn"]; ?>
				</font>
			</td>		
			<td width="13.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["callNum"]; ?>
				</font>
			</td>
			<td width="10.6" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["status"]; ?>
				</font>
			</td>
			
			<td width="12.6" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["checkedoutBy"]; ?>
				</font>
			</td>
			
			<td width="12.6" height="10">
				<font face="verdana" size="1" color="black">
					<?php echo $row["dueDate"]; ?>
				</font>
			</td>
			
			<td width="14.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php
						//echo $row["status"];
						if( $row["status"]=="Checked In")
						{
							echo '<a href="adminCatalog.php?action=check_out&id=' . $row["bookId"] . '">Change to check out</a>';
						}
						else if( $row["status"]=="Checked Out")
						{
							echo '<a href="adminCatalog.php?action=check_in&id=' . $row["bookId"] . '">Change to check in</a>';
						}
						else
						{
							print "Error: book neither checked in or out";
						}
					?>
				</font>
			</td>
			
			<td width="16.6%" height="10">
				<font face="verdana" size="1" color="black">
					<?php
						if($row["status"]=="Checked In")
						{
							/*
							echo '<a href="list.php?action=add_item&id=';
							$row["bookId"];
							echo '&con=1">Add Item</a>';
							*/
							
							//echo '<a href="list.php?action=add_item&id=' . $row["bookId"] . '&con=1">Add Book</a>';
							echo '<a href="adminCatalog.php?action=remove_item&id=' . $row["bookId"] . '">Delete Book</a>';
						} else {
						print "Not available";
						}
						
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
	} //<a href="cart.php">Your Shopping Cart &gt;&gt;</a>
?>	
			</table>
			<br><br>
<?php
include ("footer.php");
?>
		</body>
</html>