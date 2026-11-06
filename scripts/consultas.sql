-- cantidad de roms repetidas en sha1
select name,sha1, count(*)
from ROM
group by name,sha1
order by 3 DESC

-- listar en formato .zip los juegos NO clones
select game.name || ".zip" from game where game.cloneof is NULL 

-- cantidad de juegos que no son clones y no usan roms de otros
select count(game.name) from game where game.cloneof is not NULL and game.cloneof is not null

-- Juegos que tiene la misma rom
select game.name 
from game, rom, rom_game 
where game.id_game = rom_game.id_game 
    and rom.id_rom = rom_game.id_rom 
    and rom.sha1 = '2c420d34dba21e409bf78ddca710fc7de65a6642'

-- Juegos donde la emulacion es correcta
select a.name, c.text 
from game a,driver b, text c 
where a.driver = b.id_driver and b.emulation = c.id_text and c.text = "good";

-- Listado de juegos de lo primeros 50 juego--
select a.year as "Año", a.description as "Descripcion", b.name as "Source", c.name as "Fabricante", e.text as "Estado", f.text as "Emulacion"
from game a, sourcefile b, manufacturer c, driver d, text e, text f
where a.sourcefile = b.id_sourcefile and a.manufacturer = c.id_manufacturer and a.cloneof is null and a.driver = d.id_driver and d.status = f.id_text and d.emulation = e.id_text
order by a.year asc
limit 50

-- Para ver las tablas de la base de datos 
select * FROM sqlite_master

-- para ver la lista de autoincrement 
select * from sqlite_sequence

-- lista los juegos y muesta el estado de la emulacion y el status
select a.name, c.text as "Emulation", d.text as "status"
from game a,driver b, text c, text d
where a.driver = b.id_driver and b.emulation = c.id_text and b.status = d.id_text

######################################################
## Nuevo DER de la base de datos.
######################################################

-- minimal
select name, description from game where name = "rygar"

-- basic
select g.name, g.description, m.name, g.year, g.cloneof, g.romof from game g, manufacturer m where g.manufacturer = m.id_manufacturer and g.name = "rygar"

-- normal = basic + roms
select r.name as Name, r.bios as Bios, r.size as Size, r.crc as CRC, r.sha1 as SHA1, r.merge as Merge, r.region as Region, r.offset as Offset, r.status as Status, r.optional as Optional
from game g, game_rom gr, rom r
where g.id_game = gr.id_game and gr.id_rom = r.id_rom and g.name = "rygar"

-- Para saber los device_refs del juego rygar
select text.text as Device_ref
from game, device_ref, text 
where game.id_game = device_ref.id_game and device_ref.name = text.id_text and game.name = "rygar"

-- Para saber los chips del juego rygar
select chip.type as Type, chip.tag as Tag, chip.name as Name, chip.clock as Clock from game, chip, game_chip
where game_chip.id_chip = chip.id_chip and game_chip.id_game = game.id_game
    and game.name = "rygar"

-- Para saber los disks del juego rygar
select d.name, d.sha1, d.merge, d.region, d._index, d.writable, d.status, d.optional
from game g, game_disk gd, disk d
where g.id_game = gd.id_game and d.id_disk = gd.id_disk
and g.name = "rygar"

-- Para saber el display del juego rygar
select d.tag, d.type, cast(d.rotate as text) as rotate, d.flipx, cast(d.width as text) as width, cast(d.height as text) as height, d.refresh, d.pixclock, cast(d.htotal as text) as htotal, cast(d.hbend as text) as hbend, cast(d.hbstart as text) as hbstart, cast(d.vtotal as text) as vtotal, cast(d.vbend as text) as vbend, cast(d.vbstart as text) as vbstart
from game g, display d
where g.id_game = d.id_game
and g.name = "rygar"

-- Para saber el driver del juego rygar
select g.name, status.text as Status, emulation.text as Emulation, color.text as Color, sound.text as Sound, graphic.text as Graphic, cocktail.text as Cocktail, protection.text as Protection, savestate.text as SaveState
from game g, driver d, text status, text emulation, text color, text sound, text graphic, text cocktail, text protection, text savestate 
where g.id_game = d.id_game and 
status.id_text = d.status and
emulation.id_text = d.emulation and
color.id_text = d.color and
sound.id_text = d.sound and
graphic.id_text = d.graphic and
cocktail.id_text = d.cocktail and
protection.id_text = d.protection and
savestate.id_text = d.savestate and g.name = "rygar"

-- Lista de los atributos del juego rygar
select g.id_game, g.name, g.year, g.description, m.name as manufacturer, s.name as sourcefile, g.cloneof, g.romof, case(runnable) when 1 then "Yes" when 0 then "No" end as runnable, case(isbios) when 1 then "Yes" when 0 then "No" end as isbios, case(isdevice) when 1 then "Yes" when 0 then "No" end as isdevice, case(ismechanical) when 1 then "Yes" when 0 then "No" end as ismechanical
from game g, sourcefile s, manufacturer m
where g.sourcefile = s.id_sourcefile and g.manufacturer = m.id_manufacturer
and g.name = "rygar"
