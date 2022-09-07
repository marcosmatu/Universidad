
#include <CL/sycl.hpp>

using  namespace  cl::sycl;

#define MAX_WINDOW_SIZE 5*5

void buble_sort2(float array[], int size)
{
	int i, j;
	float tmp;

	for (i=1; i<size; i++)
		for (j=0 ; j<size - i; j++)
			if (array[j] > array[j+1]){
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
}

void remove_noise_SYCL(sycl::queue Q, float *im, float *image_out, 
	float thredshold, int window_size,
	int height, int width)
{
	/* To Do */
	//float window;
	//auto buf = sycl::buffer{&window, sycl::range{MAX_WINDOW_SIZE}};
	int ws2 = (window_size-1)>>1; 

	Q.submit([&](handler &h) {
	
	//	auto readAcc = sycl::accessor{buf, h, sycl::read_write};			
		
		
		// Submit the kernel
		h.parallel_for(range<2>(height-ws2,width-ws2), [=](id<2> item) {
			auto i = item[0];
			auto j = item[1];
			float window[MAX_WINDOW_SIZE];
			if((i > 0) && (j > 0)){
				for (int ii =-ws2; ii<=ws2; ii++)
				for (int jj =-ws2; jj<=ws2; jj++)
					window[(ii+ws2)*window_size + jj+ws2] = im[(i+ii)*width + j+jj];

			// SORT
			buble_sort2(window, window_size*window_size);
			float median = window[(window_size*window_size-1)>>1];
			if (fabsf((median-im[i*width+j])/median) < thredshold)
				image_out[i*width + j] = im[i*width+j];
			else
				image_out[i*width + j] = median;
			}
		}); // End of the kernel function
	}).wait();  // End of the queue commands we waint on the event reported.
	
}
