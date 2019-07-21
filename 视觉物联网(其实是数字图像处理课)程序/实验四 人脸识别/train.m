function [ V,W,img_pj,wts ] = train( training_set )
%��ѵ��������ѵ��
path = training_set;
img_path = dir(strcat(path,'*.pgm'));
img_num = length(img_path);
imagedata = [];
if img_num >0
    for j = 1:img_num
        img_name = img_path(j).name;
        temp = imread(strcat(path, '/', img_name));
        temp = double(temp(:));
        imagedata = [imagedata, temp];
    end
end
wts = size(imagedata,2);

% ���Ļ�������Э�������
img_pj = mean(imagedata,2);
for i = 1:wts
    imagedata(:,i) = imagedata(:,i) - img_pj;
end
covMat = imagedata'*imagedata;

[COEFF, latent, explained] = pcacov(covMat);
% ѡ�񹹳� 95%����������ֵ
i = 1; proportion = 0;
while(proportion < 95)
    proportion = proportion + explained(i);
    i = i+1;
end
k = i - 1;
%���ԭЭ��������������������������
V = imagedata*COEFF;
% N*M ��
V = V(:,1:k);
% ѵ�������� PCA �����ռ��µı����� k*M
W = V'*imagedata;
disp('ѵ�����');
end

