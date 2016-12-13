<?php   #flight.php for airport example fall 2014
    //When you select the publishers name from the drop down you will get the list of books published by him
    $page_title = 'Books and Publishers';
	include('header.html');
	require ('pdoConn.php');
	//$conn is the name of the db in the pdoConn.php file
	$sql = "SELECT PublisherName from Publisher";
	echo '<h3>Publisher Name</h3>';
	echo '<form action="publist.php" method="post">';
	echo '<select name= "fn">';
	echo '<option value="  " selected="true">  </option>';
	foreach($conn->query($sql) as $row)
	{
		echo '<option value = "';
		echo $row['PublisherName'];
		echo ' "> ';
		echo $row['PublisherName'];
		echo '</option>';
	}// end foreach
	echo '</select>';
	echo '<br><br><input type="submit" name="submit" value="List"><br>';
	echo '</form>';
	//now to check if the submit button has been clicked
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		$flit = $_POST['fn'];
		echo '<center>';
		echo ' Books published by '.$flit;
		echo '</center>';
		echo '<br><br>';
		$sql2 = "select * from Book where PublisherCode=(select PublisherCode from Publisher where PublisherName=?)";
		$stmt = $conn->prepare($sql2);
		$stmt->execute(array($flit));
		$rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
		echo '<center>List of books</center>';
		echo '<table border="1" align="center">';
		echo '<tr>
		         <td> BookCode       </td>
				 <td> Title          </td>
				 <td> PublisherCode  </td>
				 <td> Type           </td>
				 <td> Price          </td>
                 <td> Paperback      </td>
			  </tr> <br> ';
		foreach($rows as $r)
		{
			echo '<tr><td>'.$r['BookCode'];
			echo '</td><td>'.$r['Title'];
			echo '</td><td>'.$r['PublisherCode'];
			echo '</td><td>'.$r['Type'];
			echo '</td><td>'.$r['Price'];
			echo '</td><td>'.$r['Paperback'];
			echo ' </td></tr><br>';
		}//end foreach
		echo '</table>';
	}//end if request method
	//include ('includes/footer.html');
	    echo '<br><br><br><br><br><br><br><br><br><br>';
        echo '<h3> <center> Aravinda Krishnan V </center> </h3>';
		echo '<center> <b> Section </b> 566-3 ; <b> Tu Th </b> 2:00pm-3:15pm</center>';
?>
