create schema lifter;
use lifter;

create table if not exists 响应信息
(
时间 datetime not null,
楼层 int not null,
等待时间 bigint not null,
primary key(时间,楼层,等待时间),
index(时间)
);
create table if not exists 运行信息
(
时间 datetime not null,
楼层 int not null,
位置 double not null,
速度 double not null,
primary key(时间),
index(时间)
);