-- phpMyAdmin SQL Dump
-- version 3.3.5
-- http://www.phpmyadmin.net
--
-- 主機: localhost
-- 建立日期: Jan 21, 2017, 04:05 AM
-- 伺服器版本: 5.1.49
-- PHP 版本: 5.2.14

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 資料庫: `iot`
--

-- --------------------------------------------------------

--
-- 資料表格式： `dhtdata`
--

CREATE TABLE IF NOT EXISTS `dhtdata` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'datetime',
  `yyyymmdd` date NOT NULL,
  `humidity` float NOT NULL,
  `celsius` float NOT NULL,
  `fahrenheit` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='溫濕度感測資料' AUTO_INCREMENT=1 ;

--
-- 列出以下資料庫的數據： `dhtdata`
--


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
