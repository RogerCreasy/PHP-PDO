<?php

//testing vars
//TODO: get these as input from a form submission
$fname = 'Quark';
$lname = 'Barkeep';
$clock = '2:34';
$page = 'D12';
$date = '12/30/2011';

//Include the config SET THE PATH TO MATCH YOUR LOCATION
//the config file should be placed outside of your web root
Include 'config.inc';
echo "We got the config: $pass";

//Include the database class
Include 'class.Database.inc';

//Instantiate an object of the class
$mySQL = new DatabaseConnection;

//set the db connection varrs
$mySQL->host = $host;
$mySQL->user = $user;
$mySQL->pass = $pass;
$mySQL->dbname = $dbname;

//set up the connection
$mySQL->connect();

//set up the PDO prepare, bind the vars
$mySQL->query("INSERT INTO testtable(fname, lname, time, page, date) VALUES(:fname, :lname, :clock, :page, :date)");
$mySQL->bind(':fname', $fname);
$mySQL->bind(':lname', $lname);
$mySQL->bind(':clock', $clock);
$mySQL->bind(':page', $page);
$mySQL->bind(':date', $date);

$mySQL->execute();
