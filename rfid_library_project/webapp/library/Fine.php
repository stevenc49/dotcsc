<html>
	<body>
	<?php
	include ("TopRegion.php");
	include ("db2.php");
	include ("Links.php");
	
function dateDiff($dformat, $endDate, $beginDate)
{
$date_parts1=explode($dformat, $beginDate);
$date_parts2=explode($dformat, $endDate);
$start_date=gregoriantojd($date_parts1[0], $date_parts1[1], $date_parts1[2]);
$end_date=gregoriantojd($date_parts2[0], $date_parts2[1], $date_parts2[2]);
return $end_date - $start_date;
}
	
	$dueDate = "";
	$todayDate = "";
	$NoD = ""; // Number of Days
	$a = "";
	
	//MySQL Query to Extract the dueDate from the Online User
	$SQL = "SELECT dueDate FROM books WHERE checkedoutBy = 'admin'"; //SQL statement works; replace 'admin' with $_SESSION['login']
	$result = mysql_query($SQL);
	$dueDate = mysql_fetch_array($result);
	
	//Today's date
	$todayDate = date("d-m-Y");
	print $todayDate;
	echo "<br>";
	
    print dateDiff("-", $todayDate->format("d-m-Y"), "01-11-2008");
	
	?>
	</body>
</html>