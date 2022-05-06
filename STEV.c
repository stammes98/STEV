#include "STEV.h"

//Print progress bar
void print_progress(size_t count, size_t max) {
	int i;
	const char prefix[] = "Progress: [";
	const char suffix[] = "]";
	const size_t prefix_length = sizeof(prefix) - 1;
	const size_t suffix_length = sizeof(suffix) - 1;
	char *buffer = calloc(100 + prefix_length + suffix_length + 1, 1);

	strcpy(buffer, prefix);
	for (; i < 100; ++i)
	{
		buffer[prefix_length + i] = i < PERCENTAGE(count, max) ? '#' : ' ';
	}

	strcpy(&buffer[prefix_length + i], suffix);
	printf("\b\r%c[2K\r%s", 27, buffer);
	fflush(stdout);
	free(buffer);
}


//Function to square a float
float squared(float x) {
	return (x * x);
}

//Gaussian dispersion function
float conc(float x, float y, float z) {	
	if (Q <= 0.0f) {
		printf("Error! Model is either not initialized or improperly initalized! Don't forget to call initModel()!\nExiting...\n");
		exit(1);
	}
	sy = Iy * x;
	sz = Iz * x;
	if (sy <= 0) {
		sy = 0.01f;
	}
	if (sz <= 0) {
		sz = 0.01f;
	}
	if (0 > x) {
		return 0.0f;
	}
	float preFactor = (Q / (2 * pi * u * sy * sz));
	float factor1 = exp(-squared(y) / (2 * squared(sy)));
	float factor2 = exp(-squared((z - H)) / (2 * squared(sz)));
	float factor3 = exp(-squared((z + H)) / (2 * squared(sz)));
	return preFactor * factor1 * (factor2 + factor3);	
}

//Perform a line integral from 0,0,0 to x, y, z through the concentration field, over 10 million points
//        
//        n=10000000
//I = lim  sum f(r(t_i)) ds
//   ds->0 i=0
//float ds = sqrt(squared(x/1000000.0f) + squared(y/1000000.0f) + squared(z/1000000.0f));
//   
//   r(t) = (x*t)/1e7 + (y*t)/1e7 + (z*t)/1e7
//
float lineInt(float x, float y, float z) {
	if (Q <= 0.0f) {
		printf("Error! Model is either not initalized or improperly initalized! Don't forget to call initModel()!!\nExiting...\n");
		exit(1);
	}

	
	float sum = 0;
	float ds = sqrt(squared(x/10000000.0f) + squared(y/10000000.0f) + squared(z/10000000.0f));	
	
	//printf("Performing line integral from (0, 0, 0) to (%.1f, %.1f, %.1f) along shortest path\n", x, y, z);
	//printf("ds = %.3e\n", ds);

	for (int i = 0; i < 10000000; ++i) {
		float xPos = ((x * i) / 10000000.0f);
		float yPos = ((y * i) / 10000000.0f);
		float zPos = ((z * i) / 10000000.0f);
		sum += (conc(xPos, yPos, zPos) * ds);
	}

	return sum;
}

int writeGrid(float xLower, float xUpper, float yLower, float yUpper, float zUpper, float step) {

}

int initModel(float emissionRate, float windSpeed, float offset, float lateralIntensity, float verticalIntensity) {
	printf("Smoke Transport and Emissions Viewing - STEV\n");
	printf("********************************************\n");
	printf("Model begin\n");


	Q = emissionRate;
	u = windSpeed;
	H = offset;
		
	Iy = lateralIntensity;
	Iz = verticalIntensity;


	printf("Fire emission rate:	%f g/s\n", Q);
	printf("Downwind wind speed:	%f m/s\n", u);
	printf("Vertical offset:	%f m\n\n", H);


	/**
	FILE* fptr;

	if (writeOutput) {	
		printf("Searching region bounded by:\n");
		printf("x: %f m to %f m\n", xMin, xMax);
		printf("yfloat ds = sqrt(squared(x/1000000.0f) + squared(y/1000000.0f) + squared(z/1000000.0f));: %f m to %f m\n", -yRange, yRange);
		printf("z: %f m to %f m\n\n", 0.0f, zRange);
		
		printf("Opening output file: %s\n", outputPath);
	
		
		fptr = fopen(outputPath, "w");
		if (fptr == NULL) {
			printf("Critical error opening output file! Exiting...\n");
			exit(-1);
		}

		size_t stepX = (size_t) ((xMax - xMin) / step);
		size_t stepY = (size_t) ((yRange + yRange) / step);
		size_t stepZ = (size_t) (zRange / step);
		size_t steps = stepX * stepY * stepZ;	
	
		size_t cStep = 0;
	
		printf("Taking %i steps\n\n", (int) steps);
		for (float x = xMin; x <= xMax; x += step) {
			for (float y = -yRange; y <= yRange; y += step){
				for (float z = 0; z <= zRange; z += step) {
					float cC = conc(x, y, z);
					print_progress(cStep, steps);
					cStep++;
					//printf("%i\n", (int)step);
					fprintf(fptr, "%f, %f, %f, %f\n", x, y, z, cC);
					if (fabs(x) < 5.0f && fabs(y) < 5.0f && fabs(z) < 5.0f) {
						//printf("%f, %f, %f: %f\n", x, y, z, cC);
						//printf("%f\n", fabs(x));
					}
				}
			}
		}
		fclose(fptr);
		printf("\n");
	}
	**/
	//Integral to top of view

	/**
	float topPathConc = lineInt(0.0f, 0.0f, 200.0f);
	printf("Top path integral conc: %f g\n", topPathConc);

	float noSmokeInt = lineInt(-200.0f, 0, 200.0f);
	printf("Smokeless integral: %f g\n\n", noSmokeInt);

	fptr = fopen(intOut, "w");
	

	for (int i = 1; i < 96; ++i) {
		float angleX = 200.0f * tan((i * pi) / 180.0f);
		float integrand = lineInt(angleX, 0, 200.0f);
		printf("Angle: %i - smoke mass: %f\n", i, integrand);
		fprintf(fptr,

	fclose(fptr);
	**/
	return 0;
}
