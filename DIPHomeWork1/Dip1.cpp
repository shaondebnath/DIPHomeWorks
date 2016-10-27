//============================================================================
// Name        : Dip1.cpp
// Author      : Ronny Haensch
// Version     : 2.0
// Copyright   : -
// Description : 
//============================================================================

#include "Dip1.h"
#include <iostream>

// function that performs some kind of (simple) image processing
/*
img	input image
return	output image
*/
float Dip1::alphaValue(int a)
{

	if (a == 1) {
		std::cout << "Enter alpha value (1.0-3.0): "; std::cin >> alpha;
	}
	else {
		std::cout << "Wrong input! Please enter alpha value (1.0-3.0): "; std::cin >> alpha;
	}

	if (alpha<1.0 || alpha > 3.0)
		alpha = alphaValue(2);

	return alpha;
}
int Dip1::betaValue(int a)
{

	if (a == 1) {
		std::cout << "Enter beta value (0-100): "; std::cin >> beta;
	}
	else {
		std::cout << "Wrong input!!! Please enter beta value (0-100): "; std::cin >> beta;
	}
	if (beta<0 || beta > 100)
		beta = betaValue(2);

	return beta;
}

int Dip1::chooseOption(int a)
{

	if (a == 1) {
		std::cout << "Press 1 for GrayScale, Press 2 for Color: "; std::cin >> selectedOption;
	}
	else {
		std::cout << "Wrong input!!! Press 1 for GrayScale, Press 2 for Color:"; std::cin >> selectedOption;
	}

	if (selectedOption == 1 || selectedOption == 2)
		return selectedOption;
	else
		selectedOption = chooseOption(2);

	return selectedOption;
}

Mat Dip1::doSomethingThatMyTutorIsGonnaLike(Mat& img) {

	// TO DO !!!
	//Mat myImg; //for pencil sketch
	Mat myImg = Mat::zeros(img.size(), img.type());
	
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			for (int rgb = 0; rgb < 3; rgb++)
			{
				myImg.at<Vec3b>(y, x)[rgb] = saturate_cast<uchar>(alpha*(img.at<Vec3b>(y, x)[rgb]) + beta);
			}
		}
	}
	
	/*
	Mat coloredArt;
	stylization(img, myImg, 60, 0.45f);
	pencilSketch(img, myImg, coloredArt, 160, 0.04f, 0.05f);
	//edgePreservingFilter(Mat src, Mat dst, int flags = 1, float sigma_s = 60, float sigma_r = 0.4f)
	if(selectedOption==1)
		return myImg;
	else
		return coloredArt;
		*/
	return myImg;

}



/* *****************************
GIVEN FUNCTIONS
***************************** */

// function loads input image, calls processing function, and saves result
/*
fname	path to input image
*/
void Dip1::run(string fname) {

	// window names
	string win1 = string("Original image");
	string win2 = string("Result");

	// some images
	Mat inputImage, outputImage;

	//selectedOption = chooseOption(1);
	alpha = alphaValue(1);
	beta = betaValue(1);

	// load image
	cout << "load image" << endl;
	inputImage = imread(fname);
	cout << "done" << endl;

	// check if image can be loaded
	if (!inputImage.data) {
		cout << "ERROR: Cannot read file " << fname << endl;
		cout << "Press enter to continue..." << endl;
		cin.get();
		exit(-1);
	}
	

	// show input image
	namedWindow(win1.c_str());
	imshow(win1.c_str(), inputImage);

	// do something (reasonable!)
	
	outputImage = doSomethingThatMyTutorIsGonnaLike(inputImage);

	// show result
	namedWindow(win2.c_str());
	imshow(win2.c_str(), outputImage);

	// save result
	imwrite("result.jpg", outputImage);

	// wait a bit
	waitKey(0);

}

// function loads input image and calls the processing functions
// output is tested on "correctness" 
/*
fname	path to input image
*/
void Dip1::test(string fname) {

	// some image variables
	Mat inputImage, outputImage;

	// load image
	inputImage = imread(fname);

	// check if image can be loaded
	if (!inputImage.data) {
		cout << "ERROR: Cannot read file " << fname << endl;
		cout << "Continue with pressing enter..." << endl;
		cin.get();
		exit(-1);
	}

	// create output
	outputImage = doSomethingThatMyTutorIsGonnaLike(inputImage);
	// test output
	test_doSomethingThatMyTutorIsGonnaLike(inputImage, outputImage);

}

// function loads input image and calls processing function
// output is tested on "correctness" 
/*
inputImage	input image as used by doSomethingThatMyTutorIsGonnaLike()
outputImage	output image as created by doSomethingThatMyTutorIsGonnaLike()
*/
void Dip1::test_doSomethingThatMyTutorIsGonnaLike(Mat& inputImage, Mat& outputImage) {

	// ensure that input and output have equal number of channels
	if ((inputImage.channels() == 3) && (outputImage.channels() == 1))
		cvtColor(inputImage, inputImage, CV_BGR2GRAY);

	// split (multi-channel) image into planes
	vector<Mat> inputPlanes, outputPlanes;
	split(inputImage, inputPlanes);
	split(outputImage, outputPlanes);

	// number of planes (1=grayscale, 3=color)
	int numOfPlanes = inputPlanes.size();

	// calculate and compare image histograms for each plane
	Mat inputHist, outputHist;
	// number of bins
	int histSize = 100;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;
	double sim = 0;
	for (int p = 0; p < numOfPlanes; p++) {
		// calculate histogram
		calcHist(&inputPlanes[p], 1, 0, Mat(), inputHist, 1, &histSize, &histRange, uniform, accumulate);
		calcHist(&outputPlanes[p], 1, 0, Mat(), outputHist, 1, &histSize, &histRange, uniform, accumulate);
		// normalize
		inputHist = inputHist / sum(inputHist).val[0];
		outputHist = outputHist / sum(outputHist).val[0];
		// similarity as histogram intersection
		sim += compareHist(inputHist, outputHist, CV_COMP_INTERSECT);
	}
	sim /= numOfPlanes;

	// check whether images are to similar after transformation
	if (sim >= 0.8)
		cout << "Warning: The input and output image seem to be quite similar (similarity = " << sim << " ). Are you sure your tutor is gonna like your work?" << endl;

}
