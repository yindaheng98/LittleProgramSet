create database if not exists lifterdata
char set 'utf8'
collate 'utf8_general_ci';
use lifterdata;
create table if not exists original
(
电梯ID int unsigned not null,
实时时钟 datetime not null,
primary key(电梯ID,实时时钟),
运行速度 float unsigned not null,
母线电压 float unsigned not null,
母线电流 float unsigned not null,
频率 float unsigned not null,
当前楼层 smallint unsigned not null,
系统状态 smallint unsigned not null,
轿厢状态 smallint unsigned not null,
控制器状态 smallint unsigned not null,
故障描述 smallint unsigned not null
);