function test( img_path,training_set,V,W,img_pj,wts )
%≤‚ ‘
im=imread(img_path);
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
    imshow(imread([training_set,sprintf('%03d.pgm',id(i))]));
    title(sprintf('PCAø’º‰æ‡¿Î=%g',s_temp(i)));
end
end

