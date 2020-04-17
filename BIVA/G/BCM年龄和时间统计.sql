SELECT COUNT(DISTINCT(姓名)) AS 总人数,MAX(T.年龄) AS 最大年龄,MIN(T.年龄) AS 最小年龄,MIN(检测日期) AS 最早检测时间,MAX(检测日期) AS 最晚检测时间 FROM
(SELECT abs(TIMESTAMPDIFF(DAY, 出生日期, 检测日期))/365 AS 年龄,检测日期,姓名 FROM hospital.bcm原始数据) AS T;
