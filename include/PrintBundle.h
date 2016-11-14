#ifndef PrintBundle_h
#define PrintBundle_h

#include "Layer.h"

class PrintBundle 
{
	public:
		//Variables
		int numLayers;
		string Folder;
		queue <Layer> Layers;

		//Methods
		PrintBundle(string location);
		void LoadPrintSettings();
		void LoadLayerSettings();

};


PrintBundle::PrintBundle(string FolderLocation)
{
	Folder = FolderLocation;
	LoadLayerSettings();
}

void PrintBundle::LoadLayerSettings()
{
	ifstream LayerInfoFile;
	string file = Folder + "/layersettings.csv";
	LayerInfoFile.open(file.c_str());
	
	numLayers = 0;
	string line;
	if (LayerInfoFile.is_open())
	{
		//Get rid of the first row
		getline(LayerInfoFile, line);

		//Parse remaining rows
		while(getline(LayerInfoFile, line))
		{
			vector <string> rowData;
			Layer L;

			while(line.length() != 0 && line.find(',') != string::npos)
			{
				size_t pos;
				string OneAttribute;
				pos = line.find_first_of(',');
				OneAttribute = line.substr(0, pos);
				rowData.push_back(OneAttribute);
				line.erase(0, pos+1);

			}
			rowData.push_back(line);

			L.index = atoi(rowData[0].c_str());
			L.FirstApproachWait = atoi(rowData[1].c_str());
			L.BurnInApproachWait = atoi(rowData[2].c_str());
			L.ModelApproachWait = atoi(rowData[3].c_str());
			L.imageLoc = Folder + "/slice_" + to_string(numLayers+1) + ".png";
			
			Layers.push(L);
			numLayers++;

		}
		
	}

	else
		cout << "Unable to read in Settings file. Check again" << endl;

	numLayers = Layers.size();

	LayerInfoFile.close();

}

#endif
	
