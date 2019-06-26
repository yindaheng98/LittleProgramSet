function [ V,W,img_pj,wts ] = train( training_set )
%用训练集进行训练
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

% 中心化并计算协方差矩阵
img_pj = mean(imagedata,2);
for i = 1:wts
    imagedata(:,i) = imagedata(:,i) - img_pj;
end
covMat = imagedata'*imagedata;

[COEFF, latent, explained] = pcacov(covMat);
% 选择构成 95%能量的特征值
i = 1; proportion = 0;
while(proportion < 95)
    proportion = proportion + explained(i);
    i = i+1;
end
k = i - 1;
%求出原协方差矩阵的特征向量，即特征脸
V = imagedata*COEFF;
% N*M 阶
V = V(:,1:k);
% 训练样本在 PCA 特征空间下的表达矩阵 k*M
W = V'*imagedata;
disp('训练完成');
end

