clear;
pathfrom='images';
x=1:9;
y=[];
for training_num=x
    training_set=sprintf('sets/training%d/',training_num);
    testing_set=sprintf('sets/testing%d/',training_num);
    k=10;
    a=0;
    for i=1:k
        setdivi(pathfrom,training_num,training_set,testing_set);
        [ V,W,img_pj,wts ] = train( training_set );
        a = a+ accurancy( testing_set,V,W,img_pj,wts,training_num );
    end
    y(end+1)=a/k;
end
plot(x,y,'marker','o')
xlabel('ѵ����ͼ������(��/��)');
ylabel('��ȷ��');
title('ѵ����ͼ�񻮷�-��ȷ�ʹ�ϵͼ');