close all;clear all;clc; 
I=imread('image4.tif'); 
PSF=fspecial('motion',8,0);
luc=deconvlucy(I,PSF);
lwnr=deconvwnr(I,PSF);
lreg=deconvreg (I,PSF);
figure
subplot(2,2,1);
imshow(I);
title('原始图像');
subplot(2,2,2); 
imshow(luc); 
title('Lucy-Richardson滤波');
subplot(2,2,3); 
imshow(lwnr); 
title('维纳滤波');
subplot(2,2,4); 
imshow(lreg); 
title('可约束最小二乘滤波');
