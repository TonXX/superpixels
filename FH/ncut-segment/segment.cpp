/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"

#include<ctime>

using namespace std;
int main(int argc, char **argv) {
  //if (argc != 6) {
  //  fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
  //  return 1;
	//}
	clock_t start, end;
	start = clock();
  float sigma = 0;
  float k = 125;
  int min_size = 220;
	
  printf("loading input image.\n");
  image<rgb> *input = loadPPM("./2.ppm");
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  savePPM(seg, "2_result.ppm");

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");
  end = clock();
  double endtime = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "Total time:" << endtime << endl;		//sΪ��λ
  cout << "Total time:" << endtime * 1000 << "ms" << endl;	//msΪ��λ
  getchar();
  return 0;
}

