function [data_up,data_down] = data_classify( data )
%������������ݺ���������
%����������¥���������
%�ṹ��up/down_data[������¥����][ԭʼ��������][ԭʼ��������]
num_up=0;
num_down=0;%�Ѵ����������
flag=0;%��ȡ��ʼ/������ʶ
[total,raw,~]=size(data);%��ȡ���ݸ�����ÿ�����ݵ�����
for i=1:total%���ɨ��
    floor_start=data(i,1,8);
    [~,floor_end]=min(data(i,1:end,8));
    floor_end=floor_end-1;
    data(end)=floor_end-floor_start;%���һλ�Ǿ�����¥��
    data(end-1)=floor_end;
    data(end-2)=floor_start;%��¼��ʼ�����ֹ��
end
end

