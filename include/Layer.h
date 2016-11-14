#ifndef Layer_h
#define Layer_h

class Layer
{
	public:
		int index;
		int FirstApproachWait;
		int BurnInApproachWait;
		int ModelApproachWait;
		string imageLoc;

		//Methods
		Layer();
};

Layer::Layer()
{
	index = 0;
	FirstApproachWait = 0;
	ModelApproachWait = 0;
}

#endif