#include "./file.h"
#include <cassert>
#include <iostream>

/*
adapted from
https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows
TODO: change from wchar to char; this is really problamatic!
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

std::vector<Recipe*> file::loadAllRecipes(const wchar_t* sDir)
{
    std::vector<Recipe*> result;

    std::vector<wchar_t*> filetable;
    ListDirectoryContents(&filetable, sDir);
    
    
    for (wchar_t* filename : filetable)
    {
        std::string file_contents = LoadFile(filename);
        Parser parse(file_contents, wcharToString(filename));
        parse.Parse();
        result.push_back(parse.getReceipe());
    }

    return result;
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

/*
* Written with help by chatgpt.

*/
bool file::saveRecipeToFile(Recipe* recipe)
{
    std::string textToWrite = recipe->toString();

    // this was because previously we took the title to set as filename.
    //std::stringstream ss;
    //ss << "Recipes/" << recipe->title << ".md";  // Format the filename

    //std::string filename = ss.str();
    //for (char& c : filename) {
    //    if (c == ' ') {
    //        c = '_';
    //    }
    //}

    std::ofstream outFile(recipe->filename);

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return false; // Return with an error code
    }

    outFile << textToWrite;

    outFile.close();

    return true;
}

bool file::deleteFile(std::string filename)
{

    if (std::remove(filename.c_str()) == 0) {
        return true;
    }
    else {
        std::perror("Error deleting file"); 
    }

    return false;
}

// this is because we list our directory contents as wchar_t*,
// consider changing to wchar!
std::string file::wcharToString(const wchar_t* wstr) {
    std::wstring wide_str(wstr);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wide_str);
}

void file::unittest() {
    try {
        // Create a temporary file directly
        std::string tempFilename = "tempfile_test.txt";
        std::ofstream outfile(tempFilename);
        if (!outfile) {
            throw std::runtime_error("Error creating temporary file");
        }
        outfile << "Test content";
        outfile.close();

        // Test LoadFile
        std::string content = LoadFile(tempFilename.c_str());
        assert(content == "Test content");
        std::cout << "LoadFile test passed." << std::endl;

        // Test saveRecipeToFile
        Recipe testRecipe;
        testRecipe.setFilename(tempFilename);
        testRecipe.setTitle("Test Recipe");
        testRecipe.addIngredient(1, Recipe::teaspoon, "Salt");
        testRecipe.addInstruction("Mix all ingredients.");

        // Save the recipe to file
        bool saved = saveRecipeToFile(&testRecipe);
        assert(saved);
        std::cout << "saveRecipeToFile test passed." << std::endl;

        // Verify if file was saved correctly
        std::string savedContent = LoadFile(tempFilename.c_str());
        assert(savedContent.find("Test Recipe") != std::string::npos);
        assert(savedContent.find("Salt") != std::string::npos);
        assert(savedContent.find("Mix all ingredients.") != std::string::npos);

        // Delete the file
        bool deleted = deleteFile(tempFilename);
        assert(deleted);
        std::cout << "deleteFile test passed." << std::endl;

        // Test ListDirectoryContents
        std::vector<wchar_t*> fileTable;
        ListDirectoryContents(&fileTable, L".");
        
        bool fileFound = false;
        for (wchar_t* file : fileTable) {
            std::string fileStr = wcharToString(file);
            if (fileStr == tempFilename) {
                fileFound = true;
                break;
            }
        }
        assert(!fileFound); // Ensure the temp file was deleted
        std::cout << "ListDirectoryContents test passed." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    std::cout << "All tests passed." << std::endl;
}
