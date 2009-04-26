<?php

function dateDiff($dformat, $endDate, $beginDate)
{
$date_parts1=explode($dformat, $beginDate);
$date_parts2=explode($dformat, $endDate);
$start_date=gregoriantojd($date_parts1[2], $date_parts1[1], $date_parts1[0]);
$end_date=gregoriantojd($date_parts2[2], $date_parts2[1], $date_parts2[0]);
return $end_date - $start_date;
}

    $date1="2008-9-11";
    $date2="2008-7-11";

	$todayDate = date("Y-m-d");
	print $todayDate;
	echo "<br>";
	
    //echo "New Formatted date is ". $todayDate->format("Y-m-d\TH:i:s\Z");
	
    print "If we minus " . $date1 . " from " . $date2 . " we get " . dateDiff("-", $date2, $date1) . ".";



?>