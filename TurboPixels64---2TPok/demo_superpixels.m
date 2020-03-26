% Runs the superpixel code on the lizard image
tic;
addpath('lsmlib');
img = im2double(imread('2.png'));
[phi,boundary,disp_img] = superpixels(img, 200);
imagesc(disp_img);
imwrite(disp_img,'2_result.png');
toc;
t=toc;
disp(t);