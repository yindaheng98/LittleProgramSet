clear;
mov=VideoReader('raw.avi');

N = 20;% N frames to train the Gaussian model
h = fspecial('gaussian');
imagedata = filter2(h,rgb2gray(readFrame(mov)));%根据实际图片信息进行修改
mu = imagedata;
[m,n] = size(mu);
cov = zeros(m,n);
pro = zeros(m,n);
sav_mu =  mu;
a = 0.01;
for i=1:N
    tmp =filter2(h,rgb2gray(readFrame(mov)));
    mu = (tmp+(i-1)*sav_mu)./i;
    cov = ((tmp-mu).^2+(i-1)*cov)./(i)+(mu-sav_mu).^2;
    sav_mu = mu;
end
cov = cov+0.001;    %防止cov为0
% test the new frame
for num = N+1:499
    imagedata = double(filter2(h,rgb2gray(readFrame(mov))));
    T=0.1e-3;   % 阈值，可调节
    pro = (2*pi)^(-1/2)*exp(-0.5*(imagedata-mu).^2./cov)./sqrt(cov)< T;
%     pro = (2*pi)^(-1/2)*exp(-0.5*(imagedata-mu).^2./cov)./sqrt(cov);
    mu = mu +a*(1-pro).*(imagedata-mu);%(1-a)*mu+a*(imagedata-mu);
    cov = cov + a*(1-pro).*((imagedata-mu).^2-cov);%(1-a)*cov+a*(imagedata-mu).^2;
    imshow(mat2gray(pro)),title(sprintf('frame number %d',floor(num)));
    Mov1(num-N)  = im2frame(uint8(255*pro),gray);% put frames into movie
end;
movie2avi(Mov1,'单高斯N20T01','fps',15);