<?php
	$db=new Database();
	//Sinon les caractères accentués ne passent pas avec json_encode et toute la valeur est mise à null 
	$query="SET CHARACTER SET utf8";
	$db->setQuery($query);
	$db->query();
	$param='';
	if(isset($_GET["title"]) && $_GET["title"]!=""){
		$param.='titre LIKE "%'.$_GET["title"].'%"';
	}
	
	
	if(isset($_GET["year"]) && $_GET["year"]!=-1 && $_GET["year"]!=""){
		if($param!=""){
			$param.=" AND ";
		}
		if(isset($_GET["yearPrecision"]) && $_GET["yearPrecision"]!="" && $_GET["yearPrecision"]!="-1"){
			if($param!="")
				$param.=" AND ";
			$param.="annee BETWEEN ".($_GET["year"]- $_GET["yearPrecision"])." AND ".($_GET["year"]+ $_GET["yearPrecision"]);
		}else{		
			$param.="annee=".$_GET["year"];
		}
	}
	if(isset($_GET['time']) && $_GET['time']!=-1 && $_GET['time']!=""){
		if($param!="")
			$param.=" AND ";
		if(isset($_GET["timePrecision"]) && $_GET["timePrecision"]!="" && $_GET["timePrecision"]!="-1"){
			if($param!="")
				$param.=" AND ";
			$param.="duree BETWEEN ".($_GET["time"]- $_GET["timePrecision"])." AND ".($_GET["time"]+ $_GET["timePrecision"]);
		}else{		
			$param.="duree=".$_GET['time'];
		}
		
	}
	if($param!=""){
	
		$query="SELECT td_film.id_film,titre,duree,annee,image FROM td_film
		WHERE ".$param;
		$db->setQuery($query);
		$db->query();
		$res = $db->loadAssocList();
		//print_r(sizeof($res));
		for ($i=0;$i<sizeof($res);$i++){
			$actor_query="SELECT nom_acteur,prenom_acteur FROM td_acteur NATURAL JOIN td_film_has_acteur
			WHERE td_film_has_acteur.id_acteur=td_acteur.id_acteur AND id_film=".$res[$i]['id_film'];
			$db->setQuery($actor_query);
			$db->query();
			$actor_res=$db->loadAssocList();
			$res[$i]["actor"]=$actor_res;
			
			$genre_query="SELECT genre FROM td_genre NATURAL JOIN td_film_has_genre
			WHERE td_film_has_genre.id_genre=td_genre.id_genre AND id_film=".$res[$i]['id_film'];
			$db->setQuery($genre_query);
			$db->query();
			$genre_res=$db->loadAssocList();
			$res[$i]["genre"]=$genre_res;
			
			$director_query="SELECT nom_realisateur,prenom_realisateur FROM td_realisateur NATURAL JOIN td_film_has_realisateur
			WHERE td_film_has_realisateur.id_realisateur=td_realisateur.id_realisateur AND id_film=".$res[$i]['id_film'];
			$db->setQuery($director_query);
			$db->query();
			$director_res=$db->loadAssocList();
			$res[$i]["director"]=$director_res;
			
		}
		//print_r($res);
		if($res!=null){
			echo utf8_encode(json_encode($res));
		}
	}
	else
		$query="SELECT titre,duree,annee,image FROM td_film";
	
	

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
		$this->_user = "poudet";
		$this->_password = "6fcf0004";
		$this->_db = "poudet";
		
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