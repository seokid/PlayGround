#include "CFileAlter.h"
#include <direct.h>
#include <filesystem>
#include <io.h>

void CFileAlter::FileNameChange()
{
	string DataPath = "E:\\git\\unreal\\RaftDedicated\\Content\\Unit\\Player\\Female\\Anim\\";
	string path = DataPath + "*.*";
	string ChangeStartName = "AS_Female";
	string ChangeEndName = "";

	intptr_t handle;
	struct _finddata_t fd;

	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
		cout << "No File in Directory" << endl;

	int i = 0;
	string OldFilePath = DataPath + fd.name;
	do
	{
		string OldFileName = fd.name;
		string OldFilePath = DataPath + OldFileName;
		
		int Idx = OldFileName.find("Anim");
		if (string::npos == Idx)
			continue;

		string NewFileName = ChangeStartName + OldFileName.substr(Idx + 4, OldFileName.size()) + ChangeEndName;
		string NefFilePath = DataPath + NewFileName;
		rename(OldFilePath.c_str(), NefFilePath.c_str());

	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);
}
