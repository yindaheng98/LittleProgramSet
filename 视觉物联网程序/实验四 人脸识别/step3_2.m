%step2;
total=0;
for i=1:wts
    im=imread(['news\new2\',sprintf('%03d.pgm',i)]);
    c=classify(im,V,W,img_pj,wts);
    if floor(c/5)==floor(i/5)
        total=total+1;
    end
end
fprintf('��ȷ��Ϊ%f%%\n',total/200*100);