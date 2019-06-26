function [data_up,data_down] = data_classify( data )
%分类出上行数据和下行数据
%按所经过的楼层进行排列
%结构：up/down_data[经过的楼层数][原始数据列数][原始数据行数]
num_up=0;
num_down=0;%已存入的数据量
flag=0;%读取开始/结束标识
[total,raw,~]=size(data);%读取数据个数和每个数据的行数
for i=1:total%逐个扫描
    floor_start=data(i,1,8);
    [~,floor_end]=min(data(i,1:end,8));
    floor_end=floor_end-1;
    data(end)=floor_end-floor_start;%最后一位是经过的楼层
    data(end-1)=floor_end;
    data(end-2)=floor_start;%记录起始层和终止层
end
end

