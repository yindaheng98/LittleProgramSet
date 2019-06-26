im=imread('news\new2\001.pgm');
subplot(2,2,1);
imshow(im);
title('‘≠Õº');
im = double(im(:));
objectone = V'*(im - img_pj);
temp=[];
for k = 1:wts
    temp(k) = norm(objectone - W(:,k));
end
[s_temp,id]=sort(temp,'ascend');

for i=1:3
    subplot(2,2,i+1);
    imshow(imread(['news\new1\',sprintf('%03d.pgm',id(i))]));
    title(sprintf('PCAø’º‰æ‡¿Î=%g',s_temp(i)));
end
