function data = data_read( path )
%��ȡ������ɸѡ
total=xlsread(path);
data=data_select(total);
end
