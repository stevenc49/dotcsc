<html>
	<body>
	
		<?php
		//Links To Alternative Pages
		?>
		<p align="center">
		<a href="home.php">Home</a>
		&nbsp;&nbsp;
		<a href="search.php">Search</a>
		&nbsp;&nbsp;
		<a href="list.php?action=">List</a>
		
		<?php
		//TopRegion.php is required
		//TopRegion.php contains the code session_start();
		
		// Checks if $_SESSION['login']; is true
		if (isset($_SESSION['login']))
		{
		echo '&nbsp;&nbsp;';
		echo '<a href="checkout.php">Checked-Out</a>';
		}
		
		//If MySQL database was found
		if ($db_found)
		{
			//Checks if an User is Online
			if (isset($_SESSION['login']))
			{
				//Sending a Query to MySQL
				//Extracts the usertype if the username = $currentUser
			
				$currentUser = $_SESSION['login'];
				$SQL ="SELECT usertype FROM users where username = $currentUser";
				$result = mysql_query($SQL);
				$admin = mysql_fetch_array($result);
				$ifadmin = $admin["usertype"];

				//If usertype is 'admin'
				if ($ifadmin == 'admin')
				{
					echo '&nbsp;&nbsp;&nbsp;&nbsp;';
					echo '<a href="admindash.php">Admin Dashboard</a>';
				}
			}
		}
		?>
		</p>
		<br>
		<h4 align="center"> Administrator Tools</h4>
		<p align="center">
		<a href="addbook.php">Add Book</a>
		&nbsp;&nbsp;
		<a href="adminCatalog.php?action=">Catalog Management</a>
		&nbsp;&nbsp;
		<a href="misplaced.php?action=">Misplaced</a>
		</p>
		
		
	</body>
</html>