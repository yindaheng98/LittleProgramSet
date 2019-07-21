%��ɫ�ʻظ��Ķ�߶�retinex
%imgΪ�����ͼ��,imgΪRGBͼ��
%dΪ�Աȶȣ��ԱȶȵĿ���Ϊ����ʵ��
%nscalsΪ�߶ȵ�����,scals>=1
%maxscalsΪ���߶��� maxscals>=0

%ʹ�ã�
%img = imread(pathname);
%result = msrcr(img,d,nscals,maxscals);
%imshow(result)

function result = msrcr(img,d,nscals,maxscals)
img = double(img);
ssr = 0;
r = size(img,1);
c = size(img,2);
g = img(:,:,1) + img(:,:,2) + img(:,:,3);
scals = processcals(nscals,maxscals);
for m = 1:3    %3channel RGB
    t = img(:,:,m);
    T = fft2(t);
    for n = 1:nscals    %����scals
        gauss = gaussian(r,c,scals(n));
        gauss = fft2(gauss,size(t,1),size(t,2));
        gauss = fftshift(gauss);
        R = ifft2(T.*gauss);
        R = abs(R);
        ssr = ssr + log(t+1) - log(R+1);
    end
    msri = ssr/nscals;   %msr
    c = (log(125*t+1) - log(g+1))*46;
    msrcr = msri.*c;     %���ﻹ�����ڴ���G(msri.*c+b)  G,b  msrcr
    min1 = mean(mean(msrcr)) - std(std(msrcr))*d;     %ȡֵ��ʽ
    max1 = mean(mean(msrcr)) + std(std(msrcr))*d;
    range = max1 - min1;
    if range ==0
        range =1;
    end
    result(:,:,m) = uint8(255*(msrcr-min1)/range); 
end
end

function gauss = gaussian(r,c,sigma)
%rΪ�У�cΪ�У�simgaΪ�߶Ȳ���
[x,y] = meshgrid(-(r-1)/2:r/2,-(c-1)/2:c/2);
gauss = exp(-(x.^2+y.^2)/(2*sigma*sigma));
gauss = gauss/sum(gauss(:));   
end

function a = processcals(nscals,maxscals)
%scalsΪ�߶ȵ�������maxscalsΪ���ĳ߶�
%Ĭ�ϳ߶�Ϊ���ȷֲ�
a = [];
size_step = maxscals/nscals;
for i = 0:nscals-1
    a = [a,15 + i*size_step];    %���ص����ݵĴ���
end
end