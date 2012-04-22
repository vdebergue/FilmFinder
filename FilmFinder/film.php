<?php
	$db=new Database();
	//Sinon les caractères accentués ne passent pas avec json_encode et toute la valeur est mise à null 
	$query="SET CHARACTER SET utf8";
	$db->setQuery($query);
	$db->query();
	$param='';
	if(isset($_GET["title"]) && $_GET["title"]!=""){
		$param.='titre="'.$_GET["title"].'"';
	}
	/*if(isset($_GET["actor"]) && $_GET["actor"]!=""){
		$param.='actor="'.$_GET["actor"].'"';
	}
	if(isset($_GET["title"]) && $_GET["title"]!=""){
		$param.='titre="'.$_GET["title"].'"';
	}*/
	if(isset($_GET["year"]) && $_GET["year"]!=-1 && $_GET["year"]!=""){
		$param.="annee=".$_GET["year"];
	}
	if(isset($_GET['time']) && $_GET['time']!=-1 && $_GET['time']!=""){
		$param.="duree=".$_GET['time'];
	}
	if($param!=""){
		$query="SELECT titre,duree,annee,image FROM td_film WHERE ".$param;
		$db->setQuery($query);
		$db->query();
		$res = $db->loadAssocList();
		if($res!=null){
			echo json_encode($res);
		}
	}
	else
		$query="SELECT titre,duree,annee,image FROM td_film";
	
	


// function defination to convert array to xml
function array_to_xml($info, &$xml) {
    foreach($info as $key => $value) {
		//$xml->addChild("film","$value");
        if(is_array($value)) {
            if(!is_numeric($key)){
                $subnode = $xml->addChild("$key");
                array_to_xml($value, $subnode);
            }
            else{
				$subnode = $xml->addChild("film");
                array_to_xml($value, $subnode);
            }
        }
        else {
            $xml->addChild("$key","$value");
        }
    }
}

class Database
{
	var $_host;
	var $_user;
	var $_password;
	var $_db;
	var $_query;
	var $_dbc; // DataBaseConnect
	var $_result;
	
	function __construct()
	{
		$this->_host = "localhost"; 
		$this->_user = "root";
		$this->_password = "";
		$this->_db = "filmfinder";
		
		$this->_dbc = mysqli_connect( $this->_host, $this->_user, $this->_password, $this->_db ) or die("Impossible de se connecter Ã  la base de donnees". mysqli_connect_error());
	}
	
	function setQuery($query)
	{
		$this->_query = $query;	
	}
	
	function query()
	{
		// Take a local copy so that we don't modify the original query and cause issues later
		$query = $this->_query;
		
		$this->_result = mysqli_query( $this->_dbc, $query );
		if (!$this->_result)
		{
			die("bad query: ".$query);
			return false;
		}
		return $this->_result;
	}
	
	/**
	 * Description
	 *
	 * @access	public
	 * @return int The number of rows returned from the most recent query.
	 */
	function getNumRows( $cur=null )
	{
		return mysqli_num_rows( $cur ? $cur : $this->_result );
	}

	/**
	 * This method loads the first field of the first row returned by the query.
	 *
	 * @access	public
	 * @return The value returned in the query or null if the query failed.
	 */
	function loadResult()
	{
		if (!($cur = $this->query())) {
			return null;
		}
		$ret = null;
		if ($row = mysqli_fetch_array( $cur )) {
			$ret = $row[0];
		}
		mysqli_free_result( $cur );
		return $ret;
	}

	/**
	 * Load an array of single field results into an array
	 *
	 * @access	public
	 */
	function loadResultArray($numinarray = 0)
	{
		if (!($cur = $this->query())) {
			return null;
		}
		$array = array();
		while ($row = mysqli_fetch_array( $cur )) {
			$array[] = $row[$numinarray];
		}
		mysqli_free_result( $cur );
		return $array;
	}

	/**
	* Fetch a result row as an associative array
	*
	* @access	public
	* @return array
	*/
	function loadAssoc()
	{
		if (!($cur = $this->query())) {
			echo "null";
			return null;
		}
		$ret = null;
		if ($array = mysqli_fetch_array( $cur, MYSQLI_ASSOC )) {
			$ret = $array;
		}
		mysqli_free_result( $cur );
		return $ret;
	}

	/**
	* Load a assoc list of database rows
	*
	* @access	public
	* @param string The field name of a primary key
	* @return array If <var>key</var> is empty as sequential list of returned records.
	*/
	function loadAssocList( $key='' )
	{
		if (!($cur = $this->query())) {
			return null;
		}
		$array = array();
		while ($row = mysqli_fetch_array( $cur, MYSQLI_ASSOC )) {
			//$array['film']=array();
			if ($key) {
				$array[$row[$key]] = $row;
			} else {
				$array[] = $row;
			}
		}
		mysqli_free_result( $cur );
		return $array;
	}
}

?>