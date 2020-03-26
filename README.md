
######################################################


        #######方法1：superpixels_seeds#####
		
		
######################################################

超像素分割方法，采用论文 SEEDS: Superpixels Extracted via Energy-Driven Sampling 提出的方法，对于物体的边界具有较好的保留，如下图所示。可以辅助目标检测中制作Banchmark。

本工程在其基础上，获得的图像labels和contours，然后分别实现区域种子填充，Windows下编译环境为： OpenCV CMake Visual Studio 工程demo包括：

SuperSeedsTest: SEEDS 提供的用例，可获取超像素分割labels和contours SeedFillTest : 基于labels种子填充子块 BoundaryFillTest : 基于contours种子填充子块

备注：无需配置cmake也行，自己手动添加文件头文件和源文件
######################################################


#######方法2：ncuts：可以在matlab2012等以上版本运行#####


######################################################
Installation instructions Make sure you have MATLAB 7.0 or higher and the Image Processing Toolbox. Running the scripts

Unzip the files to some directory mydir
In matlab, type: cd mydir init compileDir //only need to be run once to compile mex-files script_ncut_multiscale // script for basic multiscale segmentation script_ncut_multiscale_timing // script for computation time Note: if you are using AMD 64 and comileDir brings errors, this might be due to a bug in gcc. The following should fix it: edit the config file for compiling matlab mex files. It is typically located under: /home/username/.matlab/R14SP3/mexopts.sh. Go to the section

######################################################


         ############ 方法3：FH ############
		 
		 
######################################################
Implementation of the segmentation algorithm described in:

Efficient Graph-Based Image Segmentation Pedro F. Felzenszwalb and Daniel P. Huttenlocher International Journal of Computer Vision, 59(2) September 2004.

The program takes a color image (PPM format) and produces a segmentation with a random color assigned to each region.

Type "make" to compile "segment".

Run "segment sigma k min input output".

The parameters are: (see the paper for details)

sigma: Used to smooth the input image before segmenting it. k: Value for the threshold function. min: Minimum component size enforced by post-processing. input: Input image. output: Output image.

Typical parameters are sigma = 0.5, k = 500, min = 20. Larger values for k result in larger components in the result.



######################################################


############## 方法4：TurboPixels64  ##############


######################################################
Put all the code into a directory (for example 'my_dir')

Run 'cd my_dir'

Start matlab

The subdirectory 'lsmlib' needs to be added to matlab's path. This is done in demo_superpixels.m, or you can do it manually by typing 'addpath('lsmlib')'

Run 'make'. To work, MEX needs to be properly configured. Ignore the warnings.

Load an image 'img = im2double(imread(image_filename))'. This ensures that the loaded image is in double format with every component in 0..1 range. Another method for loading images can be used as long as the resulting image is a 2D array of doubles. The image can be RGB or grayscale, although it only matters for displaying purposes.

Run the superpixels() function in superpixels.m. The header describes the different parameters.

demo_superpixels.m gives one example of using the code.

Examples:

Getting 1500 superpixels without intermediate display
img = im2double(imread('lizard.jpg')); [phi,boundary,disp_img] = superpixels(img, 1500); imagesc(disp_img);

Getting superpixels with an intermediate display every 5 timesteps
img = im2double(imread('lizard.jpg')); [phi,boundary,disp_img] = superpixels(img, 1500, 5); imagesc(disp_img);

Getting superpixels while saving every frame of the evolution into a movie
img = im2double(imread('lizard.jpg')); [phi,boundary,disp_img, frames] = superpixels(img, 1500, 1); disp('Press any key to view the evolution movie'); pause; movie(frames);

######################################################


    ######### 方法5：SLIC   ######### 
	
	
######################################################
