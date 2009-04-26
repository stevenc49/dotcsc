<html>
<head>
	<title>Checked-Out</title>
</head>

<?PHP
	include ("TopRegion.php");
	include ("db2.php");
	include ("Links.php");
	if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
		header ("Location: home.php");
	}
?>

<?php
$currentUser = $_SESSION['login'];

$result = mysql_query("select title, author, dueDate from books where checkedoutBy=" . $currentUser . "");
$num_rows = mysql_num_rows($result);
//print ("select title, author from books where checkedoutBy=" . $currentUser . ""); //this is a chekc

echo	'		
		<h2>Checked-Out List</h2>
		<p> Here is a list of your checked-out books. <br>
			You have <font color=navy><b>' . $num_rows . '</b></font> books checked-out.
		</p>
		';

if($num_rows > 0)
{

echo 	'	
		<table>
		<tr>
			<td bgcolor="navy" width="330" height="20">
				<font face="verdana" size="1" color="white">
					<h3>Title</h3>
				</font>
			</td>
			<td bgcolor="navy" width="330" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Author</h3>
				</font>
			</td>
			<td bgcolor="navy" width="330" height="10">
				<font face="verdana" size="1" color="white">
					<h3>Due Date</h3>
				</font>
			</td>
		</tr>
	';
	
while($row = mysql_fetch_array($result)){
// Increment the total cost of all items	
	
?>
	<td width="33.3%" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["title"]; ?>
		</font>
	</td>
	
	<td width="33.3%" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["author"]; ?>
		</font>
	</td>
	
	<td width="33.3%" height="10">
		<font face="verdana" size="1" color="black">
			<?php echo $row["dueDate"]; ?>
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
	}
}	
else
{
	echo '
			<br>
			<h3 align= "center">No Books Checked-Out</h3>';
}
echo '</table>';
?>
<br><br><br><br><br>
<?php
include ("footer.php");
?>
</td>
</html>