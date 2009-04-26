-- phpMyAdmin SQL Dump
-- version 2.9.1.1
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Apr 25, 2009 at 09:48 PM
-- Server version: 5.0.27
-- PHP Version: 5.2.0
-- 
-- Database: `librarydb`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `books`
-- 

CREATE TABLE `books` (
  `bookId` int(11) NOT NULL auto_increment,
  `bookTagNum` varchar(4) NOT NULL,
  `shelfNum` varchar(2) NOT NULL,
  `title` varchar(50) NOT NULL,
  `abbreviatedTitle` varchar(16) NOT NULL,
  `author` varchar(50) NOT NULL,
  `isbn` int(13) NOT NULL,
  `callNum` varchar(50) NOT NULL,
  `status` enum('Checked In','Checked Out') NOT NULL,
  `checkedoutBy` varchar(50) NOT NULL,
  `dueDate` date NOT NULL,
  PRIMARY KEY  (`bookId`),
  UNIQUE KEY `bookTagNum` (`bookTagNum`),
  FULLTEXT KEY `title` (`title`),
  FULLTEXT KEY `author` (`author`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=58 ;

-- 
-- Dumping data for table `books`
-- 

INSERT INTO `books` (`bookId`, `bookTagNum`, `shelfNum`, `title`, `abbreviatedTitle`, `author`, `isbn`, `callNum`, `status`, `checkedoutBy`, `dueDate`) VALUES 
(1, '&}', '1', 'Microelectronic Circuits', 'Microelec Circ', 'Sedra and Smith', 2147483647, 'SS-MC-2003', 'Checked In', '', '0000-00-00'),
(3, 'B003', '1', 'The Art of Electronics', 'Art of Elec', 'Paul horowitz', 521370977, 'PH-ARTELEC-2001', 'Checked In', '', '0000-00-00'),
(4, 'B004', '1', 'Troubleshooting Analog Circuits', 'TSing Analog Cir', 'Robert A. Pease', 750694998, 'RP-TAC-2000', 'Checked In', '', '0000-00-00'),
(5, 'B005', '1', 'The ARRL Handbook for Radio Communications', 'ARRL Handbook', 'Mark J. Wilson', 872591018, 'MW-ARRLHRC-1999', 'Checked In', '', '0000-00-00'),
(6, 'B006', '2', 'Fundamental of Electric Circuits', 'Fund of Elec Cir', 'Alexander and Sadiku', 2147483647, 'AS-FUNDELECCIR-2005', 'Checked In', '', '0000-00-00'),
(7, 'B007', '2', 'Engineering Electromagnetics', 'Eng Electromagne', 'William Hayt', 2147483647, 'WH-EM-2004', 'Checked In', '', '0000-00-00'),
(2, '&}', '2', 'Signals and Systems', 'Sig and Sys', 'Alan Oppenheimer', 2147483647, 'AO-SS-1995', 'Checked Out', 'user1', '2008-11-28');

-- --------------------------------------------------------

-- 
-- Table structure for table `list`
-- 

CREATE TABLE `list` (
  `bookListId` int(11) NOT NULL auto_increment,
  `cookieId` varchar(50) default NULL,
  `bookId` int(11) default NULL,
  `container` int(11) default NULL,
  PRIMARY KEY  (`bookListId`),
  UNIQUE KEY `id` (`bookListId`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

-- 
-- Dumping data for table `list`
-- 

INSERT INTO `list` (`bookListId`, `cookieId`, `bookId`, `container`) VALUES 
(1, 'rojobtjepa4fdsg7snvekvsdk5', 3, 1),
(2, 'rojobtjepa4fdsg7snvekvsdk5', 6, 1);

-- --------------------------------------------------------

-- 
-- Table structure for table `misplaced`
-- 

CREATE TABLE `misplaced` (
  `misplacedid` int(11) NOT NULL auto_increment,
  `bookTagNum` varchar(4) NOT NULL,
  `foundAtShelf` varchar(4) NOT NULL,
  `lastScanned` datetime NOT NULL,
  PRIMARY KEY  (`misplacedid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

-- 
-- Dumping data for table `misplaced`
-- 

INSERT INTO `misplaced` (`misplacedid`, `bookTagNum`, `foundAtShelf`, `lastScanned`) VALUES 
(1, '&}', '&}', '2008-11-14 23:33:36'),
(2, '&}', '&}', '2008-11-14 23:33:36'),
(3, '&}', '&}', '2008-11-14 23:33:36');

-- --------------------------------------------------------

-- 
-- Table structure for table `shelf`
-- 

CREATE TABLE `shelf` (
  `shelfNum` varchar(1) NOT NULL,
  `shelfTagNum` varchar(4) NOT NULL,
  UNIQUE KEY `shelfNum` (`shelfNum`),
  UNIQUE KEY `shelfTagNum` (`shelfTagNum`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `shelf`
-- 

INSERT INTO `shelf` (`shelfNum`, `shelfTagNum`) VALUES 
('1', '&}'),
('2', 'S002');

-- --------------------------------------------------------

-- 
-- Table structure for table `users`
-- 

CREATE TABLE `users` (
  `userId` int(11) NOT NULL auto_increment,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `userType` enum('admin','reg') NOT NULL default 'reg',
  PRIMARY KEY  (`userId`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

-- 
-- Dumping data for table `users`
-- 

INSERT INTO `users` (`userId`, `username`, `password`, `userType`) VALUES 
(3, 'user1', '5f62483a188d1c0fef6b7be151751e10', 'reg'),
(6, 'admin', '5f62483a188d1c0fef6b7be151751e10', 'admin'),
(10, 'user2', '5f62483a188d1c0fef6b7be151751e10', 'reg'),
(11, 'admin2', '5f62483a188d1c0fef6b7be151751e10', 'admin'),
(12, 'admin3', '5f62483a188d1c0fef6b7be151751e10', 'admin');
