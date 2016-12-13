<?php   #destination.php for airport example fall 2014
    //When you enter the Authors last name you will get the list of books written by him
    $page_title = 'Author Name';
	include ('header.html');
	require ('pdoConn.php');
	//$conn is the name of the db in the pdoConn.php file
	echo '<form method="post">';
	echo '<br>Enter the Author Last Name ';
	echo '<input type="text" name="go" id="go"><br>';
	echo '<br><input type="submit" name="submit" value="List"><br>';
	echo '</form>';
	//now to check if the submit button has been clicked
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		$dest = trim($_POST['go']);
		echo '<br>';
		$sql2 = "select * from Book where Bookcode in (select BookCode from Wrote where AuthorNum=(select AuthorNum from Author where AuthorLast= ? ));";
		$stmt = $conn->prepare($sql2);
		$stmt->execute(array($dest));
		$cnt = $stmt->rowCount();
		$rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

		echo '<center>List of books </center>';
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
			echo '<tr><td> '.$r['BookCode'];
			echo '</td><td>'.$r['Title'];
			echo '</td><td>'.$r['PublisherCode'];
			echo '</td><td>'.$r['Type'];
			echo '</td><td>'.$r['Price'];
			echo '</td><td>'.$r['Paperback'];
			echo ' </td></tr><br>';
		}//end foreach
		echo '</table>';	
	}//end if request method
	    echo '<br><br><br><br><br><br><br><br><br><br><br><br>';
        echo '<h3> <center> Aravinda Krishnan V </center> </h3>';
		echo '<center> <b> Section </b> 566-3 ; <b> Tu Th </b> 2:00pm-3:15pm</center>';
?>
