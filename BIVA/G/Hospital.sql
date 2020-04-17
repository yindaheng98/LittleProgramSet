drop database if exists Hospital;
create database Hospital DEFAULT CHARACTER SET utf8;
use Hospital;
drop user if exists Hospital@'%';
create user Hospital@'%' identified WITH mysql_native_password by 'Hospital' PASSWORD EXPIRE NEVER;
grant select,update,insert,delete,create,drop on Hospital.* to Hospital@'%';
flush privileges;