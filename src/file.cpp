#include "./file.h"
/*
adapted from
https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows

*/
bool file::ListDirectoryContents(std::vector<wchar_t*> *fileTable, const wchar_t *sDir)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    wchar_t sPath[2048];

    //Specify a file mask. *.* = We want everything! 
    wsprintf(sPath, L"%s\\*.*", sDir);

    if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        wprintf(L"Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories. 
        if (wcscmp(fdFile.cFileName, L".") != 0
            && wcscmp(fdFile.cFileName, L"..") != 0)
        {
            //Build up our file path using the passed in 
            //  [sDir] and the file/foldername we just found: 
            wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder? 
            if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                //wprintf(L"Directory: %s\n", sPath);
                ListDirectoryContents(fileTable, sPath); //Recursion, I hate it! 
            }
            else {
                //wprintf(L"File: %s\n", sPath);
                wchar_t* fileName = (wchar_t*)calloc(2048, sizeof(wchar_t));

                wcscpy_s(fileName, 2048, sPath);

                fileTable->push_back(fileName);
            }
        }
    } while (FindNextFile(hFind, &fdFile)); //Find the next file. 

    FindClose(hFind); //Always, Always, clean things up! 

    return true;
}

/*
* Provided by chatgpt.com
* TODO: DOES NOT SUPPORT WCHAR!

*/
std::string file::LoadFile(const wchar_t* fileName)
{
    std::ifstream file(fileName); // Open the file
    if (!file.is_open()) { // Check if file opened successfully
        throw std::runtime_error("Could not open the file: ");
    }

    std::ostringstream oss; // Use ostringstream to build the string
    oss << file.rdbuf(); // Read the file contents into the stringstream

    return oss.str(); // Convert the stringstream to a string
}

bool file::saveRecipeToFile(Recipe* recipe)
{
    std::string textToWrite = recipe->toString();

    std::stringstream ss;
    ss << "Recipes/" << recipe->title << ".md";  // Format the filename

    std::string filename = ss.str();
    for (char& c : filename) {
        if (c == ' ') {
            c = '_';
        }
    }

    std::ofstream outFile(filename);  // Open the file

    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return false; // Return with an error code
    }

    // Write the string to the file
    outFile << textToWrite;

    // Close the file
    outFile.close();

    // Notify the user
    std::cout << "String written to file successfully!" << std::endl;
    return true;
}
/*

Recipe file::parseRecipeFile(std::string recipeFile)
{

    const char* contents = recipeFile.c_str();
    uint32_t left = 0;
    uint32_t right = 0;
}*/