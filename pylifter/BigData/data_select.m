function data = data_select( total )
%ɸѡ���������е����ݣ��ٶȲ�Ϊ0��
%�ṹ��data[��/���й��̱��][ԭʼ��������][ԭʼ��������]
data=zeros(500,15,11);
num=0;%�Ѵ������/���й�����
flag=0;%��ȡ��ʼ/������ʶ
[raw,~]=size(total);%��ȡ����
t=0;
temp=zeros(15,11);
for i=1:raw%����ɨ��
    if (total(i,4)~=0)&&(flag==0)%�ҵ��ٶȲ�Ϊ0�����ݣ���δ��ʼ����
        flag=1;%��ʼ����
        t=t+1;
        temp(t,:)=total(i-1,:);%��temp��������һ���ٶ�Ϊ0������
        t=t+1;
        temp(t,:)=total(i,:);%��temp����һ������
    else if (total(i,4)~=0)&&(flag==1)%�ҵ��ٶȲ�Ϊ0�����ݣ������ڶ���
            t=t+1;
            temp(t,:)=total(i,:);%������temp����һ������
    else if (total(i,4)==0)&&(flag==1)%ɨ�赽����ͣ��
            t=t+1;
            temp(t,:)=total(i,:);%��temp����һ���ٶ�Ϊ0����
            flag=0;%ֹͣ��ȡ
            t=0;%t��0
            num=num+1;
            data(num,:,:)=temp(:,:);%�����ݷ���data��
        end
        end
    end
end
end

