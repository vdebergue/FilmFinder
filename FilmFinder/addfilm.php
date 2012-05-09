<?php
	@mysql_connect("localhost","poudet","6fcf0004") or die("Echec de
	connexion au serveur.");
	@mysql_query("SET NAMES 'utf8'"); 
	@mysql_select_db("poudet") or die("Echec de selection de la base");
	
if(isset($_POST['addfilm'])){

	$titre=utf8_encode($_POST['titre']);
	$annee=$_POST['annee'];
	$duree=$_POST['duree'];
	$image=$_POST['image'];
	$genre=$_POST['genre'];
	$acteur=$_POST['acteur'];
	$realisateur=$_POST['realisateur'];
	
	$genres=explode(',',$genre);
	$acteurs=explode(',',$acteur);
	$realisateurs=explode(',',$realisateur);
	
	$selectFilm=mysql_query("SELECT titre FROM td_film WHERE titre='$titre'");
	if(mysql_num_rows($selectFilm)==0){
		
		$query=mysql_query("INSERT INTO td_film VALUES(NULL,'$titre','$duree','$annee','$image')");
		$id_film=mysql_insert_id();
		
		for($i=0;$i<sizeof($genres);$i++){
			$nom=utf8_encode(trim($genres[$i]));
			$selectGenre=mysql_query("SELECT * FROM td_genre WHERE genre='$nom'");
			if(mysql_num_rows($selectGenre)==0){
				$insertGenre=mysql_query("INSERT INTO td_genre VALUES(NULL,'$nom')");
				$id_genre=mysql_insert_id();
			}
			else{
				$data=mysql_fetch_array($selectGenre);
				$id_genre=$data['id_genre'];
			}
			$insertRelationGenre=mysql_query("INSERT INTO td_film_has_genre VALUES('$id_film','$id_genre')");
		}
		for($i=0;$i<sizeof($acteurs);$i++){
			$acteur=explode(" ",trim($acteurs[$i]));
			$prenomActeur=utf8_encode($acteur[0]);
			$nomActeur=utf8_encode($acteur[1]);
			$selectActeur=mysql_query("SELECT * FROM td_acteur WHERE nom_acteur='$nomActeur' AND prenom_acteur='$prenomActeur'");
			if(mysql_num_rows($selectActeur)==0){
				$insertActeur=mysql_query("INSERT INTO td_acteur VALUES(NULL,'$nomActeur','$prenomActeur')");
				$id_acteur=mysql_insert_id();
			}
			else{
				$data=mysql_fetch_array($selectActeur);
				$id_acteur=$data['id_acteur'];
			}
			$insertRelationActeur=mysql_query("INSERT INTO td_film_has_acteur VALUES('$id_film','$id_acteur')");
		}
		for($i=0;$i<sizeof($realisateurs);$i++){
			$realisateur=explode(" ",trim($realisateurs[$i]));
			$prenomRealisateur=utf8_encode($realisateur[0]);
			$nomRealisateur=utf8_encode($realisateur[1]);
			$selectRealisateur=mysql_query("SELECT * FROM td_realisateur WHERE nom_realisateur='$nomRealisateur' AND prenom_realisateur='$prenomRealisateur'");
			if(mysql_num_rows($selectRealisateur)==0){
				$insertRealisateur=mysql_query("INSERT INTO td_realisateur VALUES(NULL,'$nomRealisateur','$prenomRealisateur')");
				$id_realisateur=mysql_insert_id();
			}
			else{
				$data=mysql_fetch_array($selectRealisateur);
				$id_realisateur=$data['id_realisateur'];
			}
			$insertRelationRealisateur=mysql_query("INSERT INTO td_film_has_realisateur VALUES('$id_film','$id_realisateur')");
		}

	}
	else{
		echo 'Film deja existant';
	}

}	
?>
<h2>Ajouter un Film</h2>
<form action="addfilm.php" method="POST">
Titre : <input type="text" name="titre"/><br/>
Annee : <input type="text" name="annee"/><br/>
Duree : <input type="text" name="duree"/><br/>
Nom Image : <input type="text" name="image"/><br/>
Genre (séparés par,) : <textarea name="genre"></textarea><br/>
Acteurs (séparés par,) : <textarea  name="acteur"></textarea><br/>
Réalisateurs (séparés par,) : <textarea  name="realisateur"></textarea><br/>
<input type="submit" name="addfilm"/>
</form>
