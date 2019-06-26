function data = data_select( total )
%筛选出所有运行的数据（速度不为0）
%结构：data[上/下行过程编号][原始数据列数][原始数据行数]
data=zeros(500,15,11);
num=0;%已存入的上/下行过程量
flag=0;%读取开始/结束标识
[raw,~]=size(total);%读取行数
t=0;
temp=zeros(15,11);
for i=1:raw%逐行扫描
    if (total(i,4)~=0)&&(flag==0)%找到速度不为0的数据，且未开始读数
        flag=1;%开始读数
        t=t+1;
        temp(t,:)=total(i-1,:);%向temp中填入上一行速度为0的数据
        t=t+1;
        temp(t,:)=total(i,:);%向temp中填一行数据
    else if (total(i,4)~=0)&&(flag==1)%找到速度不为0的数据，且正在读数
            t=t+1;
            temp(t,:)=total(i,:);%继续向temp中填一行数据
    else if (total(i,4)==0)&&(flag==1)%扫描到电梯停了
            t=t+1;
            temp(t,:)=total(i,:);%向temp中填一行速度为0数据
            flag=0;%停止读取
            t=0;%t归0
            num=num+1;
            data(num,:,:)=temp(:,:);%将数据放入data中
        end
        end
    end
end
end

