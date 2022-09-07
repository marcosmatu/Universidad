#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <inttypes.h>

#include "routinesGPU.h"


#define PI 3.141593
#define BLOCK_SIZE 16


__global__ void noiseReduction(uint8_t *im,float *NR,int height, int width){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	int j = threadIdx.y + blockDim.y * blockIdx.y;

	if(i >= 2 && j >= 2 && i < (height - 2) && j < (width - 2)){
					// Noise reduction
			NR[i*width+j] =
				 (2.0*im[(i-2)*width+(j-2)] +  4.0*im[(i-2)*width+(j-1)] +  5.0*im[(i-2)*width+(j)] +  4.0*im[(i-2)*width+(j+1)] + 2.0*im[(i-2)*width+(j+2)]
				+ 4.0*im[(i-1)*width+(j-2)] +  9.0*im[(i-1)*width+(j-1)] + 12.0*im[(i-1)*width+(j)] +  9.0*im[(i-1)*width+(j+1)] + 4.0*im[(i-1)*width+(j+2)]
				+ 5.0*im[(i  )*width+(j-2)] + 12.0*im[(i  )*width+(j-1)] + 15.0*im[(i  )*width+(j)] + 12.0*im[(i  )*width+(j+1)] + 5.0*im[(i  )*width+(j+2)]
				+ 4.0*im[(i+1)*width+(j-2)] +  9.0*im[(i+1)*width+(j-1)] + 12.0*im[(i+1)*width+(j)] +  9.0*im[(i+1)*width+(j+1)] + 4.0*im[(i+1)*width+(j+2)]
				+ 2.0*im[(i+2)*width+(j-2)] +  4.0*im[(i+2)*width+(j-1)] +  5.0*im[(i+2)*width+(j)] +  4.0*im[(i+2)*width+(j+1)] + 2.0*im[(i+2)*width+(j+2)])
				/159.0;
	} 
}

__global__ void gradienteImagen(float *NR,float *G, float *phi, int height, int width){
	
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	int j = threadIdx.y + blockDim.y * blockIdx.y;
	float Gy, Gx, phi_thread;

	if(i >= 2 && j >= 2 && i < (height - 2) && (j < width - 2)){
		Gx = 
				 (1.0*NR[(i-2)*width+(j-2)] +  2.0*NR[(i-2)*width+(j-1)] +  (-2.0)*NR[(i-2)*width+(j+1)] + (-1.0)*NR[(i-2)*width+(j+2)]
				+ 4.0*NR[(i-1)*width+(j-2)] +  8.0*NR[(i-1)*width+(j-1)] +  (-8.0)*NR[(i-1)*width+(j+1)] + (-4.0)*NR[(i-1)*width+(j+2)]
				+ 6.0*NR[(i  )*width+(j-2)] + 12.0*NR[(i  )*width+(j-1)] + (-12.0)*NR[(i  )*width+(j+1)] + (-6.0)*NR[(i  )*width+(j+2)]
				+ 4.0*NR[(i+1)*width+(j-2)] +  8.0*NR[(i+1)*width+(j-1)] +  (-8.0)*NR[(i+1)*width+(j+1)] + (-4.0)*NR[(i+1)*width+(j+2)]
				+ 1.0*NR[(i+2)*width+(j-2)] +  2.0*NR[(i+2)*width+(j-1)] +  (-2.0)*NR[(i+2)*width+(j+1)] + (-1.0)*NR[(i+2)*width+(j+2)]);


		Gy = 
				 ((-1.0)*NR[(i-2)*width+(j-2)] + (-4.0)*NR[(i-2)*width+(j-1)] +  (-6.0)*NR[(i-2)*width+(j)] + (-4.0)*NR[(i-2)*width+(j+1)] + (-1.0)*NR[(i-2)*width+(j+2)]
				+ (-2.0)*NR[(i-1)*width+(j-2)] + (-8.0)*NR[(i-1)*width+(j-1)] + (-12.0)*NR[(i-1)*width+(j)] + (-8.0)*NR[(i-1)*width+(j+1)] + (-2.0)*NR[(i-1)*width+(j+2)]
				+    2.0*NR[(i+1)*width+(j-2)] +    8.0*NR[(i+1)*width+(j-1)] +    12.0*NR[(i+1)*width+(j)] +    8.0*NR[(i+1)*width+(j+1)] +    2.0*NR[(i+1)*width+(j+2)]
				+    1.0*NR[(i+2)*width+(j-2)] +    4.0*NR[(i+2)*width+(j-1)] +     6.0*NR[(i+2)*width+(j)] +    4.0*NR[(i+2)*width+(j+1)] +    1.0*NR[(i+2)*width+(j+2)]);
		
		G[i*width+j] = sqrtf((Gx*Gx)+(Gy*Gy));	//G = √Gx²+Gy²
		phi_thread = atan2f(fabs(Gy),fabs(Gx));

		if(fabs(phi_thread)<=PI/8 ) phi[i*width+j] = 0;
		else if (fabs(phi_thread)<= 3*(PI/8)) phi[i*width+j] = 45;
		else if (fabs(phi_thread) <= 5*(PI/8)) phi[i*width+j] = 90;
		else if (fabs(phi_thread) <= 7*(PI/8)) phi[i*width+j] = 135;
		else phi[i*width+j] = 0;
	}
}

