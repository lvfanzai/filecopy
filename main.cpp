#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <direct.h>

#include<iostream>
#include<windows.h>
using namespace std;

char *suffix = ".pdf";

int main()
{
	FILE *fd;
	FILE *fd_new;
	char filename[512][1024] = { 0 };
	char namestring[1024];
	int file_count = 0;
	int final_count = 0;

	_mkdir("LAST");

	WIN32_FIND_DATAA  fileAttr;
	HANDLE  handle;

	remove("filelist_new.txt");

	fd = fopen("filelist.txt", "r");
	fd_new = fopen("filelist_new.txt", "a+");
	if (!fd)
	{
		printf("Open the filelist error,please check the name of filelist!\n");
		return -1;
	}

	while (!feof(fd))
	{
		fscanf(fd, "%s", filename[file_count]);
		file_count++;
	}
	printf("********************************************\n");
	printf("There are %d files in your datasheet folder!\n", file_count);
	printf("********************************************\n");

	printf("Their names are :\n");
	for (int i = 0; i<file_count; i++)
	{
		printf("%d,%s\n", i, filename[i]);
	}

	for (int j = 0; j<file_count; j++)
	{
		for (int k = j + 1; k<file_count;)
		{
			if ((strcmp(filename[k], filename[j]) == 0))
			{
				for (int m = k + 1; m<file_count; m++)
				{
					strcpy(filename[m - 1], filename[m]);
				}
				file_count--;
			}
			else
				k++;
		}
	}
	printf("*******************************************************\n");
	printf("There are %d different files in your datasheet folder!\n", file_count);
	printf("*******************************************************\n");
	printf("Their names are :\n");
	for (int n = 0; n<file_count; n++)
	{
		printf("%d,%s\n", n, filename[n]);
		fprintf(fd_new, "%s\n", filename[n]);
	}
	printf("*************************************************************\n");
	printf("You can check the different files names in \"filelist_new.txt\"!!!\n");
	printf("*************************************************************\n");
	fclose(fd);
	fclose(fd_new);

	FILE *folder;
	char *fullname = "";
	for (int n = 0; n<file_count; n++)
	{
		//		printf("%d,%s\n",n,filename[n]);

		fullname = strcat(filename[n], suffix);

		//		printf("%s\n",fullname);

		handle = FindFirstFileA(".\\datasheet\\*.pdf", &fileAttr);

		if (handle == INVALID_HANDLE_VALUE)
		{
			cout << "invalid handle value " << GetLastError() << endl;
		}
		else
		{
			//			cout<<fileAttr.cFileName<<endl; //输出查找到的文件名

			if ((strcmp(fullname, fileAttr.cFileName) == 0))
			{
				sprintf(namestring, "copy .\\datasheet\\%s .\\LAST\\%d_%s", fileAttr.cFileName, n, fileAttr.cFileName);
				system(namestring);
				final_count++;
			}
			while (FindNextFileA(handle, &fileAttr))
			{
				//				cout<<fileAttr.cFileName<<endl; //输出每一个查找到的文件名

				if ((strcmp(fullname, fileAttr.cFileName) == 0))
				{
					sprintf(namestring, "copy .\\datasheet\\%s .\\LAST\\%d_%s", fileAttr.cFileName, n, fileAttr.cFileName);
					system(namestring);
					final_count++;
					break;
				}
			}

			if (GetLastError() == ERROR_NO_MORE_FILES)
			{
				;//cout<<"查找完毕"<<endl;
			}
			else
			{
				cout << "查找过程出现错误" << endl;
			}

			FindClose(handle);
		}
	}
	printf("******************************************************\n");
	printf(" The %d different files in filelist have already \n", final_count);
	printf(" copied from datasheet to folder \"LAST\"!!!\n");
	printf("******************************************************\n");


	return 0;
}