function data = data_deal( data )
%��¼�¾�����¥��������ʼ¥�����ֹ¥��
[total,~,~]=size(data);%��ȡ���ݸ�����ÿ�����ݵ�����
for i=1:total%���ɨ��
    floor_start=data(i,1,8);
    [~,floor_end]=min(data(i,:,8));
    floor_end=floor_end-1;
    data(i,end,end)=floor_end-floor_start;%���һλ�Ǿ�����¥��
    data(i,end,end-1)=floor_end;
    data(i,end,end-2)=floor_start;%��¼��ʼ�����ֹ��
end
end

