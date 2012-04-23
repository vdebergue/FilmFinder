-- phpMyAdmin SQL Dump
-- version 3.3.9
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Lun 23 Avril 2012 à 08:30
-- Version du serveur: 5.1.53
-- Version de PHP: 5.3.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `filmfinder`
--

-- --------------------------------------------------------

--
-- Structure de la table `td_acteur`
--

DROP TABLE IF EXISTS `td_acteur`;
CREATE TABLE IF NOT EXISTS `td_acteur` (
  `id_acteur` int(11) NOT NULL AUTO_INCREMENT,
  `nom_acteur` varchar(100) DEFAULT NULL,
  `prenom_acteur` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id_acteur`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Contenu de la table `td_acteur`
--

INSERT INTO `td_acteur` (`id_acteur`, `nom_acteur`, `prenom_acteur`) VALUES
(1, 'Sy', 'Omar'),
(2, 'Cluzet', 'Francois'),
(3, 'Smith', 'Will'),
(4, 'Dawson', 'Rosario'),
(5, 'Dujardin', 'Jean'),
(6, 'Croze', 'Marie-Josée'),
(7, 'Diaz', 'Cameron'),
(8, 'Breslin', 'Abigail'),
(9, 'Baldwin', 'Alec'),
(10, 'Lellouche', 'Gilles'),
(11, 'Zem', 'Roschdy'),
(12, 'Lanvin', 'Gérard');

-- --------------------------------------------------------

--
-- Structure de la table `td_film`
--

DROP TABLE IF EXISTS `td_film`;
CREATE TABLE IF NOT EXISTS `td_film` (
  `id_film` int(11) NOT NULL AUTO_INCREMENT,
  `titre` varchar(256) DEFAULT NULL,
  `duree` int(11) DEFAULT NULL,
  `annee` varchar(4) DEFAULT NULL,
  `image` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_film`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Contenu de la table `td_film`
--

INSERT INTO `td_film` (`id_film`, `titre`, `duree`, `annee`, `image`) VALUES
(1, 'Intouchables', 112, '2011', NULL),
(2, 'Ma vie pour la tienne', 109, '2010', NULL),
(3, 'Sept Vies', 118, '2008', NULL),
(4, 'Un Balcon Sur la mer', 103, '2010', NULL),
(5, 'A Bout Portant', 81, '2010', NULL);

-- --------------------------------------------------------

--
-- Structure de la table `td_film_has_acteur`
--

DROP TABLE IF EXISTS `td_film_has_acteur`;
CREATE TABLE IF NOT EXISTS `td_film_has_acteur` (
  `id_film` int(11) NOT NULL,
  `id_acteur` int(11) NOT NULL,
  PRIMARY KEY (`id_film`,`id_acteur`),
  KEY `fk_td_film_has_td_acteur_td_acteur1` (`id_acteur`),
  KEY `fk_td_film_has_td_acteur_td_film` (`id_film`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `td_film_has_acteur`
--

INSERT INTO `td_film_has_acteur` (`id_film`, `id_acteur`) VALUES
(1, 1),
(1, 2),
(3, 3),
(3, 4);

-- --------------------------------------------------------

--
-- Structure de la table `td_film_has_genre`
--

DROP TABLE IF EXISTS `td_film_has_genre`;
CREATE TABLE IF NOT EXISTS `td_film_has_genre` (
  `id_film` int(11) NOT NULL,
  `id_genre` int(11) NOT NULL,
  PRIMARY KEY (`id_film`,`id_genre`),
  KEY `fk_td_film_has_td_genre_td_genre1` (`id_genre`),
  KEY `fk_td_film_has_td_genre_td_film1` (`id_film`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `td_film_has_genre`
--

INSERT INTO `td_film_has_genre` (`id_film`, `id_genre`) VALUES
(1, 1),
(2, 2),
(3, 2),
(4, 2),
(5, 2);

-- --------------------------------------------------------

--
-- Structure de la table `td_film_has_realisateur`
--

DROP TABLE IF EXISTS `td_film_has_realisateur`;
CREATE TABLE IF NOT EXISTS `td_film_has_realisateur` (
  `id_film` int(11) NOT NULL,
  `id_realisateur` int(11) NOT NULL,
  PRIMARY KEY (`id_film`,`id_realisateur`),
  KEY `fk_td_film_has_td_realisateur_td_realisateur1` (`id_realisateur`),
  KEY `fk_td_film_has_td_realisateur_td_film1` (`id_film`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `td_film_has_realisateur`
--

INSERT INTO `td_film_has_realisateur` (`id_film`, `id_realisateur`) VALUES
(1, 1),
(1, 2);

-- --------------------------------------------------------

--
-- Structure de la table `td_genre`
--

DROP TABLE IF EXISTS `td_genre`;
CREATE TABLE IF NOT EXISTS `td_genre` (
  `id_genre` int(11) NOT NULL AUTO_INCREMENT,
  `genre` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_genre`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Contenu de la table `td_genre`
--

INSERT INTO `td_genre` (`id_genre`, `genre`) VALUES
(1, 'Comédie'),
(2, 'Drame');

-- --------------------------------------------------------

--
-- Structure de la table `td_realisateur`
--

DROP TABLE IF EXISTS `td_realisateur`;
CREATE TABLE IF NOT EXISTS `td_realisateur` (
  `id_realisateur` int(11) NOT NULL AUTO_INCREMENT,
  `nom_realisateur` varchar(100) DEFAULT NULL,
  `prenom_realisateur` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id_realisateur`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Contenu de la table `td_realisateur`
--

INSERT INTO `td_realisateur` (`id_realisateur`, `nom_realisateur`, `prenom_realisateur`) VALUES
(1, 'Nakache', 'Olivier'),
(2, 'Toledano', 'Eric'),
(3, 'Cavayé', 'Fred'),
(4, 'Garcia', 'Nicole'),
(5, 'Muccino', 'Gabriele');

--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `td_film_has_acteur`
--
ALTER TABLE `td_film_has_acteur`
  ADD CONSTRAINT `fk_td_film_has_td_acteur_td_film` FOREIGN KEY (`id_film`) REFERENCES `td_film` (`id_film`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_td_film_has_td_acteur_td_acteur1` FOREIGN KEY (`id_acteur`) REFERENCES `td_acteur` (`id_acteur`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Contraintes pour la table `td_film_has_genre`
--
ALTER TABLE `td_film_has_genre`
  ADD CONSTRAINT `fk_td_film_has_td_genre_td_film1` FOREIGN KEY (`id_film`) REFERENCES `td_film` (`id_film`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_td_film_has_td_genre_td_genre1` FOREIGN KEY (`id_genre`) REFERENCES `td_genre` (`id_genre`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Contraintes pour la table `td_film_has_realisateur`
--
ALTER TABLE `td_film_has_realisateur`
  ADD CONSTRAINT `fk_td_film_has_td_realisateur_td_film1` FOREIGN KEY (`id_film`) REFERENCES `td_film` (`id_film`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_td_film_has_td_realisateur_td_realisateur1` FOREIGN KEY (`id_realisateur`) REFERENCES `td_realisateur` (`id_realisateur`) ON DELETE NO ACTION ON UPDATE NO ACTION;
