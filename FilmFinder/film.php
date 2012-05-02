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
		if($param!="")
			$param.=" AND ";
		$array=explode($_GET["actor"]," ");
		$param.='actor="'.$_GET["actor"].'"';
	}*/
	/*if(isset($_GET["title"]) && $_GET["title"]!=""){
		if($param!="")
			$param.=" AND ";
		$param.='titre="'.$_GET["title"].'"';
	}*/
	if(isset($_GET["year"]) && $_GET["year"]!=-1 && $_GET["year"]!=""){
		if($param!="")
			$param.=" AND ";
		$param.="annee=".$_GET["year"];
	}
	if(isset($_GET['time']) && $_GET['time']!=-1 && $_GET['time']!=""){
		if($param!="")
			$param.=" AND ";
		$param.="duree=".$_GET['time'];
	}
	if($param!=""){
	
		///Je pense qu'il ne faut pas faire une jointure mais plutot juste les films et pour chaque film créer un tableau ds le tableau pour les acteurs et réalisateurs
		/*$query="SELECT titre,duree,annee,image,nom_acteur,prenom_acteur,nom_realisateur,prenom_realisateur,genre FROM td_film NATURAL JOIN td_acteur,td_film_has_acteur ,td_genre,td_film_has_genre,
		td_realisateur,td_film_has_realisateur
		WHERE td_film_has_acteur.id_film=td_film.id_film AND td_film_has_acteur.id_acteur=td_acteur.id_acteur AND 
		td_film_has_realisateur.id_film=td_film.id_film AND td_film_has_realisateur.id_realisateur=td_realisateur.id_realisateur AND 
		td_film_has_genre.id_film=td_film.id_film AND td_film_has_genre.id_genre=td_genre.id_genre AND ".$param;*/
		$query="SELECT td_film.id_film,titre,duree,annee,image,genre FROM td_film NATURAL JOIN td_genre,td_film_has_genre
		WHERE td_film_has_genre.id_film=td_film.id_film AND td_film_has_genre.id_genre=td_genre.id_genre AND ".$param;
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