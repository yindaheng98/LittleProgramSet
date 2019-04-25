clear;
K=5000;%运行10次
LearningDegree=0.1;%学习率
LAYERN=3;
HIDEN=7;

XMAX=10;
YMAX=10;
XPRECISION=50;
YPRECISION=50;

x=linspace(0,XMAX,XPRECISION);
y=linspace(0,YMAX,YPRECISION);
xs=repmat(x',1,YPRECISION);
ys=repmat(y,XPRECISION,1);
z0=zeros(XPRECISION,YPRECISION);
z=zeros(XPRECISION,YPRECISION);
for i=1:XPRECISION
    for j=1:YPRECISION
        z0(i,j)=test_func2([x(i);y(j)]);
    end
end
nw=Network2(2,1,HIDEN,LAYERN);

M=moviein(K);
%vidObj = VideoWriter('peaks.avi');
%open(vidObj);
for k=1:K
    input=rand(2,1);
    output=test_func2(input);
    nw=nw.BackPropagation(input,output,LearningDegree);
    xcost(k)=k;
    cost(k)=min(nw.costs,1);
    subplot(1,2,2);
    plot(xcost,cost);
    axis([0,K,0,1]);
    for i=1:XPRECISION
        for j=1:YPRECISION
            z(i,j)=nw.Calculate([x(i);y(j)]);
        end
    end
    subplot(1,2,1);
    surf(xs,ys,z0);
    hold on
    surf(xs,ys,z);
    axis([0,XMAX,0,YMAX,min(min(z0)),max(max(z0))]);
    shading interp
    hold off
    %writeVideo(vidObj,currFrame);
    M(:,k) = getframe;
end
%close(vidObj);
movie(M,1,10);

