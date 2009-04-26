<html>
	<body>
<?php
	include ("TopRegion.php");
	include ("db2.php");
	include ("Links.php");
	
	//If a user is Online, Extract the username into a variable
	if (isset($_SESSION['login']))
	{
		$uname = $_SESSION['login'];
	}
?>

<?php
	//Extract the variable from the search.php
	$search = $_GET['search'];
	
	//Checks the search variable matches anything in the database
	$result = mysql_query("SELECT * FROM books WHERE MATCH (title, author) AGAINST ('*$search*' IN BOOLEAN MODE)");
	$num_rows = mysql_num_rows($result);
	
?>	
		<h2>Library Catalog</h2>
		<p> Please add the books that you would like to search for onto the list.
		</p>
		
		<?php
		include ("minisearch.php");
		echo '<b><font color=navy>' . $num_rows . '</font> Results:</b>';
		
		if ($num_rows > 0)
		{
		?>
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
					<h3>Add</h3>
				</font>
			</td>
		</tr>
		
			<?php
			while($row = mysql_fetch_assoc($result)){
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
			
			
			<td width="200" height="10">
				<font face="verdana" size="1" color="black">
					<?php
						if($row["status"]=="Checked In")
						{
							/*
							echo '<a href="list.php?action=add_item&id=';
							$row["bookId"];
							echo '&con=1">Add Item</a>';
							*/
							
							echo '<a href="list.php?action=add_item&id=' . $row["bookId"] . '&con=1">Add Book</a>';
						} else {
						print "Not available";
						}
						
					?>
				</font>
			</td>
			
			
		</tr>
			<tr>
				<td width="100%" colspan="6">
					<hr size="1" color="navy" NOSHADE>
				</td>
			</tr>
<?php
		} //<a href="cart.php">Your Shopping Cart &gt;&gt;</a>
	}
else
{
	echo '
			<br>
			<h3 align= "center">No Results</h3>';
}
?>	
			</table>
			<br><br><br><br>
<?php
include ("footer.php");
?>
		</body>
</html>