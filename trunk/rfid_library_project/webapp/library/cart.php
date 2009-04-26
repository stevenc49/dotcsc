<?PHP
session_start();
if (!(isset($_SESSION['login']) && $_SESSION['login'] != '')) {
	header ("Location: login3.php");
}
?>

<?php

$dbUser = "root";
$dbPass = "";
$dbName = "libraryDB";
$dbServer = "127.0.0.1";

// Connect to the database and return
// true/false depending on whether or
// not a connection could be made.

$s = mysql_connect($dbServer, $dbUser, $dbPass);
$d = mysql_select_db($dbName, $s);

	if ($d) {

	print "in";
	}
	else
	{
	print "Not In";
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

switch($_GET["action"])
{
case "add_item":
{
AddItem($_GET["id"], $_GET["qty"]);
ShowCart();
break;
}
case "update_item":
{
UpdateItem($_GET["id"], $_GET["qty"]);
ShowCart();
break;
}
case "remove_item":
{
RemoveItem($_GET["id"]);
ShowCart();
break;
}
default:
{
ShowCart();
}
}

function AddItem($itemId, $qty) {
//This create an error
//function can not detect connection

$dbUser = "root";
$dbPass = "";
$dbName = "cart";
$dbServer = "127.0.0.1";

// Connect to the database and return
// true/false depending on whether or
// not a connection could be made.

$s = mysql_connect($dbServer, $dbUser, $dbPass);
$d = mysql_select_db($dbName, $s);


//tests if connection is a sucess
	if ($d) {

	print "in"; //connection success
	}
	else
	{
	print "Not In"; //connection fail
	}
$result = mysql_query("select count(*) from cart where cookieId = '" . GetCartId() . "' and itemId = $itemId");
$row = mysql_fetch_row($result);
$numRows = $row[0];

//tests if connection is a sucess
	if ($d) {

	print "in"; //connection success
	}
	else
	{
	print "Not In"; //connection fail
	}

if($numRows == 0)
{
// This item doesn't exist in the users cart,
// we will add it with an insert query

//This also creates an error
//Is the problem that it can't access to the database?
mysql_query("insert into cart(cookieId, itemId, qty) values('" . GetCartId(). "', $itemId, $qty)");
}
else
{
// This item already exists in the users cart,
// we will update it instead
UpdateItem($itemId, $qty);
}
}
function UpdateItem($itemId, $qty) {
mysql_query("update cart set qty = $qty where cookieId = '" . GetCartId() . "' and itemId = $itemId");
}
function RemoveItem($itemId) {
mysql_query("delete from cart where cookieId = '" . GetCartId() . "' and itemId = $itemId");
}
?>

<?php
function Showcart() { //still work in process

$dbUser = "root";
$dbPass = "";
$dbName = "cart";
$dbServer = "127.0.0.1";

$s = mysql_connect($dbServer, $dbUser, $dbPass);
$d = mysql_select_db($dbName, $s);

//tests if connection is a success
	if ($d) {

	print "in"; //connection success
	}
	else
	{
	print "Not In"; //connection fail
	}

print "hi";

$result = mysql_query("select * from cart inner join items on cart.itemId = items.itemId where cart.cookieId = '" . GetCartId() . "' order by items.itemName asc");
while($row = mysql_fetch_array($result)){
// Increment the total cost of all items

?>
<tr>
	<td width="15%" height="25">
		<font face="verdana" size="1" color="black">
			<select name="<?php echo $row["itemId"]; ?>" onChange="UpdateQty(this)">
				<?php
				for($i = 1; $i <= 20; $i++)
				{
				echo "<option ";
				if($row["qty"] == $i)
				{
				echo " SELECTED ";
				}
				echo ">" . $i . "</option>";
				}
				?>
			</select>
		</font>
	</td>
<td width="55%" height="25">
	<font face="verdana" size="1" color="black">
		<?php echo $row["itemName"]; ?>
	</font>
</td>
<td width="20%" height="25">
<font face="verdana" size="1" color="black">
<?php echo number_format($row["itemPrice"], 2, ".", ","); ?>
</font>
</td>
<td width="10%" height="25">
<font face="verdana" size="1" color="black">
<a href="cart.php?action=remove_item&id=<?php echo $row["itemId"]; ?>">Remove</a>
</font>
</td>
</tr>


<tr>
<td width="100%" colspan="4">
<hr size="1" color="red" NOSHADE>
</td>
</tr>
<tr>


</tr>

<?php
}


}


?>
<td width="70%" colspan="2">
<font face="verdana" size="1" color="black">
<a href="catalog.php">&lt;&lt; Keep Shopping</a>
</font>
</td>
