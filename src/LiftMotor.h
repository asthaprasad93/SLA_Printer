#ifndef LiftMotor_h
#define LiftMotor_h

class LiftMotor
{
	public: 
		int z;
		bool LimitSwitchBottom, LimitSwitchTop;
		int zmin = 0;
		int zmax = 10000;

		//Methods
		LiftMotor(ofstream &myFile);
		void MoveUp(int deltaZ);
		void MoveDown(int deltaZ);
		void MoveToTopLimit();
		void MoveToBottomLimit();
		void UpdateSwitches(int z);
		void MotorMove(int deltaZ);

};

LiftMotor::LiftMotor(ofstream &myFile)
{
	srand(time(NULL));
	cout << endl << "LIFT MOTOR INITIALIZED!" << endl;
	myFile << endl << "LIFT MOTOR INITIALIZED!" << endl;
	z = rand() % zmax;
	LimitSwitchTop = false;
	LimitSwitchBottom = false;
}


void LiftMotor::MotorMove(int deltaZ)
{
	int moves = 0;
	if (z + deltaZ > zmax || z + deltaZ < zmin)
		cout << "Motor approaching Limit" << endl;
	else
		cout << "...moving from " << z << " to " << z + deltaZ << "..."<< endl;

	//Physical move up
	if (deltaZ >=0)
	{
		
		while(moves < deltaZ)
		{
			z++;
			moves++;

			//Delay of 
			this_thread::sleep_for(std::chrono::milliseconds(1));
			if (z == zmax)
			{
				LimitSwitchTop = true;
				break;
			}
		}

	}

	//Physical move down
	else
	{
		while(moves < abs(deltaZ))
		{
			z--;
			moves++;
			this_thread::sleep_for(std::chrono::milliseconds(1));
			if (z == zmin)
			{
				LimitSwitchBottom = true;
				break;
			}
		}
	}

}



void LiftMotor::MoveDown(int deltaZ)
{

	LiftMotor::MotorMove(deltaZ);

	UpdateSwitches(z);
}

void LiftMotor::MoveUp(int deltaZ)
{

	LiftMotor::MotorMove(deltaZ);

	UpdateSwitches(z);
}

void LiftMotor::MoveToBottomLimit()
{
	int deltaZ = zmin - z;

	LiftMotor::MotorMove(deltaZ);

	UpdateSwitches(z);
	cout << "MOTOR AT BOTTOM" << endl;
}

void LiftMotor::MoveToTopLimit()
{
	int deltaZ = zmax - z;

	LiftMotor::MotorMove(deltaZ);

	UpdateSwitches(z);
	cout << "MOTOR AT TOP" << endl;
}

void LiftMotor::UpdateSwitches(int z)
{
	if (z == zmax)
	{
		LimitSwitchTop = true;
		LimitSwitchBottom = false;
	}

	else if (z == zmin)
	{
		LimitSwitchTop = false;
		LimitSwitchBottom = true;
	}

	else
	{
		LimitSwitchTop = false;
		LimitSwitchBottom = false;
	}
}

#endif