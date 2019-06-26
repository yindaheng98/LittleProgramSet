function [weightfirst,weighthide,weightfinal]=NetworkBackPropagationOnce(cost,weightfirst,weighthide,weightfinal,degree)
%进行一次反向传播,degree为学习率
%和代价函数的形式有关,和
[hidenum,inputnum]=size(weightfirst);
[layernum,~,~]=size(weighthide);
[outputnum,~]=size(weightfinal);

end
