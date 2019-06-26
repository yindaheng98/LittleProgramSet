function data = data_read( path )
%读取并调用筛选
total=xlsread(path);
data=data_select(total);
end
