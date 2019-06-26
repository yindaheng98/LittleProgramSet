function data = data_deal( data )
%记录下经过的楼层数，起始楼层和终止楼层
[total,~,~]=size(data);%读取数据个数和每个数据的行数
for i=1:total%逐个扫描
    floor_start=data(i,1,8);
    [~,floor_end]=min(data(i,:,8));
    floor_end=floor_end-1;
    data(i,end,end)=floor_end-floor_start;%最后一位是经过的楼层
    data(i,end,end-1)=floor_end;
    data(i,end,end-2)=floor_start;%记录起始层和终止层
end
end

