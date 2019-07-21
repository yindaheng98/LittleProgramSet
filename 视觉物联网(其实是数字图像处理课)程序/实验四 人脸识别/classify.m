function c = classify(im,V,W,img_pj,wts)
im = double(im(:));
objectone = V'*(im - img_pj);
c=0;
m=inf;
for k = 1:wts
    t=norm(objectone - W(:,k));
    if t<m
        m=t;
        c=k;
    end
end
end