__global__ void edge(float *G, float *phi,uint8_t *image_out,int height, int width){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	int j = threadIdx.y + blockDim.y * blockIdx.y;
	int ii, jj;
	float lowthres, hithres;
	uint8_t pedge = 0;

	if(i >= 3 && j >= 3 && i < (height - 3) && (j < width - 3)){
		if(phi[i*width+j] == 0){
				if(G[i*width+j]>G[i*width+j+1] && G[i*width+j]>G[i*width+j-1]) //edge is in N-S
					pedge = 1;

			} else if(phi[i*width+j] == 45) {
				if(G[i*width+j]>G[(i+1)*width+j+1] && G[i*width+j]>G[(i-1)*width+j-1]) // edge is in NW-SE
					pedge = 1;

			} else if(phi[i*width+j] == 90) {	
				if(G[i*width+j]>G[(i+1)*width+j] && G[i*width+j]>G[(i-1)*width+j]) //edge is in E-W
					pedge = 1;

			} else if(phi[i*width+j] == 135) {
				if(G[i*width+j]>G[(i+1)*width+j-1] && G[i*width+j]>G[(i-1)*width+j+1]) // edge is in NE-SW
					pedge = 1;
			}
	
		lowthres = 1000.0f/2;
		hithres  = 2*(1000.0f);

		image_out[i*width+j] = 0;
		if(G[i*width+j]>hithres && pedge)
			image_out[i*width+j] = 255;
		else if(pedge && G[i*width+j]>=lowthres && G[i*width+j]<hithres)
			// check neighbours 3x3
			for (ii=-1;ii<=1; ii++)
				for (jj=-1;jj<=1; jj++)
					if (G[(i+ii)*width+j+jj]>hithres){
						image_out[i*width+j] = 255;
					//	ii = 2;
						//jj=2;
					}
	}
	
	
}
__global__
void houghtransform(uint8_t *im, uint32_t *accumulators, float *sin_table, float *cos_table, int height, int width)
{

	int i = threadIdx.x + blockDim.x * blockIdx.x;
	int j = threadIdx.y + blockDim.y * blockIdx.y; 
	int theta;

	float hough_h = ((sqrt(2.0) * (float)(height>width?height:width)) / 2.0);

	

	float center_x = width/2.0; 
	float center_y = height/2.0;
	if(i >= 0 && j >= 0 && i < height && j < width){ //Quitar los mayor = que 0
		if( im[ (i*width) + j] > 250 ) // Pixel is edge  
		{  
			for(theta=0;theta<180;theta++)  
			{  
				float rho = ( ((float)j - center_x) * cos_table[theta]) + (((float)i - center_y) * sin_table[theta]);
				atomicAdd(&accumulators[(int)((round(rho + hough_h) * 180.0)) + theta],1);


			} 
		} 
	}	 
}

