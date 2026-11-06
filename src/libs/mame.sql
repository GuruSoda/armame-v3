PRAGMA foreign_keys=on;

create table manufacturer (
	id_manufacturer integer primary key autoincrement,
	name			text not null
);

create table game (
	id_game 	integer primary key autoincrement,
	name		text unique,
	sourcefile	text,
	year		integer,
	description	text,

	id_manufacturer INTEGER REFERENCES manufacturer (id_manufacturer) ON DELETE CASCADE
--	cloneof		integer references game (id_game) on delete cascade,
--	romof		integer references game (id_game) on delete cascade

--	cloneof		text,
--	romof		text
);

create table rom (
	id_rom	integer primary key autoincrement,
	name	text not null, 
	size	integer,
	crc		text,
	sha1	text,
	merge	integer
);

create table rom_game (
	id_game		integer references game (id_game) on delete cascade,
	id_rom		integer references rom (id_rom) on delete cascade
);

create table game_cloneof_romof (
	id_game integer not null, 
	cloneof text, 
	romof text
);
