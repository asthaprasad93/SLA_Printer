#include "include.h"

//classes
#include "Projector.h"
#include "LiftMotor.h"
#include "PrintBundle.h"


double SecToMilli = 1000;
double ModelExposureWait = 4500*SecToMilli;
double LayerThicknessMicrons = 100;

int start(PrintBundle job, LiftMotor motor, Projector proj, ofstream &myFile)
{
	int LayerNum = 1;
	Layer L = job.Layers.front();

	cout << "Plate initial position : " << motor.z << endl;
	myFile << "Plate initial position : " << motor.z << endl;
	motor.MoveToTopLimit();

	//Move from top to bottom and load image simultaneously
	thread t_moveBOTTOM(&LiftMotor::MoveToBottomLimit, ref(motor));
	proj.LoadSlice(L.imageLoc, myFile);
	t_moveBOTTOM.join();

	cout << "==================================================" << endl;
	myFile << "==================================================" << endl;

	while (!job.Layers.empty())
	{

		cout << "LAYER " << LayerNum << endl;
		myFile << "LAYER " << LayerNum << endl;
		proj.PrintCurrentSlice(myFile);

		//Delay
		cout << "Waiting for Model Approach Time :" << L.ModelApproachWait << "ms.." << endl;
		myFile << "Waiting for Model Approach Time :" << L.ModelApproachWait << "ms.." << endl;
		
		this_thread::sleep_for(std::chrono::milliseconds(L.ModelApproachWait));

		//Exposure
		milliseconds start = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
		milliseconds now = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
		proj.TurnOnLED(myFile);
		while((now.count()-start.count()) < ModelExposureWait)
			now = duration_cast <milliseconds> (system_clock::now().time_since_epoch());
		proj.TurnOffLED(myFile);
		cout << "Exposure time : " << now.count()-start.count() << " ms" << endl;
		myFile << "Exposure time : " << now.count()-start.count() << " ms" << endl;
		
		//Move up
		int deltaZ = LayerThicknessMicrons;
		myFile << "...moving from " << motor.z << " to " << motor.z + deltaZ << "..."<< endl;
		motor.MoveUp(deltaZ);

		//Pop layer and load next layer if it exists
		job.Layers.pop();
		if (!job.Layers.empty())
		{
			L = job.Layers.front();
			proj.LoadSlice(L.imageLoc, myFile);
			LayerNum++;
		}
		else
		{
			cout << "End of print " << endl;
			myFile << "End of print " << endl;
		}
		
		cout << "==================================================" << endl;
		myFile << "==================================================" << endl;
			
	}

	motor.MoveToTopLimit();
	cout << "Currently at " << motor.z << endl;

	return 0;

}


int main(int argc, char*argv[])
{

	ofstream myFile;
	myFile.open("Log.txt");

	//Initialize Print Bundle, Motor and Projector
	PrintBundle CurrentJob(argv[1]);
	LiftMotor motor(myFile);
	Projector proj(myFile);

	//Start Print 
	start(CurrentJob, motor, proj, myFile);

	myFile.close();

	return 0;

}