#ifndef Projector_h
#define Projector_h

class Projector 
{

		//Variables
		bool LED = false;
		string CurrentImageLoc; 
		Mat CurrentImage;
	
	public:
		//Methods
		Projector(ofstream &myFile);
		void LoadSlice(string imageLoc, ofstream &myFile);
		void TurnOnLED(ofstream &myFile);
		void TurnOffLED(ofstream &myFile);
		void PrintCurrentSlice(ofstream &myFile);
		void DisplayCurrentSlice();

};


Projector::Projector(ofstream &myFile)
{
	//Initializez Projector

	cout << endl << "PROJECTOR INITIALIZED!" << endl << endl;
	myFile << endl << "PROJECTOR INITIALIZED!" << endl << endl;
}

void Projector::DisplayCurrentSlice()
{
	//Displays the current image on an openCV window

	namedWindow("Current Image", WINDOW_NORMAL);
	cv::Point pt = Point(0,0);
	putText(CurrentImage, CurrentImageLoc, Point(30,30), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(255, 255, 255), 1, 8, false);
	imshow("Current Image", CurrentImage);
	waitKey(20000);

}

void Projector::PrintCurrentSlice(ofstream &myFile)
{
	// Pronts location of current slice
	
	cout << "Current Projector Image: " << CurrentImageLoc << endl;
	myFile << "Projector Image: " << CurrentImageLoc << endl;

}

void Projector::LoadSlice(string imageLoc, ofstream &myFile)
{

	CurrentImageLoc = imageLoc;
	CurrentImage = imread(imageLoc, 1);

	//Display image in seperate thread
	thread t_display(&Projector::DisplayCurrentSlice, this);
	t_display.detach();

	if (!CurrentImage.data)
	{
		cout << "No Image data!" << endl;
		myFile << "No Image data!" << endl;

	}
	else
	{
		cout << "New Image loaded" << endl;
		myFile << "New Image loaded" << endl;
	}


}

void Projector::TurnOffLED(ofstream &myFile)
{
	cout << "LED off " << endl;
	myFile << "LED off " << endl;
	LED = false;

}

void Projector::TurnOnLED(ofstream &myFile)
{
	cout << "LED on (Exposing...)" << endl;
	myFile << "LED on (Exposing...)" << endl;
	LED = true;
}

#endif
	
