#host :172.0.0.1
#database:nameserver
#Table: 'COMPANY'
CREATE TABLE 'COMPANY' (
	'ID' int(32) unsigned NOT NULL aoto_increment,
	'NAME' varchar(32) NOT NULL default '',
	'ZONE',smallint(10) unsigned NOT NULL default '0',
	PRIMARY KEY ('ID')
	) ENGINE=MyISAM DEFAULT CHARSET=latin1;