void getlines(int threshold, uint32_t *accumulators, int accu_width, int accu_height, int width, int height, 
	float *sin_table, float *cos_table,
	int *x1_lines, int *y1_lines, int *x2_lines, int *y2_lines, int *lines)
{
	int rho, theta;
	uint32_t max;
	for(rho=0;rho<accu_height;rho++)
	{

		for(theta=0;theta<accu_width;theta++)  
		{  
			
			if(accumulators[(rho*accu_width) + theta] >= threshold)  
			{  
				//Is this point a local maxima (9x9)  
				max = accumulators[(rho*accu_width) + theta]; 
				
				for(int ii=-4;ii<=4;ii++)  
				{  
					for(int jj=-4;jj<=4;jj++)  
					{  
						if( (ii+rho>=0 && ii+rho<accu_height) && (jj+theta>=0 && jj+theta<accu_width) )  
						{  
							if( accumulators[((rho+ii)*accu_width) + (theta+jj)] > max )  
							{
								max = accumulators[((rho+ii)*accu_width) + (theta+jj)];
							}  
						}  
					}  
				}  

				if(max == accumulators[(rho*accu_width) + theta]) //local maxima
				{
					int x1, y1, x2, y2;  
					x1 = y1 = x2 = y2 = 0;  

					if(theta >= 45 && theta <= 135)  
					{
						if (theta>90) {
							//y = (r - x cos(t)) / sin(t)  
							x1 = width/2;  
							y1 = ((float)(rho-(accu_height/2)) - ((x1 - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);
							x2 = width;  
							y2 = ((float)(rho-(accu_height/2)) - ((x2 - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);  
						} else {
							//y = (r - x cos(t)) / sin(t)  
							x1 = 0;  
							y1 = ((float)(rho-(accu_height/2)) - ((x1 - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);
							x2 = width*2/5;  
							y2 = ((float)(rho-(accu_height/2)) - ((x2 - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2); 
						}
					} else {
						//x = (r - y sin(t)) / cos(t);  
						y1 = 0;  
						x1 = ((float)(rho-(accu_height/2)) - ((y1 - (height/2) ) * sin_table[theta])) / cos_table[theta] + (width / 2);  
						y2 = height;  
						x2 = ((float)(rho-(accu_height/2)) - ((y2 - (height/2) ) * sin_table[theta])) / cos_table[theta] + (width / 2);  
					}
					x1_lines[*lines] = x1;
					y1_lines[*lines] = y1;
					x2_lines[*lines] = x2;
					y2_lines[*lines] = y2;
					(*lines)++;
				}
			}
		}
	}
}



void line_asist_GPU(uint8_t *im, int height, int width,
	uint8_t *imEdge, float *NR, float *G, float *phi, float *Gx, float *Gy, uint8_t *pedge,
	float *sin_table, float *cos_table, 
	uint32_t *accum, int accu_height, int accu_width,
	int *x1, int *x2, int *y1, int *y2, int *nlines)
{
	//printf("%d",height);
	/* To do */

	
	uint8_t *imGPU;
	float *NRGPU;
	float *GGPU;
	float *phiGPU;
	uint8_t *im_outGPU;
	uint32_t *accumGPU;
	int threshold;
	float *sin_tableGPU;
	float *cos_tableGPU;
	
	
	cudaMalloc((void**)&imGPU, sizeof(uint8_t)*height*width);
	cudaMalloc((void**)&NRGPU, sizeof(float)*height*width);
	cudaMalloc((void**)&GGPU, sizeof(float)*height*width);
	cudaMalloc((void**)&phiGPU, sizeof(float)*height*width);;
	cudaMalloc((void**)&im_outGPU, sizeof(uint8_t)*height*width);

	dim3 threadsPerBlock(BLOCK_SIZE,BLOCK_SIZE);	
	dim3 numBlocks((height/BLOCK_SIZE + 1),(width/BLOCK_SIZE)+1);
	
	cudaMemcpy(imGPU,im, sizeof(uint8_t)*height*width, cudaMemcpyHostToDevice);
	noiseReduction<<<numBlocks,threadsPerBlock>>>(imGPU, NRGPU, height, width);	

	gradienteImagen<<<numBlocks,threadsPerBlock>>>(NRGPU, GGPU, phiGPU,height, width);

	edge<<<numBlocks,threadsPerBlock>>>(GGPU, phiGPU,im_outGPU, height, width);


	//cudaMemcpy(pedgeGPU,im, sizeof(uint8_t)*height*width, cudaMemcpyHostToDevice);

	cudaMalloc((void**)&accumGPU, accu_width*accu_height*sizeof(uint32_t));
	cudaMalloc((void**)&sin_tableGPU, sizeof(float)*180);
	cudaMalloc((void**)&cos_tableGPU, sizeof(float)*180);
	
	cudaMemcpy(sin_tableGPU,sin_table, sizeof(float)*180, cudaMemcpyHostToDevice);
	cudaMemcpy(cos_tableGPU,cos_table, sizeof(float)*180, cudaMemcpyHostToDevice);

	cudaMemset(accumGPU, 0, (sizeof(uint32_t) * accu_width * accu_height));
	houghtransform<<<numBlocks,threadsPerBlock>>>(im_outGPU,accumGPU, sin_tableGPU, cos_tableGPU,height, width);
	//Pasarselo al accum
	cudaMemcpy(accum, accumGPU, accu_width*accu_height*sizeof(uint32_t), cudaMemcpyDeviceToHost);

	if (width>height) threshold = width/6;
	else threshold = height/6;

	
	getlines(threshold, accum, accu_width, accu_height, width, height, 
		sin_table, cos_table,
		x1, y1, x2, y2, nlines);


	cudaFree(imGPU);	
	cudaFree(NR);	
	cudaFree(GGPU);
	cudaFree(phiGPU);
	cudaFree(im_outGPU);
	cudaFree(accumGPU);
	cudaFree(sin_tableGPU);
	cudaFree(cos_tableGPU);
			
			
	
}
