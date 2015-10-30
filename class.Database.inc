<?php
class DatabaseConnection
{

    public $dbh = '';
    private $error;

    private $queryStmt;

    function __construct()
    {
        include 'config.inc';
	$this->connect();   
    }
/**
 * Set up and make the connection
 */
    function connect()
    {

	// Set DSN - this line sets for MySQL, change for otehr DB types
        $dsn = 'mysql:host=' . $this->host . ';dbname=' . $this->dbname;
    
        echo "Here is the dsn: $dsn";
    
        //Set options
        $options = array(
    		PDO::ATTR_PERSISTENT => true, // Allows a persistent connection
    		PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION //Throws Exception in the event of an Error
        );
	
        //Create new PDO
	try{
            $this->dbh = new PDO($dsn, $this->user, $this->pass, $options);
            $this->dbh->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);


        }
        catch(PDOException $e){

            echo 'There was an error while trying to connect to the database';
            file_put_contents('connection.errors.txt', $e->getMessage().PHP_EOL,FILE_APPEND);

        }
    }

/**
 * prepare the query
 * @param query $query
 */
    public function query($query){
	echo "<br />This is the query: $query <br />";
	$this->queryStmt = $this->dbh->prepare($query);
    }

/**
 * bind the parameters
 * @param mixed $param
 * @param mixed $value
 * @param int $type
 */
    public function bind($param, $value, $type = null){
	if (is_null($type)) {
		switch (true) {
			case is_int($value):
				$type = PDO::PARAM_INT;
				break;
			case is_bool($value):
				$type = PDO::PARAM_BOOL;
				break;
			case is_null($value):
				$type = PDO::PARAM_NULL;
				break;
			default:
				$type = PDO::PARAM_STR;
		}
		$this->queryStmt->bindValue($param, $value, $type);
		echo "Insert values: $param $value $type <br />";
	}
    }

    public function execute(){
	return $this->queryStmt->execute();
    }

    //Return a result set in the form of an array
    public function resultset(){
	$this->execute();
	return $this->queryStmt->fetchAll(PDO::FETCH_ASSOC);
    }

    //Return a single result
    public function single(){
	$this->execute();
	return $this->queryStmt->fetch(PDO::FETCH_ASSOC);
    }

    //returns the number of rows affected by the last-run DELETE, UPDATE, or INSERT
    public function rowCount(){
	return $this->queryStmt->rowCount();
    }

    //returns the ID of the last INSERT
    public function lastInsertId(){
	return $this->dbh->lastInsertId();
    }

    }
